#include<Wire.h>
#include<LiquidCrystal_I2C.h>
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
float vout;
float temp;
float density;
int gs = A0;
int gs2 = A6;
int gs3 = A7;
int buzz = 7;
int led = 13;
int light = 2;
int fan = 3;
int lock = 4;
int autoled=11;
int dcfan_pwm =9;
int dcfan_inA =8;
int dcfan_inB = 10;
int spd = 250 ;
int smoke1 ;
int smoke2 ;
int smoke3 ;
int smoke ;
char sms;
void lightonoff()
{
  digitalWrite(buzz, HIGH);
  digitalWrite(led, HIGH);
  delay(5000);
  digitalWrite(led, LOW);
  digitalWrite(buzz, LOW);
  delay(5000);
}


void setup() {
  
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(buzz, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(lock, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(autoled, OUTPUT);
  pinMode(dcfan_pwm, OUTPUT);
  pinMode(dcfan_inA, OUTPUT);
  pinMode(dcfan_inB, OUTPUT);
  

}

void loop() {
  
  density = analogRead(A2);
  if(density<500)
  {
    digitalWrite(autoled,HIGH);
  }
  else
  {
    digitalWrite(autoled,LOW);
  }
  smoke1 = analogRead(gs);
  smoke2 = analogRead(gs2);
  smoke3 = analogRead(gs3);
  smoke  = ((smoke1 + smoke2 + smoke3) / 3);
  vout = analogRead(A1);
  temp = (vout * 500) / 1023;

  if (smoke > 100)
  {
    lightonoff();
    analogWrite(dcfan_pwm,spd);
    digitalWrite(dcfan_inA, HIGH);
    digitalWrite(dcfan_inB, LOW);
  }
  else
  {
    digitalWrite(buzz, LOW);
    digitalWrite(led, LOW);
    digitalWrite(dcfan_inA, LOW);
    digitalWrite(dcfan_inB, LOW);
    
  }
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("Density: ");
  lcd.print(density);

  Serial.print(temp);
  Serial.print("|");
  Serial.print(density);
  Serial.print("|");
  Serial.println(smoke);
  delay(3000);
  //control
  if (Serial.available() != 0)
  {
    sms = Serial.read();
  }
  if (sms == '1')
  {
    digitalWrite(light, HIGH);
  }
  if (sms == '2')
  {
    digitalWrite(light, LOW);
  }
  if (sms == '3')
  {
    digitalWrite(fan, HIGH);
  }
  if (sms == '4')
  {
    digitalWrite(fan, LOW);
  }
  if (sms == '5')
  {
    digitalWrite(lock, HIGH);
  }
  if (sms == '6')
  {
    digitalWrite(lock, LOW);
  }
}
