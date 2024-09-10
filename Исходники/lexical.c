int main() {
  printf(
	 "============================================\n"	\
	 "<expr> -> <term> {(+|-)<term>}\n"			\
	 "<term> -> <factor> {(*|/)<factor>}\n"			\
	 "<expr> -> id | int_constant | ( <expr>)\n"		\
	 "============================================\n\n"
	 );

  in_fp = fopen("expression.in", "r");

  if (in_fp == NULL) {
    printf("ERROR: Cannot open `expression.in` file");
  } else {
    getChar();

    do {
      lex();
      expr();
    } while (nextToken != EOF);
  }

  return 0;
}