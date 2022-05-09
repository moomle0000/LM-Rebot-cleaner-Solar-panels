// Motor A connections
int enA = 9;  //for speed control motor low
int in1 = 8;  //for direction control motor low
int in2 = 7;  //for direction control motor low
// Motor B connections
int enB = 3;  //for speed control motor high
int in3 = 5;  //for direction control motor High
int in4 = 4;  //for direction control motor

//Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;

//Roller Button
const int rollerbutton = A0;
//Run Button
const int rubutton = 12;      // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long time = 0;           // the last time the output pin was toggled
unsigned long debounce = 200UL;   // the debounce time, increase if the output flickers
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int ultrastat = 0;

void setup()
{
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
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");


}

void loop()
{
  reading = digitalRead(rubutton);

  int buttonState = 0;
  buttonState = digitalRead(rollerbutton);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW )
  {
    if (state == HIGH) {
      state = LOW;
      ultrastat = 0;
    }
    else {
      state = HIGH;
      ultrastat = 0;
    }

    time = millis();
  }


  if (state == 1) {
    Serial.println(state);

    int cm = ultrasonic();

    Serial.println(ultrastat);




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


  if (buttonState == LOW) {
    stopmotor();
    state = 0;
    ultrastat = 0;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, 155);
    analogWrite(enB, 155);


    // if bush roll button stop

  }









  previous = reading;
}




void motorleft() {

  //analogWrite(enA, 100);
  //analogWrite(enB, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 255);
  analogWrite(enB, 255);


}

void motorright() {
  stopmotor();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 255);
  analogWrite(enB, 255);
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
  Serial.println(distance);

  return distance;


}



void stopmotor() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);


}
