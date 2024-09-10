int main()
{
	int t;
	char str[401];
	char stack[400];
	int k;
	int len;
	int i, j;

	scanf("%d", &t);
	getchar();
	k = 0;
	while (k++ < t) {
		gets(str);

		len = strlen(str);
		i = j= 0;
		while (i < len) {
			switch (str[i]) {
				case '^':
				case '*':
				case '/':
					if ((stack[j - 1] == '^'
							|| stack[j - 1] == '*'
							|| stack[j - 1] == '/')
							&& stack[j - 1] != '(') {
						printf("%c", stack[j - 1]);
						stack[j - 1] = str[i];
					}
					else {
						stack[j] = str[i];
						j++;
					}
					break;
				case '+':
				case '-':
					if (stack[j - 1] != '(') {
						printf("%c", stack[j - 1]);
						stack[j - 1] = str[i];
					}
					else {
						stack[j] = str[i];
						j++;
					}
					break;
				case '(':
					stack[j] = str[i];
					j++;
					break;
				case ')':
					while (stack[j - 1] != '(') {
						printf("%c", stack[j - 1]);
						j--;
					}
					j--;
					break;
				default:
					printf("%c", str[i]);
			}
			i++;
		}
		printf("\n");
	}
	return 0;
}