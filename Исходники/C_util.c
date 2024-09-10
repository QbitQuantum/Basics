int64_t float_to_nsec(double t){
  return trunc(t * NANO_SCALE_FLOAT);
}