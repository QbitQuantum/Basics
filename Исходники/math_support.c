__attribute__((weak)) float nexttowardf(float f, long double td) {
  return nextafterf(f, (float)td);
}