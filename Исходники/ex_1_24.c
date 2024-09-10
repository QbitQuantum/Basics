int findclose(int c) {
	int d;

	while((d = getchar())!=EOF) {
		if(d == '{') {
			findclose('}');
		}
		else if(d == '[') {
			findclose(']');
		}
		else if(d == '(') {
			findclose(')');
		}
		else if(d == '/') {
			if ((d = getchar()) == '*')
				in_comment();
		}
		else if(d == '\'' || d == '"') {
			echo_quote(d);
		}
		else if(c == d) {
			return 0;
		}
		else if(d == '}' || d == ']' || d == ')') {
			printf("find %c, unexpected %c\nexit.\n", c, d);
			_exit(-1);
		}
	}

	if(c != 255) {
		printf("not match, %c\n", c);
		_exit(-1);
	}
	printf("ok\n");
	return 0;
}