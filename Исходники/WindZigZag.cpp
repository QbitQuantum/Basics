static  double ItoV(int i) {
    return max(0,min(i,NUM_V_POINTS-1))*V_SCALE/(NUM_V_POINTS-1);
  }