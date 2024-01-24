const int BUZZER = 35;

void F_BUZ_setup() {
  pinMode(BUZZER, OUTPUT);
}


void F_BUZ_frog() {
  int a = 150;
  int b = 225;
  int c = 300;
  int d = 425;
  tone(BUZZER, 262, a); //ド
  delay(b);
  tone(BUZZER, 262, a); //ド
  delay(b);
  tone(BUZZER, 294, a); //レ
  delay(b);
  tone(BUZZER, 294, a); //レ
  delay(b);
  tone(BUZZER, 330, a); //ミ
  delay(b);
  tone(BUZZER, 330, a); //ミ
  delay(b);
  tone(BUZZER, 349, a); //ファ
  delay(b);
  tone(BUZZER, 349, a); //ファ
  delay(b);

  tone(BUZZER, 330, b); //ミ
  delay(d);
  tone(BUZZER, 294, b); //レ
  delay(d);
  tone(BUZZER, 262, b); //ド
  delay(d);
}

void F_BUZ_DarthVader() {
  //音の長さ(msec)を定義する(BPM=100)
#define Bt2 1200 //2分音符
#define Bt4 500 //4分音符、スタッカート気味
#define Bt8f 450 //付点8分音符
#define Bt8 300 //8分音符
#define Bt16 150 //16分音符

  //音符に対してのDelay Time(msec)を設定
#define Dt2 1100
#define Dt4 500
#define Dt8f 350
#define Dt8 200
#define Dt16 50

  //音程を定義する
#define G4 392 //ソ
#define Ds4 311 //レ＃
#define As4 466 //ラ＃
#define D5 587 //レ
#define Ds5 622 //レ＃
#define Fs4 370 //ファ＃
#define G5 784 //ソ
#define Fs5 740 //ファ＃
#define F5 698 //ファ
#define E5 659 //ミ
#define Gs4 415 //ソ＃
#define Cs5 554 //ド＃
#define C5 523 //ド
#define B4 494 //シ
#define A4 440 //ラ


  tone(BUZZER, G4, Bt4);
  delay(Dt4);
  tone(BUZZER, G4, Bt4);
  delay(Dt4);
  tone(BUZZER, G4, Bt4);
  delay(Dt4);
  tone(BUZZER, Ds4, Bt8f);
  delay(Dt8f);
  tone(BUZZER, As4, Bt8);
  delay(Dt8);
  tone(BUZZER, G4, Bt4);
  delay(Dt4);
  tone(BUZZER, Ds4, Bt8f);
  delay(Dt8f);
  tone(BUZZER, As4, Bt8);
  delay(Dt8);
  tone(BUZZER, G4, Bt2);
  delay(Dt2);

  //3~4小節
  tone(BUZZER, D5, Bt4);
  delay(Dt4);
  tone(BUZZER, D5, Bt4);
  delay(Dt4);
  tone(BUZZER, D5, Bt4);
  delay(Dt4);
  tone(BUZZER, Ds5, Bt8f);
  delay(Bt8f);
  tone(BUZZER, As4, Bt16);
  delay(Dt16);
  tone(BUZZER, Fs4, Bt4);
  delay(Dt4);
  tone(BUZZER, Ds4, Bt8f);
  delay(Dt8f);
  tone(BUZZER, As4, Bt16);
  delay(Dt16);
  tone(BUZZER, G4, Bt2);
  delay(Dt2);

  //5~6小節
  tone(BUZZER, G5, Bt4);
  delay(Dt4);
  tone(BUZZER, G4, Bt8f);
  delay(Dt8f + 50);
  tone(BUZZER, G4, Bt16);
  delay(Dt16);
  tone(BUZZER, G5, Bt4);
  delay(Dt4);
  tone(BUZZER, Fs5, Bt8f);
  delay(Dt8f);
  tone(BUZZER, F5, Bt16);
  delay(Dt16 + 100);
  tone(BUZZER, E5, Bt16);
  delay(Dt16 + 100);
  tone(BUZZER, Ds5, Bt8);
  delay(Dt8);
  delay(Bt8 - 50);
  tone(BUZZER, Gs4, Bt8);
  delay(Dt8);
  tone(BUZZER, Cs5, Bt4);
  delay(Dt4);
  tone(BUZZER, C5, Bt8f);
  delay(Dt8f);
  tone(BUZZER, B4, Bt16);
  delay(Bt16);

  //7~8小節
  tone(BUZZER, As4, Bt16);
  delay(Dt16 + 100);
  tone(BUZZER, A4, Bt16);
  delay(Dt16 + 100);
  tone(BUZZER, Gs4, Bt8);
  delay(Dt8);
  delay(Bt8 - 50);
  tone(BUZZER, Ds4, Bt8);
  delay(Dt8);
  tone(BUZZER, Fs4, Bt4);
  delay(Dt4);
  tone(BUZZER, Ds4, Bt8f);
  delay(Dt8f);
  tone(BUZZER, As4, Bt16);
  delay(Dt16);
  tone(BUZZER, G4, Bt4);
  delay(Dt4);
  tone(BUZZER, Ds4, Bt8f);
  delay(Dt8f);
  tone(BUZZER, As4, Bt16);
  delay(Dt16);
  tone(BUZZER, G4, Bt2);
  delay(Dt2);

  delay(1000);

}
