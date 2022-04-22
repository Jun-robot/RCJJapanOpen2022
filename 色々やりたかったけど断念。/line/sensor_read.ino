int analog_value[sensor_num];
int digital_value[sensor_num];
float line_angle;

int get_angle() {
  int a;
  if (line_angle != 0) {
    a = line_angle;
  } else {
    a = 0;
  }
  return a;
}


bool sensor_check() {
  bool a = 0;
  for (int id = 0; id < sensor_num; id++) {
    if (digital_value[id] == 1) {
      a = 1;
    }
  }

  return a;
}


int sensor_cal() {//16で作るので32だとだめかもしれない
  int sensor_cont[sensor_num][2];//0の範囲を記録する
  int cout_num = 0;
  for (int id = 0; id < sensor_num; id++) {
    sensor_cont[id][0] = -1;
    sensor_cont[id][1] = -1;


    if (digital_value[id] > digital_value[id + 1]) {
      //今回が1　次回が0
      sensor_cont[cout_num][0] = id + 1;
    } else if (digital_value[id] < digital_value[id + 1]) {
      //今回が0　次回が1
      sensor_cont[cout_num][1] = id;
      cout_num++;
    }
  }

  cout_num -= 1; //入ってる数。

  if (sensor_cont[cout_num][0] == -1) {
    sensor_cont[cout_num][1] = -1;
  }
  else if (sensor_cont[0][0] == -1) {
    sensor_cont[0][0] = sensor_cont[cout_num][0];
    sensor_cont[0][1] += 16;
    sensor_cont[cout_num][0] = -1;
    sensor_cont[cout_num][1] = -1;
    cout_num -= 1;
  }

  for (int id = 0; id < sensor_num; id++) {
    Serial.print(sensor_cont[id][0]);
    Serial.print(":");
    Serial.print(sensor_cont[id][1]);
    Serial.print(" ");
  }
  Serial.println(" ");


//  if (sensor_cont[0][1] != -1) {
//    int range[cout_num + 1];
//    float max_range = -1;
//    int max_id = -1;
//
//    for (int n = 0; n <= cout_num ; n++) {
//      if (sensor_cont[n][0] <= sensor_cont[n][1]) {
//        range[n] = sensor_cont[n][1] - sensor_cont[n][0];
//      } else {
//        range[n] = (sensor_num - sensor_cont[n][0]) + sensor_cont[n][1];
//      }
//      Serial.print(range[n]);
//      Serial.print(" ");
//
//      max_range = max(max_range, range[n]);
//      if (max_range == range[n]) {
//        max_id = n;
//      }
//    }
//
//    Serial.print("|");
//    Serial.print(max_id);
//    Serial.print("|");
//    Serial.print(max_range);
//    Serial.print("|  ");
//
//    Serial.print(sensor_cont[max_id][0] + (max_range / 2));
//    Serial.print("  |  ");
//
//    line_angle = (sensor_cont[max_id][0] + (max_range / 2)) * 22.5;
//
//  }
//
//  if (line_angle > 360) {
//    line_angle -= 360;
//
//  }
//  else if (line_angle < 0) {
//    for (int id = 0; id < sensor_num; id++) {
//      if (digital_value[id] == 1) {
//        line_angle = id * 22.5;
//        goto aaaa;
//      }
//      line_angle = 0;
//    }
//aaaa:;
//  }
//
//  Serial.print(line_angle);

  Serial.println();
}




















void debug() {
  for (int id = 0; id < sensor_num; id++) {
    Serial.print(id);
    Serial.print("=");
    //    Serial.print(analog_value[id]);
    //    Serial.print(":");
    Serial.print(digital_value[id]);
    Serial.print(" ");
  }
  Serial.println("");
}


void sensor_convert() {
  for (int id = 0; id < sensor_num; id++) {
    if (analog_value[id] >= C_line_threshold) {
      digital_value[id] = 1;
    } else {
      digital_value[id] = 0;
    }
  }
}

void sensor_setup() {
  for (int id = 0; id < 3; id++) {
    pinMode(CHOICE_PIN[id], OUTPUT);
  }
  for (int id = 0; id < 4; id++) {
    pinMode(READ_PIN[id], INPUT);
  }
}


void sensor_read() { //全部のセンサーを読んで変数に突っ込むよ
  if (sensor_num == 32) {
    for (int id = 0; id < 8; id++) {
      sensor_choice(id);
      analog_value[id] = analogRead(READ_PIN[0]); //0-7
      analog_value[id + 8] = analogRead(READ_PIN[1]); //8-15
      analog_value[id + 16] = analogRead(READ_PIN[2]); //15-23
      analog_value[id + 24] = analogRead(READ_PIN[3]); //24-31
    }
  } else if (sensor_num == 16) {
    int hikakin_value[32];
    for (int id = 0; id < 8; id++) {
      sensor_choice(id);
      hikakin_value[id] = analogRead(READ_PIN[0]); //0-7
      hikakin_value[id + 8] = analogRead(READ_PIN[1]); //8-15
      hikakin_value[id + 16] = analogRead(READ_PIN[2]); //15-23
      hikakin_value[id + 24] = analogRead(READ_PIN[3]); //24-31
    }
    for (int id = 0; id < 32; id += 2) {
      analog_value[id / 2] = hikakin_value[id];
    }
  }
}


void sensor_choice(int sensor_num) {
  int choice_output[3];
  switch (sensor_num) {
    case 0:
      choice_output[2] = 0;
      choice_output[1] = 0;
      choice_output[0] = 0;
      break;
    case 1:
      choice_output[2] = 0;
      choice_output[1] = 0;
      choice_output[0] = 1;
      break;
    case 2:
      choice_output[2] = 0;
      choice_output[1] = 1;
      choice_output[0] = 0;
      break;
    case 3:
      choice_output[2] = 0;
      choice_output[1] = 1;
      choice_output[0] = 1;
      break;
    case 4:
      choice_output[2] = 1;
      choice_output[1] = 0;
      choice_output[0] = 0;
      break;
    case 5:
      choice_output[2] = 1;
      choice_output[1] = 0;
      choice_output[0] = 1;
      break;
    case 6:
      choice_output[2] = 1;
      choice_output[1] = 1;
      choice_output[0] = 0;
      break;
    case 7:
      choice_output[2] = 1;
      choice_output[1] = 1;
      choice_output[0] = 1;
      break;
      //default:
  }

  if (choice_output[2] == 1) {
    digitalWrite(CHOICE_PIN[2], HIGH);
  } else {
    digitalWrite(CHOICE_PIN[2], LOW);
  }

  if (choice_output[1] == 1) {
    digitalWrite(CHOICE_PIN[1], HIGH);
  } else {
    digitalWrite(CHOICE_PIN[1], LOW);
  }

  if (choice_output[0] == 1) {
    digitalWrite(CHOICE_PIN[0], HIGH);
  } else {
    digitalWrite(CHOICE_PIN[0], LOW);
  }
}
