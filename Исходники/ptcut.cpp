inline unsigned long long refClock() {
  unsigned int taux=0;
  return __rdtscp(&taux);
}