
int x, y, v;
int h = 0;
int s = 255;
  

void setup() {

  Serial.begin(9600); // turns on the serial - 9600 is the baud rate
}

void loop()
{
  // SERIAL IN FROM COMPUTER TO ARDUINO:
  if (Serial.available()) {
     // look for the next valid integer in the incoming serial stream:
    x = Serial.parseInt();
    // do it again:
    y = Serial.parseInt();
    // do it again:
    v = Serial.parseInt();
    if (Serial.read() == '\n') {
      Serial.println("got it!");
    }
  }

    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.println(v);

}

