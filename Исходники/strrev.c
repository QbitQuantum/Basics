int main(void)
{
    char s[128], i, len;
    while (scanf("%s", s)!=EOF) {
	for (i = 0, len = 0; s[i]; i+=1, len+=1)
		;
        printf("in : %s\n", s);
        strrev(s);
        //strrev_utf8(s);
        printf("out: %s\n", s);
        strrev_r(s, 0, len-1);
        printf("out: %s\n", s);
    }
    return 0;
}