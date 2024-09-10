int powF(int pow, int base) {
  if(pow == 0)
    return 1;
  else
    return base * powF(pow-1, base);
} 