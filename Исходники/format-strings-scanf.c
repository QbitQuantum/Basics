void test_variants(int *i, const char *s, ...) {
  FILE *f = 0;
  char buf[100];

  fscanf(f, "%ld", i); // expected-warning{{format specifies type 'long *' but the argument has type 'int *'}}
  sscanf(buf, "%ld", i); // expected-warning{{format specifies type 'long *' but the argument has type 'int *'}}
  my_scanf("%ld", i); // expected-warning{{format specifies type 'long *' but the argument has type 'int *'}}

  va_list ap;
  va_start(ap, s);

  vscanf("%[abc", ap); // expected-warning{{no closing ']' for '%[' in scanf format string}}
  vfscanf(f, "%[abc", ap); // expected-warning{{no closing ']' for '%[' in scanf format string}}
  vsscanf(buf, "%[abc", ap); // expected-warning{{no closing ']' for '%[' in scanf format string}}
}