int
divides(long double first, long double second){
  long double r =   second/first;
  if (floorl (r) == r)
      return 1;
  else
      return 0;
}