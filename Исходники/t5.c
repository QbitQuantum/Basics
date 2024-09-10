int main(void) {
  int i = 8;
  int j = 5;
  double x = 0.005, y = -0.01;
  char c = 'c', d = 'd';
  // Absolute value of integer
  printf("a) %d \n", abs(i - 2 * j));
  // Absolute value of floating point number
  printf("b) %f \n", fabs(x+y));
  // 1-0, printable or not
  printf("c) %d \n", isprint(c));
  // 1-0, parameter is decimal digit or not
  printf("d) %d \n", isdigit(c));
  // Convert form lowercase to uppercase
  printf("e) %d \n", toupper(d));
  // Round upwards
  printf("f) %f \n", ceil(x));
  // Round updwards
  printf("g) %f \n", ceil(x+y));
  // Round downwards
  printf("h) %f \n", floor(x));
  // Round downwards
  printf("i) %f \n", floor(x+y));
  // 1-0, lowercase letter or not
  printf("j) %d \n", islower(c));
  // 1-0 is uppercase letter or not
  printf("k) %d \n", isupper(j));
  // Base e exponential function, e^x
  printf("l) %f \n", exp(x));
  // Natural logarithm
  printf("m) %f \n", log(exp(x)));
  // Square root
  printf("o) %f \n", sqrt(x*x+y*y));
  // 1-0, is dedimal digit or letter
  printf("p) %d \n", isalnum(10*j));
  //1-0, is alphabetic letter or not
  printf("q) %d \n", isalpha(10*j));
  // 1-0, ascii or not
  printf("r) %d \n", isascii(10*j));
  // Converts to ascii
  printf("s) %d \n", toascii(10*j));
  // Floating point remainder of x/y
  printf("t) %f \n", fmod(x,y));
  // Converts to lowercase if a letter
  printf("u) %d \n", tolower(65));
  // Length of string before termination
  printf("v) %zu \n", strlen("hello\0"));
  // WTF
  //printf("w) %d \n", strpos("hello\0", 'e'));
}