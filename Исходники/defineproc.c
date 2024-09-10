// procdefn: process #define or #undef statement
int procdefn(void) {
	char word[MAXWORD], val[MAXTOKEN];
	int c, def;

	while ((c=getch()) != '#' && c != EOF);
	if (c == '#' && (c=getword(word,MAXWORD)) != EOF)
		if ((!strcmp(word,"define")||!strcmp(word,"undef"))) {
			def = word[0] == 'd';
			if ((c=getword(word,MAXWORD)) != EOF) {
				c = gettoken(val,MAXTOKEN);
				if (def)
					install(word, *val != '\0' ? val : "");
				else
					free((void *) undef(word));
			}
		}
	return c;
}