void eqnsys<nr_type_t>::solve_inverse (void) {
  *X = inverse (*A) * *B;
}