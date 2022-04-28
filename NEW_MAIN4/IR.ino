int IR_receive = 0;
int IR_distance = 0;
int IR_camera = 0;

void F_IR_setup() {
  Serial3.begin(115200);
}

void F_IR_read() {
  //  while (Serial3.available() > 5) {
  //    int g = Serial3.read();
  //  }
  //  if (Serial3.available() > 0) {
  //    IR_receive = Serial3.read() * 2;
  //  }

  while (Serial3.available() > 8) {
    int g = Serial3.read();
  }

modoru:
  uint8_t data = (uint8_t)Serial3.read();
  if (data == 0xFF) {
    uint8_t deg = Serial3.read();
    uint8_t dis = Serial3.read();
    uint8_t cam = Serial3.read();

        Serial.print("   ");
        Serial.print(deg);
        Serial.print(" ");
        Serial.print(dis);
        Serial.print(" ");
        Serial.print(cam);
        Serial.print("  ");

    //----------------------------
    if (deg != 255) {
      IR_receive = deg * 1.5;
    }
    if (dis != 255) {
      IR_distance = dis;
    }
    if (cam != 255) {
      IR_camera = cam * 1.5;
    }
    //----------------------------

  } else {
    goto modoru;
  }
}


int F_IR_get() {
  return IR_receive;
}

int F_IR_camera() {
  return IR_camera;
}

void F_IR_debug() {
  Serial.print(" IR:");
  Serial.print(IR_receive);
}


int F_IR_wrap_around(int IR) {
  //IR -= 1;
  //const int C_IR_length = 16.25; //距離が500時、16.25°。距離がxの時、arcsin(140 / x)°
  int IR_wrap_degree;

  if (IR_distance == 0) {
    IR_wrap_degree = 0;
  } else if (IR_distance == 1 || IR_distance == 2) {
    IR_wrap_degree = F_IR_mawarikomi(IR, 65);
  } else if (IR_distance == 3) {
    IR_wrap_degree = F_IR_mawarikomi_mae(IR, 35);
  }
  return IR_wrap_degree;
}



int F_IR_mawarikomi(int IR, int leng) {
  const int C_IR_length = leng; //300mm

  int result;
  //回り込み
  if (IR == 0) {
    result = 0;
  } else if ((25 >= IR || IR >= 335) ) {
    result = 360;
  } else if ((25 <= IR && IR <= 25) ) {
    result = 5;
  } else if ((25 <= IR && IR <= 70) ) {
    result = IR + 70;

  } else if (70 <= IR && IR <= 180) {
    result = IR + C_IR_length ;

  } else if ( 180 <= IR && IR <= 290 ) {
    result = IR - C_IR_length;

  } else if ((290 <= IR && IR <= 335) ) {
    result = IR - 70;

  } else if ( 335 <= IR && IR <= 335 ) {
    result = 355;
  }
  return result;
}

int F_IR_mawarikomi_mae(int IR, int leng) {
  const int C_IR_length = leng; //300mm

  int result;
  //回り込み
  if (IR == 0) {
    result = 0;
  } else if ((30 >= IR || IR >= 330) ) {
    result = 360;
  } else if ((30 <= IR && IR <= 45) ) {
    result = 65;
  } else if ((45 <= IR && IR <= 70) ) {
    result = IR + 70;

  } else if (70 <= IR && IR <= 180) {
    result = IR + C_IR_length ;

  } else if ( 180 <= IR && IR <= 290 ) {
    result = IR - C_IR_length;

  } else if ((290 <= IR && IR <= 315) ) {
    result = IR - 70;

  } else if ( 315 <= IR && IR <= 330 ) {
    result = 295;
  }
  return result;
}
