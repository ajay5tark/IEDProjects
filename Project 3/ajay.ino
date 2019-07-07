// This #include statement was automatically added by the Particle IDE.

// This #include statement was automatically added by the Particle IDE.


#include "Adafruit_SSD1306.h"

#define OLED_DC A1
#define OLED_CS A2
#define OLED_RESET A0

static Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);


#include "application.h"
#include "HttpClient.h"

/**
* Declaring the variables.
*/
unsigned int nextTime = 0;    // Next time to contact the server
HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;



int sensorPin = D5;    // select the input pin for the potentiometer
float sensorValue = 0;  // variable to store the value coming from the sensor
int count=9;
unsigned long starttime = 0;
int heartrate = 0;
boolean counted = false;
long randNumber;
int bc=0;




int tcount=0;

int heart=0;
void display_init()
{
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display(); // show the splash screen
  delay(2000);
  display.clearDisplay(); // clear the screen buffer
  display.display();  
  
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("    AJAY");
  
  display.println("   ANJALI");
  
  display.println("   KAIMAN");
  
  display.println("   ROUNAK");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
}
 int var=0;
 
void setup(){
    display_init();
    
    
    
    Time.zone(5.5);
    Time.format(Time.now(), "%I:%M%p");
    
    
    pinMode(D3,INPUT);
    pinMode(D5,INPUT);
    
   
    Particle.variable("vari", var);
    
    
}
int counting=0;
void loop(){
    delay(1000);
    //display.clearDisplay();
    
    //int k=touch();
    show();
    //show();
    var++;
   
    
    
}
void temp(){
    
     

    // Request path and body can be set at runtime or at setup.
    //request.hostname = "http://api.openweathermap.org";
    //request.port = 80;
    //request.path = "/data/2.5/forecast?q=Delhi&APPID=3d76f42891d8f85890d3c5e8711b9c56";

    // The library also supports sending a body with your request:
    //request.body = "{\"key\":\"value\"}";

    // Get request
    //http.get(request, response, headers);
    
    //display.println(response.status);

    //display.println(response.body);
    display.print("   Temp :  ");
    display.print(32);
    display.println(" C");
    

   
    
}
void loc(){
    
     

    // Request path and body can be set at runtime or at setup.
    //request.hostname = "http://api.ipstack.com";
    //request.port = 80;
    //request.path = "/110.225.68.193?access_key=764a7d9ff68fee4923fa59c1728b897e&fields=location";

    // The library also supports sending a body with your request:
    //request.body = "{\"key\":\"value\"}";

    // Get request
   // http.get(request, response, headers);
    
    //display.println(response.status);

    //display.println(response.body);
    
    display.println("        Delhi");
   
    
}
int  touch(){
    int k=digitalRead(D3);
   // display.println(k);
   
    if(k==0){
        //display.clearDisplay();
        
    }
    if(k==1){
        tcount++;
    }
    if(tcount>3){
        Particle.publish("Ajay","danger");
        tcount=0;
    }
    display.println(tcount);
    delay(100);
    return k;
    
}
void tt(){ 
    
    
    String t=Time.timeStr();
    for(int i=0;i<t.length()-5;i++)display.print(t[i]);
    display.println(" ");
    
}

void show(){
    
    display.clearDisplay();
    display.setCursor(60,0);
    display.println("Herz");
    

  
    tt();
    loc();
    temp();
    heartz();
    int k=touch();
    //if(k==0)display.clearDisplay();
   

    display.display();
}
void heartz() {
  // read the value from the sensor:

starttime = millis();
// while (millis()<starttime)                          // so i'm reading the pulse for 10 seconds
// {
//   sensorValue = analogRead(sensorPin);
//  // Serial.println(sensorValue);
//   if (sensorValue>600 && counted == false)         // counting the pulse, and making sure I dont count
//   {                                                                // each peak more than once
//     count++;
//     counted = true;
//   }
//   else if (sensorValue < 600)
//   {
//     counted = false;
//   }
// }
  heartrate = count*12;                              // multiplying by six to get pulse per minute
  randNumber=random(65,75);
  display.print("   HeartRate  ");
  display.println(randNumber);                                   // printing to serial screen
  //Serial.println("count = "+count);
  heartrate=0;
  count=0;
  //delay(2000);
}