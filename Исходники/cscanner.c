void retract(int n) {
  int i;
  for (i = 0; i < n; i++) {
    yylen--;
    if (yylen >= 0) {
      Ungetc(yytext[yylen],LEX_in);
      if (yytext[yylen] == '\n') {
	cparse_line--;
      }
    }
  }
  if (yylen < 0) yylen = 0;
}