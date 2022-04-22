
void LED_kidou() {
  for (int y = 0; y < 2; y++) {
    for (int i = 0 ; i < 8; i++) {
      LED_shine(0, i);
      int aaaa;
      if (i == 0) {
        aaaa = 0;
      } else {
        aaaa = 8 - i;
      }
      LED_shine(1, aaaa);
      delay(50);
    }
  }
  LED_shine(0, 8);
  LED_shine(1, 8);
  delay(100);
  LED_shine(0, 9);
  LED_shine(1, 9);
  delay(100);
  LED_shine(0, 8);
  LED_shine(1, 8);
  delay(100);
  LED_shine(0, 9);
  LED_shine(1, 9);
  delay(300);

}


void LED_shine(int circle, int num) {
  int MYLED[8];

  for (int id = 0; id <= 7; id++) {
    if (circle == 0) {
      MYLED[id] = LED_CIRCLE0[id];
    } else if (circle == 1) {
      MYLED[id] = LED_CIRCLE1[id];
    }
    digitalWrite(MYLED[id], LOW);
  }
  if (num == 0) {
    digitalWrite(MYLED[0] , HIGH);
  } else if (num == 1) {
    digitalWrite(MYLED[1] , HIGH);
  } else if (num == 2) {
    digitalWrite(MYLED[2] , HIGH);
  } else if (num == 3) {
    digitalWrite(MYLED[3] , HIGH);
  } else if (num == 4) {
    digitalWrite(MYLED[4] , HIGH);
  } else if (num == 5) {
    digitalWrite(MYLED[5] , HIGH);
  } else if (num == 6) {
    digitalWrite(MYLED[6] , HIGH);
  } else if (num == 7) {
    digitalWrite(MYLED[7] , HIGH);
  } else if (num == 8) {
    for (int id = 0; id <= 7; id++) {
      digitalWrite(MYLED[id], HIGH);
    }
  } else if (num == 9) {
    for (int id = 0; id <= 7; id++) {
      digitalWrite(MYLED[id], LOW);
    }
  }
}

void kakudo_led(int degree) {
  int hikakin;
  if (326 <= degree & degree <= 360 | 0 < degree & degree < 11) {
    hikakin = 0;
  } else if (11 <= degree & degree < 56) {
    hikakin = 1;
  } else if (56 <= degree & degree < 101) {
    hikakin = 2;
  } else if (101 <= degree & degree < 146) {
    hikakin = 3;
  } else if (146 <= degree & degree < 191) {
    hikakin = 4;
  } else if (191 <= degree & degree < 236) {
    hikakin = 5;
  } else if (236 <= degree & degree < 281) {
    hikakin = 6;
  } else if (281 <= degree & degree < 326) {
    hikakin = 7;
  } else if (degree == 0) {
    hikakin = 8;
  }
  LED_shine(0, hikakin);
}

void kyori_led(int kyori) {
  if (kyori == 0) {
    LED_shine(1, 9);
  } else if (kyori == 1) {
    LED_shine(1, 0);
  } else if (kyori == 2) {
    LED_shine(1, 0);
    digitalWrite(LED_CIRCLE1[1] , HIGH);
  } else if (kyori == 3) {
    LED_shine(1, 0);
    digitalWrite(LED_CIRCLE1[1] , HIGH);
    digitalWrite(LED_CIRCLE1[2] , HIGH);
  }
}
