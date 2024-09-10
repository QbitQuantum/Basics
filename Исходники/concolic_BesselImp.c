/* Our C definition of the function bessely0 declared in Bessel.java */
JNIEXPORT jdouble JNICALL
Java_concolic_Bessel_bessely0(JNIEnv *env, jobject obj, jdouble x)
{
  double y;

  /* Call the Y0(x) Bessel function from the
     standard C mathematical library */
  y = y0(x);

  return y;
}