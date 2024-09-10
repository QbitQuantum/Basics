main(){
	char *s0 = "abcd", *s1 = "efg", *s2 = "def", st[MAXLEN];
	strCat(st, s0);
	strCat(st, s1);
	printf("New st is %s.\n", st);
	strnCpy(s1, st, 2);
	printf("%s\n", st);
	return 0;
}