#include <Servo.h>

const int TRIG_PIN  = 6;
const int ECHO_PIN  = 7;
const int SERVO_PIN = 9;
const int DISTANCE_THRESHOLD = 8;
Servo servo;
float duration_us, distance_cm;    //servo distance

int trigPin1 = 11;    // Trigger
int echoPin1 = 12;    // Echo
long duration1, cm1, inches1;
int Motor=10;
 
void setup() {
  servo.attach(9);
  Serial.begin (9600);

  pinMode(TRIG_PIN, OUTPUT);  //servo
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN);
  servo.write(0);

  pinMode(trigPin1, OUTPUT);  //pump
  pinMode(echoPin1, INPUT);
  pinMode(Motor, OUTPUT);
}
 
void loop() {

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;
  if(distance_cm >= DISTANCE_THRESHOLD){
    servo.write(90);
    Serial.print("Servo Rotates");
  }
  else{
    servo.write(0);
  }

  Serial.print("distance of Servo: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
    
  digitalWrite(Motor, LOW);   //pump
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
 
  // Convert the time into a distance
  cm1 = (duration1/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches1 = (duration1/2) / 74;   // Divide by 74 or multiply by 0.0135
  if (cm1 <=10){
    digitalWrite(Motor, HIGH);
    delay(2000);
    Serial.print("Pump Starts");
    
  }
  Serial.print(inches1);
  Serial.print("in, ");
  Serial.print(cm1);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
