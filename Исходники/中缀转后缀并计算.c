int main()
{
	int i, j, len, a, b;
	char *src = "6*(5+(2+3)*8+3)";
	char des[255];
	Stack S;

	S = createStack();
	if (S == NULL) {
		printf_s("Error\n");
		return 1;
	}

	i = len = 0;
	while (src[i++] != '\0')
		len++;

	/* 将中缀转换为后缀 */
	for (i = j = 0; i < len; i++) {
		if (isSymbol(src[i])) {
			if (src[i] != ')') {
				if (isEmpty(S))
					pushChar(src[i], S);
				else if (pricmp(src[i], topChar(S)) > 0)
					pushChar(src[i], S);                      
				else {
					while (!isEmpty(S) && pricmp(src[i], topChar(S)) <= 0) {
						des[j++] = topChar(S);
						pop(S);
					}
					pushChar(src[i], S);
				}
			}
			else if (src[i] == ')') {
				while (topChar(S) != '(' && !isEmpty(S)) {
					des[j++] = topChar(S);
					pop(S);
				}
				pop(S);
			}
		}
		else {
			des[j++] = src[i];
		}
	}
	/* 将栈里的剩余符号弹出 */
	while (!isEmpty(S)) {
		des[j++] = topChar(S);
		pop(S);
	}
	des[j--] = '\0';
	printf("%s\n", des);
	/* 转换结束 */
	
	/* 用后缀表达式完成计算 */
	i = len = 0;
	while (des[i++] != '\0')
		len++;

	for (i = 0; i < len; i++) {
		if (!isSymbol(des[i]))
			pushInt(des[i] - 48, S);
		else {
			a = topInt(S);
			pop(S);
			b = topInt(S);
			pop(S);
			//printf_s("\na=%d, b=%d\n", a, b);
			switch (des[i]) {
			case '+':
				pushInt(a + b, S);
				break;
			case '-':
				pushInt(a - b, S);
				break;
			case '*':
				pushInt(a*b, S);
				break;
			case '/':
				pushInt(a / b, S);
				break;
			}
		}
	}
	printf_s("Result=%d\n", topInt(S));
	return 0;
}