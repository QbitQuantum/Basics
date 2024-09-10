uint64_t sum_square_digits(uint64_t x) {
  uint64_t sum = 0;

  while(x > 0) {
    ldiv_t div_result = ldiv(x, 10);
    sum += div_result.rem * div_result.rem;
    x = div_result.quot;
  }

  return sum;
}