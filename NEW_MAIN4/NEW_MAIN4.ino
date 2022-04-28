int toggle = 41;
int select0 = 37;
int select1 = 39;

void setup() {
  all_reset();
  //↑リセットします！！！！
  Serial.begin(115200);


  F_MD_setup();
  F_ESP_setup();
  F_GYRO_setup();
  F_KICCER_SETUP();
  F_LINE_setup();
  F_IR_setup();

  F_BUZ_setup();
  F_BUZ_frog();
  pinMode(toggle, INPUT);//トグルスイッチ
  pinMode(30, OUTPUT);//LED
  pinMode(31, OUTPUT);//LED
  pinMode(select0, INPUT);
  pinMode(select1, INPUT);
  delay(1000);
}

int tilt = 0;
int nnn = 0;

void loop() {
  F_ESP_read();
  F_KICCER_loop();
  F_time_read();
  F_GYRO_read();
  F_LINE_read();
  F_IR_read();


  if (digitalRead(select0) == 0 && digitalRead(select1) == 0) {
    //赤、赤　-> アタッカーモード
    if (digitalRead(toggle) == 0) {
      digitalWrite(31, LOW);
      if (F_KICCER_judge_V2() == 1) {
        F_KICCER_kick();
      }

      int GYRO_DEGDEG = F_360_correct(F_GYRO_get() - tilt);
      int GO_DEGDEG;
      int SPEED_PEDPED;
      if (F_LINE_get() > 0) {
        Serial.print('_');
        GO_DEGDEG = F_360_correct(F_LINE_get() + F_GYRO_get());
        SPEED_PEDPED = 255;
      } else {
        Serial.print('*');
        if (F_IR_get()  != 0) {
          GO_DEGDEG = F_IR_wrap_around(F_360_correct(F_IR_get() + F_GYRO_get()));
          SPEED_PEDPED = 255;
        } else {
          GO_DEGDEG = 180;
          SPEED_PEDPED = 50;
        }
      }

      Serial.print(" go:");
      Serial.print(GO_DEGDEG);

      if (GO_DEGDEG != 0) {
        GO_DEGDEG = F_360_correct(GO_DEGDEG  - F_GYRO_get());
      } else {
        GO_DEGDEG = 0;
      }


      F_MD_rotate(GO_DEGDEG, GYRO_DEGDEG, SPEED_PEDPED);



    } else {
      digitalWrite(31, HIGH);

      //      if (F_KICCER_judge_V2() == 1 || F_ESP_switch() == 3) {
      //        F_KICCER_kick();
      //      }
      //      if (F_ESP_switch() == 4) {
      //        tilt += 15;
      //      }
      //      if (F_ESP_switch() == 1) {
      //        tilt = 0;
      //      }
      //      if (F_ESP_switch() == 2) {
      //        tilt -= 15;
      //      }
      //
      //      int GYRO_DEGDEG = F_360_correct(F_GYRO_get() - tilt);
      //      int GO_DEGDEG;
      //
      //      if (F_ESP_angle() != 0) {
      //        GO_DEGDEG = F_360_correct(F_ESP_angle()  - F_GYRO_get());
      //      } else {
      //        GO_DEGDEG = 0;
      //      }
      //
      //      F_MD_rotate(GO_DEGDEG, GYRO_DEGDEG, map(F_ESP_speed(), 0, 100, 40, 254));
      F_MD_rotate(0, 0, 0);
    }

    F_GYRO_debug();
    F_LINE_debug();
    F_IR_debug();
    F_KICCER_debug();

    F_MD_debug();

    Serial.println();
  } else if (digitalRead(select0) == 1 && digitalRead(select1) == 1) {
    //青、青　-> ライン閾値調整モード
    F_MD_rotate(0, 0, 0);
    if (digitalRead(toggle) == 0) {
      F_LINE_threshold();
      Serial.println("okuttayoooooooooooooooooooooooooooooooooooooooooooooo");
    }

  } else if (digitalRead(select0) == 0 && digitalRead(select1) == 1) {
    //赤、青　-> ブロッカーモード
    if (digitalRead(toggle) == 0) {
      digitalWrite(30, LOW);
      Serial.println(F_IR_camera());

      // -----------------------------------------------

      if (F_KICCER_judge_V2() == 1) {
        F_KICCER_kick();
      }

      int GYRO_DEGDEG = F_360_correct(F_GYRO_get() - tilt);
      int GO_DEGDEG;
      int SPEED_PEDPED;
      if (F_LINE_get() > 0) {
        Serial.print('_');
        if (80 < F_LINE_get() + F_GYRO_get() && F_LINE_get() + F_GYRO_get()  < 100) {
          GO_DEGDEG = F_360_correct(50 + F_GYRO_get());
        } else  if (260 < F_LINE_get() + F_GYRO_get() && F_LINE_get() + F_GYRO_get()  < 280) {
          GO_DEGDEG = F_360_correct(310 + F_GYRO_get());
        } else {
          GO_DEGDEG = F_360_correct(F_LINE_get() + F_GYRO_get());
        }
        SPEED_PEDPED = 255;
      } else if (F_IR_camera() > 0) {
        Serial.print('@');
        GO_DEGDEG = F_360_correct(F_IR_camera() + F_GYRO_get());
        SPEED_PEDPED = 255;
      } else {
        Serial.print('*');
        if (F_IR_get()  != 0) {
          int aa = F_360_correct(F_IR_get() + F_GYRO_get());
          if (345 < aa || aa < 15) {
            GO_DEGDEG = 0;
          } else if (15 <= aa && aa < 80) {
            GO_DEGDEG = 85;
          } else if (80 <= aa && aa < 180) {
            GO_DEGDEG = 100;
//          } else if (130 <= aa && aa < 220) {
//            GO_DEGDEG = F_IR_wrap_around(aa);
          } else if (180 <= aa && aa < 280) {
            //            GO_DEGDEG = 270;
            GO_DEGDEG = 260;
          } else if (280 <= aa && aa <= 345) {
            //            GO_DEGDEG = 275;
            GO_DEGDEG = 260;
          }

          SPEED_PEDPED = 255;
        } else {
          GO_DEGDEG = 180;
          //          SPEED_PEDPED = 50;
          SPEED_PEDPED = 0;
        }
      }

      Serial.print(" go:");
      Serial.print(GO_DEGDEG);
      Serial.print("  ");

      if (GO_DEGDEG != 0) {
        GO_DEGDEG = F_360_correct(GO_DEGDEG  - F_GYRO_get());
      } else {
        GO_DEGDEG = 0;
      }


      F_MD_rotate(GO_DEGDEG, GYRO_DEGDEG, SPEED_PEDPED);



      // ----------------------------------------------
    } else {
      digitalWrite(30, HIGH);
      F_MD_rotate(0, 0, 0);
    }

  } else if (digitalRead(select0) == 1 && digitalRead(select1) == 0) {
    //青、赤　-> モード
    F_MD_rotate(0, 0, 0);
    if (digitalRead(toggle) == 0) {

    }

  }
}
