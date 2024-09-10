/// F2H: Convert a floating point number to half-float
inline HALF F2H(FLOAT in)
{
  bool negative = (in < 0);
  int  exponent;
  int  mantissa = 2048.0 * frexpf((negative)?(-in):(in),&exponent);

  if (mantissa == 0) {
    // Zero and -Zero
    return (negative)?(0x8000):(0x0000);
  } 

  /*
  ** this would be the fixup code.
  mantissa <<= 1; // shift into explicit one-bit
  exponent--;     // normalize the exponent correspondingly.
  */
  exponent += 14; // Exponent bias is 15. If this is too large to represent, generate INFs
  if (exponent >= 31) {
    return (negative)?(0xfc00):(0x7c00);
  } else if (exponent < 1) {
    // Denormalize the number.
    while(exponent < 1) {
      exponent++;
      mantissa >>= 1;
    }
    // This is represented with the exponent zero.
    exponent = 0;
  }
  //
  // Now combine the results into one value. Remove the implicit one,
  // and shift the exponent in place 
  mantissa = (mantissa & 0x03ff) | (exponent << 10);
  if (negative)
    mantissa |= 0x8000;

  return mantissa;
}