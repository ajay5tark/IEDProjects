int output=0;
void setup() {

pinMode(A1,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(D6,OUTPUT);
pinMode(D5,INPUT);
Particle.function("doorOpen",door);
Particle.function("doorClose",close);
// char* ajay="ajay";
// Particle.publish(ajay,"open");
Particle.variable("output",output);
}

void loop() {

if(digitalRead(D5)==HIGH){

Particle.publish("ajay","open");

    
}
    
}
int door(String str){
    analogWrite(A1,5);
    digitalWrite(D7,HIGH);
    //digitalWrite(D6,LOW);
    delay(1000);
    digitalWrite(D7,LOW);
    
    output=5;
    return 0;
}
int close(String str){
    analogWrite(A1,10);
    //digitalWrite(D7,LOW);
    digitalWrite(D6,HIGH);
    delay(1000);
    digitalWrite(D6,LOW);
    output=10;
    return 0;
}
