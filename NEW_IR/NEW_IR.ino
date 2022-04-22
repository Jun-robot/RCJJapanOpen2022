#include <SoftwareSerial.h>
SoftwareSerial IRSerial(23, 53); // RX, TX

const int IR_PIN[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
const int LED_PIN[] = {20, 21};
const int LED_CIRCLE0[] = {30, 31, 32, 33, 34, 35, 36, 37};
const int LED_CIRCLE1[] = {40, 41, 42, 43, 44, 45, 46, 47};
const float sine[] = {0, 0.38268, 0.70711, 0.92388, 1, 0.92388, 0.70711, 0.38268, 0, -0.38268, -0.70711, -0.92388, -1, -0.92388, -0.70711, -0.38268};
const float cosine[] = {1, 0.92388, 0.70711, 0.38268, 0, -0.38268, -0.70711, -0.92388, -1, -0.92388, -0.70711, -0.38268, 0, 0.38268, 0.70711, 0.92388};
const int mytimeout = 1725;

int degree;
int distance;
int pre_degree;
int pre_distance;


void setup() {
  Serial.begin(115200);
  IRSerial.begin(115200);
  pinMode(10, OUTPUT);
  for (int id = 0; id <= 2; id++) {
    pinMode(LED_PIN[id], OUTPUT);
    digitalWrite(LED_PIN[id], HIGH);
  }
  for (int id = 0; id <= 7; id++) {
    pinMode(LED_CIRCLE0[id], OUTPUT);
    pinMode(LED_CIRCLE1[id], OUTPUT);
    //    digitalWrite(LED_CIRCLE2[id], HIGH);
  }
  for (int id = 0; id <= 15; id++) {
    pinMode(IR_PIN[id], INPUT);
  }

  LED_kidou();
}


unsigned long mytime;

void loop() {
  int duration[16];
  int pulse[16];
  int pre_duration[16];
  int best_id = 0;
  int best_duration = 0;

  //値取得
  for (int i = 0; i < 16; i++) {
    pulse[i] = 0;
  }
  const unsigned long startTime = micros();
  do {
    for (int i = 0; i < 16; i++) {
      if (digitalGet(i) == false) {
        pulse[i] += 5;
      }
    }
  } while ((micros() - startTime) < 833);

  //計算
  for (int id = 0; id < 16; id++) {
    duration[id] = pulse[id] * 0.6 + pre_duration[id] * 0.4;
    //    duration[id] = pulseIn(IR_PIN[id], LOW, mytimeout) * 0.5 + pre_duration[id] * 0.5;
    if (id == 0) {
      duration[0] *= 1.12;
    }
    pre_duration[id] = duration[id];

    best_duration = max(best_duration, duration[id]);
    if (best_duration == duration[id]) {
      best_id = id;
    }
    //    Serial.print(duration[id]);
    //    Serial.print(",");
  }

//  Serial.print(" id:");
//  Serial.print(best_id);
//  Serial.print(" dur:");
//  Serial.print(best_duration);

  if (best_duration > 0) {
    //ボールがあったとき
    int read_id[5];
    int x_axis = 0;
    int y_axis = 0;
    read_id[0] = best_id - 2;
    read_id[1] = best_id - 1;
    read_id[2] = best_id;
    read_id[3] = best_id + 1;
    read_id[4] = best_id + 2;
    for (int i = 0; i < 5; i++) {
      if (read_id[i] > 15) {
        read_id[i] -= 16;
      }
      if (read_id[i] < 0) {
        read_id[i] += 16;
      }

      x_axis += duration[read_id[i]] * cosine[read_id[i]];
      y_axis += duration[read_id[i]] * sine[read_id[i]];

    }

    degree = (atan2((y_axis), (x_axis)) * 180 / PI);
    if (degree > 360) {
      degree -= 360;
    } else if (degree < 1) {
      degree += 360;
    }

    //ここから長さ

    if (best_duration > 37) {
      //一番近い
      distance = 1;
    } else if (best_duration > 27) {
      //真ん中位
      distance = 2;
    } else if (best_duration > 0) {
      //遠い
      distance = 3;
    }


  } else {
    //ボールがなかった時
    degree = 0;
    distance = 0;
  }
  
  //ローパスフィルタ
  if (pre_degree != 0 && degree != 0) {
    if (pre_degree > 250 && degree < 70) {
      degree += 360;
    } else if (degree > 250 && pre_degree < 70) {
      pre_degree += 360;
    }
    degree = degree * 0.3 + pre_degree * 0.7;

    if (degree > 360) {
      degree -= 360;
    }
  }

//  if (pre_distance != 0 && distance != 0) {
//    distance = (distance * 0.9) + (pre_distance * 0.1);
//  }

  uint8_t deg = degree / 1.5;
  uint8_t dis = distance;

//  Serial.print(" deg:");
//  Serial.print(degree);
//  Serial.print(" dis:");
//  Serial.print(distance);

  IRSerial.write(255); //header
  IRSerial.write(deg);
  IRSerial.write(dis);
  IRSerial.flush();

  kakudo_led(degree);
  kyori_led(distance);



  pre_degree = degree;
  pre_distance = distance;

  //時間計測
  Serial.print(" //");
  unsigned long now = micros();
  Serial.println(now - mytime);
  mytime = now;

}



bool digitalGet(uint8_t pin) {
  switch (pin) {
    case 0:   return PINE & (1 << 4);
    case 1:   return PINE & (1 << 5);
    case 2:   return PING & (1 << 5);
    case 3:   return PINE & (1 << 3);
    case 4:   return PINH & (1 << 3);
    case 5:   return PINH & (1 << 4);
    case 6:   return PINH & (1 << 5);
    case 7:   return PINH & (1 << 6);
    case 8:   return PINB & (1 << 4);
    case 9:   return PINB & (1 << 5);
    case 10:  return PINB & (1 << 6);
    case 11:  return PINB & (1 << 7);
    case 12:  return PINJ & (1 << 1);
    case 13:  return PINJ & (1 << 0);
    case 14:  return PINH & (1 << 1);
    case 15:  return PINH & (1 << 0);
  }
}
