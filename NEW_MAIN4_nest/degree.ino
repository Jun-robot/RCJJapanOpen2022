int F_360_correct(int degree){
  while(degree < 0){
    degree += 360;
  }
  while(degree > 360){
    degree -= 360;
  }
  return degree;
}

bool range_check(int a, int b, int c) {
  //360だよ
  // a 範囲の最初
  // b 範囲の最後
  // c 判定値

  a = F_360_correct(a);
  b = F_360_correct(b);
  c = F_360_correct(c);

  if (a > b) {
    b += 360;
  }

  if (a <= c && c <= b) {
    return 1;
  } else {
    c += 360;
    if(a <= c && c <= b){
      return 1;
    }
    return 0;
  }
}
