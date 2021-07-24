#include<Servo.h>
#include <TinyGPS.h>
TinyGPS gps; 
Servo Myservo1,Myservo2,Myservo3,Myservo4,Myservo5,Myservo6,Myservo7,Myservo8;
int pot1 = A0;
int pot2 = A1;
int pot3 = A2;
int pot4 = A3;
int pot5 = A7;
int pot6 = A6;
const int echo = 11;
const int trig = 12;
unsigned long current = 0;
unsigned long previous = 0;
int ser1 = 7;
int a =0;
int b =0;
int c =0;
int d =0;
int f =0;
int e =0;
int h =0;

void setup() {
  pinMode(pot1,INPUT);
  pinMode(pot2,INPUT);
  pinMode(pot3,INPUT);
  pinMode(ser1,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  Myservo1.attach(7);
  Myservo2.attach(6);
  Myservo3.attach(5);
  Myservo4.attach(4);
  Myservo5.attach(3);
  Myservo6.attach(45);
  Myservo7.attach(44);
  Myservo8.attach(43);
}

void loop() {

  
  //########################################
gprs();

  current =millis();
   
   //############motion#################
  a = analogRead(pot1);
  float v=a/51.15;
   //###############propulsion####################
  for(int pos=80;pos<=110;pos+=v)
  {
   
   Myservo1.write(pos);
   delay(10);
   Myservo2.write(pos);
   delay(10);
   Myservo3.write(pos);
   delay(10);
  }
   for(int pos=110;pos>=80;pos-=v)
  {
  
   Myservo1.write(pos);
   delay(10);
   Myservo2.write(pos);
   delay(10);
   Myservo3.write(pos);
   delay(10);
  }
  //###################direction########################
  b = analogRead(pot2);
  b=map(b, 0,1023, 0, 90);
  Myservo4.write(b);
  delay(10);
  c = analogRead(pot3);
  c=map(c, 0,1023, 0, 180);
  Myservo5.write(c);
  delay(10);
  d = analogRead(pot4);
  d=map(d, 0,1023, 0, 70);
  Myservo6.write(d);
  delay(10);
  h = analogRead(pot6);
  h = map(h, 0, 1023, 0, 80);
  Myservo7.write(h);
  Myservo8.write(h);
  delay(10);
 //##############ballast######################
 e = analogRead(pot5);
 if(e<210)
 {
 analogWrite(10,150);
 analogWrite(9,0);
 delay(10);
 }
 else if(e>810)
   {
   analogWrite(9,150);
   analogWrite(10,0);
   delay(10);
   }
   else{
    analogWrite(9,0);
    analogWrite(10,0);
    delay(10);
   }
   //##############################fins#######################
   
   //################# distance#######################
 long duration,cm;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration= pulseIn(echo,HIGH);
 
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println(" ");
  delay(10);
 
  
 
 //###############direction################
 


}

long microsecondsToCentimeters(long microseconds)
  {
    return microseconds/29/2;
  }

void gprs(){
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  for (unsigned long start = millis(); millis() - start <=1000;)
  {
    while (Serial.available())
    {
      char g = Serial.read();
      //Serial.print(c);
      if (gps.encode(g)) 
        newData = true;  
    }
  }

  if (newData) 
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);   
    Serial.print("Latitude = ");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" Longitude = ");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);

  }
 
  Serial.println(failed);
}
