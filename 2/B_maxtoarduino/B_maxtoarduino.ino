
// this runs once:
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // turns on the serial - 9600 is the baud rate
  pinMode(9, OUTPUT); // pin 9 is output
}

void loop() {
  int incoming;
  
  // SERIAL OUT FROM ARDUINO TO COMPUTER:
  int val = analogRead(A0); // read the pin A0 and store it into 'val'
  Serial.println(val); // send the 'val' down the serial line

  // SERIAL IN FROM COMPUTER TO ARDUINO:
  if (Serial.available()) {
    // read the oldest byte in the serial buffer:
    incoming = Serial.read();
    analogWrite(9, incoming);
  }
  
  delay(5);
}
