const int potPin = A0;
const int BUTTON_PIN = 2;
const int RED = 11;
const int GREEN = 10;
const int BLUE = 9;
int ledState = 0;  //0 - off, 1 - on, 2 - on, 3 - on
boolean isHeld = false;
boolean autoOn = false;

int distanceThreshold = 0;
int cm = 0;
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(potPin, INPUT);  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
}

    
    
void loop()
{
  distanceThreshold = 250;
  cm = 0.01723 * readUltrasonicDistance(7,6);
  Serial.print(cm);
  Serial.print("cm, ");
  if (cm <= distanceThreshold) {
    autoOn = true;
  }
  else {
  autoOn = false;
  }
  
  
  int potValue = analogRead(potPin);
  Serial.println(potValue);
  
  int bright = map(potValue,0,1023,0,255);
  
 // analogWrite(11, bright);
  
  
  int buttonValue = digitalRead(BUTTON_PIN);
  	Serial.println(buttonValue);
  	
  if (buttonValue == 0 && isHeld == false) {
  	ledState = (ledState + 1)%5;
    isHeld = true;
  }
  else if (buttonValue == 1) {
  	isHeld = false;
  }
  
   if (ledState == 0) { //if off
     if (autoOn == true){
        digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
     }
     else {
    analogWrite(RED, 0);
  	analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
     }
  }
  else if (ledState == 1) { //RED
  	analogWrite(RED, bright);
  }
  else if (ledState == 2) {//GREEN
    analogWrite(RED, 0);
    analogWrite(GREEN, bright);
  }
  else if (ledState == 3) {//BLUE
    analogWrite(GREEN, 0);
    analogWrite(BLUE, bright);
  }
    else if (ledState == 4) {//BLUE
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
  }
}