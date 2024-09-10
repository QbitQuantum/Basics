char io() {
	char str[9];
	char st[10];
	char get[500];
	char* end;
	int hant, i = 0, l = 0;
	char* p;
	char key = NULL;
	FILE * save;

	while (1) {
		puts("名前を8文字以内で入力してください");
		*str = '\0';
		fgets(str, sizeof(8), stdin);
		p = strchr(str, '\n');
		if (p != NULL) { *p = '\0'; }

		while (str[i] != '\0') {
			l = _ismbblead(str[i]);
			i++;
			if (l != 0)break;
		}

		if (l != 0) {
			puts("全角文字が含まれています。半角で入力してください");
			continue;
		}

		sprintf(st, "%s:", str);
		if ((save = fopen("save.txt", "r")) == NULL) {
			save = fopen("save.txt", "w");
			fprintf(save, "%s:", str);
			break;
		}
		else {
			save = fopen("save.txt", "a+");
			end = fgets(get, sizeof(get), save);
			while (end != NULL) {
				end = fgets(get, sizeof(get), save);
				if (_mbsstr(get, st) == NULL) {
					hant = 0;
				}
				else {
					hant = 1;
					break;
				}
			}
			if (hant == 0) {
				fprintf(save, "\n%s:", str);
				break;
			}
			else {
				puts("同じ名前の人がいます。もう一度入力してください\n");
			}
		}
	}
	fclose(save);

	printf("名前は%sです。Enterを押してね！\n", str);

	scanf("%c", &key);
	if (key != NULL) {
		system("cls");
		key = NULL;
	}
	return 0;
}