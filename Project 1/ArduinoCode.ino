#include <Servo.h>
#include <SoftwareSerial.h>

Servo myservo;  // create servo object to control a servo
 
const int LEDfood=12;
const int LEDempty = 13;
const int irPin = 8;  // This is our input pin
int isEmpty = LOW;  // LOW MEANS CONTAINER IS FILLED
int Data=0; //Data input
int buzzer=5; //buzzer pin
SoftwareSerial mySerial(11,10); // Bluetooth module tx rx

void setup() {
  // put your setup code here, to run once:
 
  myservo.attach(9,600,2300);  // (pin, min angle in ms pulse duration, max)
 
  pinMode(LEDfood, OUTPUT);
  pinMode(LEDempty, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(2,OUTPUT);
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
 
  Serial.begin(9600);
  mySerial.begin(9600);
}
 
void serv(int t){
  
  Serial.print("Servo is Working for ");
  Serial.println(t);
  digitalWrite(buzzer,HIGH);
  myservo.write(130-20);  // tell servo to go to a particular angle
  delay(1000*t);
 
  myservo.write(0+10);              
  delay(500*2*t);
 
  myservo.write(130-20);              
  //delay(1500);
  digitalWrite(buzzer,LOW);
   
}
 
void chkEmpty(){
  isEmpty = digitalRead(irPin);
  if (isEmpty == LOW)
  {
    Serial.println("RELAX! Food is enough.");
    digitalWrite(LEDempty, LOW);
  }
  else
  {
    Serial.println("ALERT! Fill the food.");
    digitalWrite(LEDempty, HIGH);
    mySerial.write(1);
  }
  delay(200);
  digitalWrite(LEDempty, LOW);
}
// 
//double ultronic(){
//     // Clears the trigPin
//    digitalWrite(trigPin, LOW);
//    delayMicroseconds(2);
//    // Sets the trigPin on HIGH state for 10 micro seconds
//    digitalWrite(trigPin, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(trigPin, LOW);
//    // Reads the echoPin, returns the sound wave travel time in microseconds
//    double t = pulseIn(echoPin, HIGH);
//    // Calculating the distance
//    double dist= t*0.034/2;
//    // Prints the distance on the Serial Monitor
//    Serial.print("Distance: ");
//    Serial.println(dist);
//    return dist;
//}
//int bluetooth(){
//int Data=0;
//if (mySerial.available())
//
//{
//Data=mySerial.read();
//
//Serial.println(Data);
//
//}
//delay(100);
//return Data;
//}
 
void loop() {
  // put your main code here, to run repeatedly:
//Serial.println(bluetooth());
digitalWrite(2,LOW);
if (mySerial.available())

{
Data=mySerial.read();

Serial.println(Data);

chkEmpty();
serv(Data);

}

//delay(100);
long time=millis()/1000;
Serial.println(time);
if(time%(2*60)==0){
  serv(4);
}

}
