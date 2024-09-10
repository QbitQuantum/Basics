/**
  * This function returns the following:
  * -1, a<0
  *  0, a=0
  *  1, a>0
  */
inline __device__ float sign(float& a) {
	/**
	  * The following works by bit hacks. In non-obfuscated code, something like
	  *  float r = ((int&)a & 0x7FFFFFFF)!=0; //set r to one or zero
	  *  (int&)r |= ((int&)a & 0x80000000);   //Copy sign bit of a
	  *  return r;
	  */
#ifndef NEW_SIGN
	return (signed((int&)a & 0x80000000) >> 31 ) | ((int&)a & 0x7FFFFFFF)!=0;
#else
	float r = ((int&)a & 0x7FFFFFFF)!=0;
	return copysignf(r, a);
#endif
}