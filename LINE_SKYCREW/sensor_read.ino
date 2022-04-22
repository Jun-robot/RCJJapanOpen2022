int analog_value[sensor_num];
int digital_value[sensor_num];
float line_angle;

int green_sensor_num;

int get_angle() {
  int a;
  if (line_angle != 0) {
    a = line_angle;
  } else {
    a = 0;
  }
  return a;
}





int sensor_cal() {//16で作るので32だとだめかもしれない
  int green_sensor_id[green_sensor_num];//0の範囲を記録する
  int a = 0;
  for (int i = 0; i < sensor_num; i++) {
    if (digital_value[i] == 0) {
      green_sensor_id[a] = i;
      a++;
    }
  }

  //  Serial.print(green_sensor_num);
  //  Serial.print("  ");

  if (green_sensor_num != sensor_num) {
    //センサー反応してるよ
    int cont_num[green_sensor_num][2];//[初めのID][連続した数]
    for (int i = 0; i < green_sensor_num; i++) {
      cont_num[i][0] = 0;
      cont_num[i][1] = 0;
    }

    int hika = 0;

    cont_num[0][0] = green_sensor_id[0];

    for (int i = 0; i < green_sensor_num; i++) {

      if (green_sensor_id[i] + 1 == green_sensor_id[i + 1]) {
        //        Serial.print("a");
        cont_num[hika][1] += 1;
        //0指定できてない

      } else {
        //        Serial.print("b");
        if (i + 1 < green_sensor_num) {
          hika += 1;
          cont_num[hika][0] = green_sensor_id[i + 1];
        }
      }
      //      Serial.print(green_sensor_id[i]);
      //      Serial.print(": ");
    }

    if (cont_num[hika][0] + cont_num[hika][1] == 15 && cont_num[0][0] == 0) {
      //最後と最初をつなげる
      cont_num[0][0] = cont_num[hika][0] ;
      cont_num[0][1] += cont_num[hika][1] + 1;
      cont_num[hika][0] = 0;
      cont_num[hika][1] = 0;
    }

    //-------------------------

    Serial.println();

    for (int i = 0; i < green_sensor_num; i++) {
      Serial.print(cont_num[i][0]);
      Serial.print(" ");
      Serial.print(cont_num[i][1]);
      Serial.print("  ");
    }

    int best_cout = -1;
    int best_cout_id = -1;

    for (int i = 0; i < green_sensor_num; i++) {
      best_cout = max(best_cout , cont_num[i][1]);
      if (best_cout == cont_num[i][1]) {
        best_cout_id = i;
      }
    }
    Serial.println();
    Serial.print(best_cout );
    Serial.print( " ");
    Serial.print(best_cout_id);

    line_angle = (cont_num[best_cout_id][0] + (cont_num[best_cout_id][1] / 2)) * 22.5;
    if (line_angle > 360.00) {
      line_angle -= 360;
    }
    Serial.print( " ");
    Serial.print(line_angle);



  } else {
    //ラインなし
    line_angle = 0;
  }

  Serial.println();

}











void debug() {
  for (int id = 0; id < sensor_num; id++) {
    Serial.print(id);
    Serial.print("=");
    Serial.print(analog_value[id]);
    Serial.print(":");
    Serial.print(digital_value[id]);
    Serial.print(" ");
  }
  Serial.println("");
}


void sensor_convert() {
  green_sensor_num = 0;
  for (int id = 0; id < sensor_num; id++) {
    if (analog_value[id] >= C_line_threshold) {
      digital_value[id] = 1;
    } else {
      digital_value[id] = 0;
      green_sensor_num++;
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
