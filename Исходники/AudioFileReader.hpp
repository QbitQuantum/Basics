 /**
  * Converts amplitude level to decibel where an amplitude of 1 
  * relates to a decibel value of 0, and amplitude 0 related to -inf.
  */
 static float amplitude_to_decibe(float a) {
     return log10f(fabsf(a))*20;
 }