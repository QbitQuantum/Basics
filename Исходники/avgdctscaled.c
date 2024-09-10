/*
 * Compression: converts the arguments of floats and returns a scaled integer in
 * the range of plus or minus 15. 
 */
static int convertToScaledInt(float num) {
    if(num > .3) num = .3;
    else if (num < -.3) num = -.3;
    int scaled = nearbyint(50.0*num);
    if (scaled > 15)
        scaled = 15;
    if (scaled < -15)
        scaled = -15;

  return scaled;
}