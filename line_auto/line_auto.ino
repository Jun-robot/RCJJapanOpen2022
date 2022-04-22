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
  Serial.begin(115200);
  LINESer.begin(115200);
  pinMode(10, OUTPUT); //ソフトシリアル頑張ってくれ、、

  sensor_setup();
  FullLED_setup();
  for (int r = 0; r < 150; r++) {
    FullLED_loop(r, 150 - r, 0);
    delay(5);
  }
  auto_threshould();
}

int pre_GET_angle;
int GET_angle;
unsigned long line_time;

void loop() {
  FullLED_loop(255, 1, 1);

  sensor_read(); //まずは読み込むよ！
  sensor_convert(); // デジタルに変換するよ！
  debug(); // デバッグ用に出力
  Serial.println("");


  sensor_cal(); //
  GET_angle = get_angle();





  Serial.println("");
  Serial.println("--------------------------------------------");
  Serial.println("");

  // ラインが見えなくなっても一定時間は進もう！！
//  if (GET_angle != 0) {
//    line_time = F_time_goal(100);
//  }
//  if (GET_angle == 0 && line_time > F_time_get()) {
//    GET_angle = pre_GET_angle;
//  }
  LINESer.write(GET_angle / 2);
  LINESer.flush();

  pre_GET_angle = GET_angle;

  Serial.print("                                                                           ");
  Serial.println(GET_angle);
  Serial.println();




  //  int pre_range[2];
  //  pre_range[0] = pre_GET_angle + 110;
  //  pre_range[1] = pre_GET_angle + 250;
  //  for (int i; i < 2; i++) {
  //    if (pre_range[i] > 360) {
  //      pre_range[i] -= 360;
  //    }
  //    Serial.print("aaa");
  //    Serial.print(pre_range[i]);
  //  }
  //
  //  pre_GET_angle = GET_angle;
  //
  //
  //  LINESer.write(GET_angle / 2);
  //  LINESer.flush();
}
