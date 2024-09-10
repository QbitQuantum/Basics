inline unsigned long long rdtsc() {
 unsigned int i = 0;
 return __rdtscp(&i);
}