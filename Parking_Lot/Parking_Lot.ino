// Parking Lot Arduino code

#define ledr 9
#define ledb 10
#define ledy 11
#define lsl A0
#define lsr A1
#define Bee 4
#include <Servo.h>
#include <Wire.h>
byte x = 0;
Servo myservo;
int flag=0;
int flag2=0;
int pos = 90;
int a=0;
int r,l;
const int NOTES_1[] = { 262, 294, 330, 349 }; // C, D, E, F frequencies
const int NOTES_2[] = { 349, 330, 294, 262 }; // C, D, E, F frequencies
void setup() {
// put your setup code here, to run once:
Wire.begin(1);
Wire.onReceive(receiveEvent);
Serial.begin(9600);
pinMode(ledr,OUTPUT);
pinMode(ledb,OUTPUT);
pinMode(ledy,OUTPUT);
pinMode(Bee,OUTPUT);
pinMode(lsr,INPUT);
pinMode(lsl,INPUT);
myservo.attach(8); // 將 servo 物件連接到 pin 8
}

void loop() {
// tone(Bee, NOTES_2[2]); // first switch ~ key C

r=analogRead(lsr);
l=analogRead(lsl);

myservo.write(pos);
if(a==0||a==1){
digitalWrite(ledb,HIGH);
digitalWrite(ledr,LOW);
digitalWrite(ledy,LOW);
}
if(a==2){
digitalWrite(ledy,HIGH);
digitalWrite(ledr,LOW);
digitalWrite(ledb,LOW);
}
if(a==3){
digitalWrite(ledr,HIGH);
digitalWrite(ledb,LOW);
digitalWrite(ledy,LOW);
}
if(flag2==1){
for (int i = 0 ;i<4;i++){
tone(Bee, NOTES_2[i]); // first switch ~ key C
delay(250);
}
noTone(Bee);
flag2=0;
}
if(flag==1){
if(pos==90)
{
pos=180;
myservo.write(pos);
a++;
r=500;
l=500;
Serial.println(a);
for (int i = 0 ;i<4;i++){
tone(Bee, NOTES_1[i]); // first switch ~ key C
delay(250);
}
noTone(Bee);
delay(1000);
flag=0;
}
}

if(pos==90)
{
if(r<350)
{
if(a<3)
{ Wire.beginTransmission(0); // transmit to device #0
Wire.write(0x31); // sends five bytes
Wire.endTransmission(); // stop transmitting
}
}
if(l<350)
{
if(a>0)
{ pos=180;
myservo.write(pos);
a--;
r=500;
l=500;
}
Serial.println(a);
delay(1000);
}
}

if(pos==180)
{
if(l<350){
pos=90;
myservo.write(pos);
}
if(r<350){
pos=90;
myservo.write(pos);
}
}


delay(1000);
Serial.println(a);

}

void receiveEvent(int numBytes){
char c;
while(Wire.available()){ //判斷Wire.available()有沒有訊號
c = Wire.read(); //將傳入的訊號Wire.read()指定給字串C
Serial.print(c); //透過Serial印出字串C的內容
}
if (c == 0x11)
{
flag=1;
}
if (c == 0x22)
{
flag2 =1;
flag=0;
}

}
