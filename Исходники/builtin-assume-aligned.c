int test6(int *a) {
  a = __builtin_assume_aligned(a, 32, 0, 0); // expected-error {{too many arguments to function call, expected at most 3, have 4}}
  return a[0];
}