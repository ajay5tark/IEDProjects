#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <SoftwareSerial.h>

Servo myservo;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

const int ledPin = 13;
const int knockSensor = A3;
const int threshold = 1;
int sensorReading = 0;
const int  buzzerpin= 5;
int rfid_on=0;
int irs=8;
int acessdenied=0;
const int wifi1=4;
const int wifi2=3;
int doorstate=0;
const int particle=2;
int kok=0;
void setup()
{
  myservo.attach(6, 600, 2300);
  pinMode(A1, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(buzzerpin,OUTPUT);
  pinMode(irs,INPUT);
  pinMode(wifi1,INPUT);
  pinMode(wifi2,INPUT);
  pinMode(particle,OUTPUT);
  myservo.write(120);

}
void loop()
{
  rfid();
  knock();
  ir();
  //Serial.print(digitalRead(wifi1));
  
  //Serial.print(" ");
  
  //Serial.println(digitalRead(wifi2));
  
  
  if(digitalRead(wifi1)==HIGH){ //open
    serv(0);
    doorstate=1;
    rfid_on=1;
    kok=0;
 
  }
  if(digitalRead(wifi2)==HIGH){ //close
    serv(120);
    doorstate=0;
    rfid_on=0;
  }
 
 // delay(1000);
}
void rfid() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "85 27 41 43") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
    analogWrite(A1, 5);
    serv(0);
    rfid_on=1;
    kok=0;
  }

  else   {
    Serial.println(" Access denied");
    Serial.println();
    analogWrite(A1, 10);
    //buzzer();
    //digitalWrite(buzzerpin,HIGH);
    delay(3000);
     if(acessdenied>2){
      buzzer();
      acessdenied=0;
      rfid_on=0;
    }
    
    acessdenied+=1;
    //digitalWrite(buzzerpin,LOW);
   
    
  }
}
void serv(int t) {

  Serial.print("Servo is Working for ");
  Serial.println(t);
  //digitalWrite(buzzer,HIGH);
  myservo.write(t);  // tell servo to go to a particular angle
  delay(1000);

  //myservo.write(0+10);
  //delay(500);

  //myservo.write();
  //delay(1000);
  //digitalWrite(buzzer,LOW);

}
void knock() {
  // read the sensor and store it in the variable sensorReading:
   sensorReading= analogRead(knockSensor);
 Serial.println(sensorReading); 
  // if the sensor reading is greater than the threshold:
  if (sensorReading <= threshold&&kok==0) {
    // toggle the status of the ledPin:
   // send the string "Knock!" back to the computer, followed by newline
    Serial.println("Knock!");
    rfid_on=0;
    serv(120);
    kok=1;
  }
  delay(250) ;  // delay to avoid overloading the serial port buffer
}
void buzzer(){
  digitalWrite(buzzerpin,HIGH);
  digitalWrite(particle,HIGH);
  delay(3000);
  digitalWrite(particle,HIGH);
  digitalWrite(buzzerpin,LOW);
}
void ir(){
  if(digitalRead(irs)==LOW&&rfid_on!=1){
    Serial.println("chor aaya");
    buzzer();
    //delay(1000);
  }
//  if(digitalRead(irs)==LOW&&rfid_on==1){
//    rfid_on=0;
//  }
  //                  Serial.println(digitalRead(irs));
}
