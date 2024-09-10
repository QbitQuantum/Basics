int main(int argc, char* argv[]) {

  char c;
  c = getchar();

  while ( c != EOF) {
    if (isUpper(c) == 0)
      c = c + 32;
    printf("%c",c);
    c = getchar();

  }

  return 0;

}