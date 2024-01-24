int LINE_receive;
int pre_LINE_receive;

//bool isOut = 0;//  外にいるとき1にする

void F_LINE_setup() {
  Serial1.begin(115200);
}

unsigned long line_force_time = 0;

void F_LINE_read() {


  while (Serial1.available() > 5) {
    int g = Serial1.read();
  }
  if (Serial1.available() > 0) {
    LINE_receive = Serial1.read() * 2;
    if (LINE_receive > 0) {
      LINE_receive = F_360_correct(LINE_receive);
    }
  }
  if (pre_LINE_receive != 0 && LINE_receive != 0) {
    if (range_check(pre_LINE_receive + 110, pre_LINE_receive + 250, LINE_receive)) {
      LINE_receive += 180;
      if (LINE_receive > 360) {
        LINE_receive -= 360;
      }
    }
  }

  if (LINE_receive == 360) {
    LINE_receive = 359;
  }

  pre_LINE_receive = LINE_receive;
}

void F_LINE_read_block() {
  while (Serial1.available() > 5) {
    int g = Serial1.read();
  }
  if (Serial1.available() > 0) {
    LINE_receive = Serial1.read() * 2;
    if (LINE_receive > 0) {
      LINE_receive = F_360_correct(LINE_receive);
    }
  }
}


int F_LINE_get() {
  return LINE_receive;
}

void F_LINE_debug() {
  Serial.print(" LINE:");
  Serial.print(LINE_receive);
}


void F_LINE_threshold() {
  Serial1.write(100);
  delay(1);
  Serial1.write(100);
  delay(1);
  Serial1.write(100);
  F_BUZ_DarthVader();



}
