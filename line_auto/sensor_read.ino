#include <EEPROM.h>

int analog_value[sensor_num];
int digital_value[sensor_num];
float line_angle;

int LINE_THRESHOLD[16];

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

    //    Serial.println();

    //    for (int i = 0; i < green_sensor_num; i++) {
    //      Serial.print(cont_num[i][0]);
    //      Serial.print(" ");
    //      Serial.print(cont_num[i][1]);
    //      Serial.print("  ");
    //    }

    int best_cout = -1;
    int best_cout_id = -1;

    for (int i = 0; i < green_sensor_num; i++) {
      best_cout = max(best_cout , cont_num[i][1]);
      if (best_cout == cont_num[i][1]) {
        best_cout_id = i;
      }
    }
    //    Serial.println();
    //    Serial.print(best_cout );
    //    Serial.print( " ");
    //    Serial.print(best_cout_id);

    line_angle = (cont_num[best_cout_id][0] + (cont_num[best_cout_id][1] / 2)) * 22.5;
    if (line_angle > 360.00) {
      line_angle -= 360;
    }
    //    Serial.print( " ");
    //    Serial.print(line_angle);



  } else {
    //ラインなし
    line_angle = 0;
  }

  //  Serial.println();

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
    if (analog_value[id] >=  LINE_THRESHOLD[id]) {
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
  for (int i = 0; i < 16; i++) {
    LINE_THRESHOLD[i] = EEP_READ(i);
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























unsigned long finish_time;
int THRESHOULD[16];

void auto_threshould() {
  int read_num = 0;
  int analog_max[16];
  int analog_min[16];

  for (int i; i < 16; i++) {
    analog_max[i] = 0;
    analog_min[i] = 800;
  }


  F_time_read();
  finish_time = F_time_goal(10000);

  while (finish_time > F_time_get()) {
    sensor_read();
    read_num ++;
    for (int i = 0; i < 16; i++) {
      analog_max[i] = max(analog_max[i], analog_value[i]);
      analog_min[i] = min(analog_min[i], analog_value[i]);
    }
    F_time_read();
  }

  for (int i = 0; i < 16; i++) {
    THRESHOULD[i] = analog_min[i] + ((analog_max[i] - analog_min[i]) / 3 * 2);
  }




  Serial.println("------------------");
  Serial.println("");
  Serial.print("num :");
  Serial.print(read_num);
  for (int i; i < 16; i++) {
    Serial.print(i);
    Serial.print(" max :");
    Serial.print(analog_max[i]);
    Serial.print(" min :");
    Serial.print(analog_min[i]);
    Serial.print(" thr :");
    Serial.print(THRESHOULD[i]);

    EEP_WRITE(i, THRESHOULD[i]);

    Serial.println();
  }
  Serial.println("");
  Serial.println("------------------");
}

void EEP_WRITE(int id, int num) {
  if (id == 0) {
    EEPROM.put(0x000, num);
  } else if (id == 1) {
    EEPROM.put(0x002, num);
  } else if (id == 2) {
    EEPROM.put(0x004, num);
  } else if (id == 3) {
    EEPROM.put(0x006, num);
  } else if (id == 4) {
    EEPROM.put(0x008, num);
  } else if (id == 5) {
    EEPROM.put(0x00A, num);
  } else if (id == 6) {
    EEPROM.put(0x00C, num);
  } else if (id == 7) {
    EEPROM.put(0x00E, num);
  } else if (id == 8) {
    EEPROM.put(0x010, num);
  } else if (id == 9) {
    EEPROM.put(0x012, num);
  } else if (id == 10) {
    EEPROM.put(0x014, num);
  } else if (id == 11) {
    EEPROM.put(0x016, num);
  } else if (id == 12) {
    EEPROM.put(0x018, num);
  } else if (id == 13) {
    EEPROM.put(0x01A, num);
  } else if (id == 14) {
    EEPROM.put(0x01C, num);
  } else if (id == 15) {
    EEPROM.put(0x01E, num);
  }
}

int EEP_READ(int id) {
  int myreturn;
  if (id == 0) {
    EEPROM.get(0x000, myreturn);
  } else if (id == 1) {
    EEPROM.get(0x002, myreturn);
  } else if (id == 2) {
    EEPROM.get(0x004, myreturn);
  } else if (id == 3) {
    EEPROM.get(0x006, myreturn);
  } else if (id == 4) {
    EEPROM.get(0x008, myreturn);
  } else if (id == 5) {
    EEPROM.get(0x00A, myreturn);
  } else if (id == 6) {
    EEPROM.get(0x00C, myreturn);
  } else if (id == 7) {
    EEPROM.get(0x00E, myreturn);
  } else if (id == 8) {
    EEPROM.get(0x010, myreturn);
  } else if (id == 9) {
    EEPROM.get(0x012, myreturn);
  } else if (id == 10) {
    EEPROM.get(0x014, myreturn);
  } else if (id == 11) {
    EEPROM.get(0x016, myreturn);
  } else if (id == 12) {
    EEPROM.get(0x018, myreturn);
  } else if (id == 13) {
    EEPROM.get(0x01A, myreturn);
  } else if (id == 14) {
    EEPROM.get(0x01C, myreturn);
  } else if (id == 15) {
    EEPROM.get(0x01E, myreturn);
  }
  return myreturn;
}
