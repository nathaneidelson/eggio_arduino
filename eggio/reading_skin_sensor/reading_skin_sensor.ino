int inPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(inPin, INPUT);      // sets the digital pin 7 as input

}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(inPin);
  Serial.println(val);
}
