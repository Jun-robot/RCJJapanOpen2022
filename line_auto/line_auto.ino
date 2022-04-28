#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

SoftwareSerial LINESer(10, 11); //rx,tx

const int FullLED_PIN = 5;
const int FullLED_NUM = 32;
Adafruit_NeoPixel FullLED(FullLED_NUM, FullLED_PIN, NEO_GRB + NEO_KHZ800);

const int CHOICE_PIN[] = {2, 3, 4};
const int READ_PIN[] = {A0, A1, A2, A3};

const int sensor_num = 16; //16or32
const int C_line_threshold = 250;

void setup() {
//  Serial.begin(115200);
  LINESer.begin(115200);
  pinMode(10, INPUT); //ソフトシリアル頑張ってくれ、、
  //  pinMode(11)

  sensor_setup();
  FullLED_setup();
  for (int r = 0; r < 150; r++) {
    FullLED_loop(r, 150 - r, 0);
    delay(5);
  }
  FullLED_loop(255, 1, 1);


  //
  //  auto_threshould();


  for (int i = 0; i < 16; i++) {
    Serial.print(i);
    Serial.print(" ");
    Serial.println(EEP_READ(i));
  }
}

int pre_GET_angle;
int GET_angle;
unsigned long line_time;

void loop() {
//  while (LINESer.available() > 5) {
//    int g = LINESer.read();
//  }
  if (LINESer.available() > 0) {
    if (LINESer.read() == 100) {
      for (int g = 0; g < 10; g++) {
        FullLED_loop(1, 255, 200);
        delay(150);
        FullLED_loop(0, 0, 0);
        delay(150);
      }

      FullLED_loop(255, 1, 1);
      auto_threshould();

      for (int g = 0; g < 10; g++) {
        FullLED_loop(255, 200, 0);
        delay(150);
        FullLED_loop(0, 0, 0);
        delay(150);
      }
      while (LINESer.available() > 0) {
        int g = LINESer.read();
      }
    }
  }


  FullLED_loop(255, 1, 1);

  sensor_read(); //まずは読み込むよ！
  sensor_convert(); // デジタルに変換するよ！
  debug(); // デバッグ用に出力
  //  Serial.println("");


  sensor_cal(); //
  GET_angle = get_angle();





  //  Serial.println("");
  //  Serial.println("--------------------------------------------");
  //  Serial.println("");

  LINESer.write(GET_angle / 2);
  LINESer.flush();

  pre_GET_angle = GET_angle;

  Serial.print("                                                                           ");
  Serial.println(GET_angle);
  Serial.println();

}
