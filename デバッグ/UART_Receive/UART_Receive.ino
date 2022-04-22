//void setup() {
//  Serial.begin(115200);
//  Serial1.begin(115200);
//  //pinMode(8, INPUT);
//
//}
//
//void loop() {
//  if (Serial1.available()) {
//    Serial.write(Serial1.read());
//  }
//}


#include <SoftwareSerial.h>
//SoftwareSerial mySerial(66, 69); // RX, TX

void setup() {
  Serial.begin(115200);
  Serial1.begin(19200);
  pinMode(8, INPUT);

}

void loop() {
  if (Serial1.available()) {
    byte byteRead = Serial1.read();
    Serial.println(byteRead);
  }

}
