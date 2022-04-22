#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>


const int CHOICE_PIN[] = {2,3,4};
const int READ_PIN[] = {A0, A1, A2, A3};

SoftwareSerial LINESer(10, 11); //rx,tx

const int LED_PIN = 5;
const int LED_NUM = 32;
Adafruit_NeoPixel pixels(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

class line_one {
  public:
    void init(int num);
    void analog_read(void);
    void convert(void);

    int analog_value;
    int digital_value;
  private:
    void pin_set(int num);
    void 
};

void setup() {
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}
