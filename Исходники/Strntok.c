void
main(int argc, char **argv)
{
	char buf[256];
	int i;
	char *t;
	char token[8];
	int tokenLen;

	if (argc < 3) {
		fprintf(stderr, "Usage: test \"buffer,with,delims\" <delimiters>\n");
		exit(1);
	}
	strcpy(buf, argv[1]);
	i = 1;
	t = strtok(buf, argv[2]);
	if (t == NULL)
		exit(0);
	do {
		printf("strtok %d=[%s] length=%d\n", i, t, (int) strlen(t));
		t = strtok(NULL, argv[2]);
		++i;
	} while (t != NULL);

	printf("------------------------------------------------\n");
	strcpy(buf, argv[1]);
	i = 1;
	t = Strtok(buf, argv[2]);
	if (t == NULL)
		exit(0);
	do {
		printf("Strtok %d=[%s] length=%d\n", i, t, (int) strlen(t));
		t = Strtok(NULL, argv[2]);
		++i;
	} while (t != NULL);

	printf("------------------------------------------------\n");
	strcpy(buf, argv[1]);
	i = 1;
	tokenLen = Strntok(token, sizeof(token), buf, argv[2]);
	if (tokenLen < 0)
		exit(0);
	do {
		printf("Strntok %d=[%s] length=%d\n", i, token, tokenLen);
		tokenLen = Strntok(token, sizeof(token), NULL, argv[2]);
		++i;
	} while (tokenLen >= 0);
	exit(0);
}