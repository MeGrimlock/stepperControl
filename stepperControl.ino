// defines pins numbers

const int enablePin = 17;

const int ms1Pin = 16;
const int ms2Pin = 15;
const int ms3Pin = 14;

const int rstPin = 13;
const int slpPin = 12;

const int stepPin = 11; 
const int dirPin = 10; 

const int button = 2;
int motorStep = 1;

void setup() {
  Serial.begin(9600);
  pinMode(button,INPUT_PULLUP);
  // Sets the two pins as Outputs
  pinMode(enablePin,OUTPUT);
  
  pinMode(ms1Pin,OUTPUT);
  pinMode(ms2Pin,OUTPUT);
  pinMode(ms3Pin,OUTPUT);
  
  pinMode(rstPin,OUTPUT);
  pinMode(slpPin,OUTPUT);
  
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  //Config word
  //low , MOTORS ON
  digitalWrite(enablePin, LOW);
  //All low for full step
  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, LOW);
  //High allows to work, otherwise it goes to preconfig start position.
  digitalWrite(rstPin, HIGH);
  digitalWrite(slpPin, HIGH);
  //Step high on step, dir for clockwise antclockwise
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, HIGH);
  
}

unsigned long previousMillis = 0; 
long intervalFast = 1000;
long intervalNormal = 18000;
long interval = intervalNormal; 

void loop() {
  unsigned long currentMillis = millis();
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  int sensorVal = digitalRead(button);
  //Switch mode
  /*
  if (sensorVal == LOW) {
      if(interval == intervalNormal){
        interval = intervalFast;
      }else{
        interval = intervalNormal;  
      }  
      delay(100);        
  }*/
  if (sensorVal == LOW) {
    interval = intervalFast;
    motorStep=2;
  }else{
    interval = intervalNormal;
    motorStep=1;
  }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    for(int x = 0; x < motorStep; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500); 
    }  
    Serial.println(previousMillis);
  }  
}
