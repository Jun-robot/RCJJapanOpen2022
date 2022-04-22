void FullLED_setup() {
  FullLED.begin();
  FullLED.clear();

}

void FullLED_loop(int R, int G, int B) {
  //  for (int id = 0; id <= 31; id++) {
  //    FullLED.setPixelColor(id, FullLED.Color(R, G, B));
  //  }

  for (int id = 0; id <= 31; id += 2) {
    FullLED.setPixelColor(id, FullLED.Color(R, G, B));
  }

  for (int id = 1; id <= 31; id += 2) {
    FullLED.setPixelColor(id, FullLED.Color(0, 0, 0));
  }
  
  FullLED.show();
}
