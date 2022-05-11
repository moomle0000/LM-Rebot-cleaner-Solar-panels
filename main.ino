#include "arduino_secrets.h"
#include "thingProperties.h"

int led = 6;
// Motor A connections
int enA = 0;  //for speed control motor low
int in1 = 1;  //for direction control motor low
int in2 = 2;  //for direction control motor low
// Motor B connections
int enB = 5;  //for speed control motor high
int in3 = 3;  //for direction control motor High
int in4 = 4;  //for direction control motor

//Ultrasonic Sensor
const int trigPin = 8;
const int echoPin = 10;

//Roller Button
const int rollerbutton = A1;
//Run Button
const int rubutton = 9;      // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;   // the previous reading from the input pin

bool roll = true;
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
// the last time the output pin was toggled
unsigned long debounce = 200UL;   // the debounce time, increase if the output flickers
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int right = 0;
int ultrastat = 0;
int scultrastat = 0;

void setup() {
  // Initialize serial and wait for port to open:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //
  pinMode(rubutton, INPUT_PULLUP);
  pinMode(rollerbutton, INPUT_PULLUP);
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found




  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  delay(9500);
}

void loop() {
  ArduinoCloud.update();

  starte();

  onScheduleTestChange();



}

/*
  Since Start is READ_WRITE variable, onStartChange() is
  executed every time a new value is received from IoT Cloud.
*/




void onStartChange()  {
  // Add your code here to act upon Start change

}

void starte() {


  enging();


  stopall();


}




void motorleft() {
  digitalWrite(in1, HIGH); // motor controller left
  digitalWrite(in2, LOW); // motor controller left
  digitalWrite(in3, HIGH); // motor controller left
  digitalWrite(in4, LOW); // motor controller left

  analogWrite(enA, 100); // motor enA speed 
  analogWrite(enB, 100); // motor enB speed 


}

void motorright() {
  stopmotor();
  digitalWrite(in1, LOW); // motor controller right
  digitalWrite(in2, HIGH); // motor controller right
  digitalWrite(in3, LOW); // motor controller right
  digitalWrite(in4, HIGH); // motor controller right

  analogWrite(enA, 100); // motor enA speed 
  analogWrite(enB, 100); // motor enB speed 
  //delay(20);




}

int ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //Serial.println(distance);
  delay(100);

  return distance;


}



void stopmotor() {

  digitalWrite(in1, LOW); // stop  all motor
  digitalWrite(in2, LOW); //stop  all motor
  digitalWrite(in3, LOW); //stop  all motor
  digitalWrite(in4, LOW); //stop  all motor


}


void enging() {

  //Serial.println(start);


  if (start == 1) {
    int cm = ultrasonic();
    ultras = cm;
    if (cm < 10) {
      if (ultrastat == 0) {
        motorleft();
      }
      if (ultrastat == 1) {
        motorright();
      }
    }
    if (cm > 10) {
      ultrastat = 1;
      motorright();
    }

  } else {
    stopmotor();

  }





}

void stopall() {
  int buttonState = 0;
  buttonState = digitalRead(rollerbutton);
  // if roll button no stop all the motor and reset all setting
  if (buttonState == LOW) {
    stopmotor();
    start = 0;
    ultrastat = 0;
    motorleft();
  }

}
/*
  Since ScheduleTest is READ_WRITE variable, onScheduleTestChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onScheduleTestChange()  {
  // Add your code here to act upon ScheduleTest change

  if (schedule_test.isActive()) {
    Serial.println("ON schedule_test");
      start = 1;
    

  }

  if (ArduinoCloud.connected()) {
    time_read = ArduinoCloud.getLocalTime();
  }
}







