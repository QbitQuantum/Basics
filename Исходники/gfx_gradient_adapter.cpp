 static int calculate(int x, int y, int d)
 {
     return uround(Fabs(Atan2(INT_TO_SCALAR(y), INT_TO_SCALAR(x))) * INT_TO_SCALAR(d) * _1divPI);
 }