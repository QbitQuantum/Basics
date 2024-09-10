inline volatile unsigned long long rdtsc() {
 return __rdtscp(&taux);
}