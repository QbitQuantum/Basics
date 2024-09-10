void write_putty_version(char *path)
{
	BOOL ret;
	FILE *fp;
	char *keywords[] = {
		//"AppVerName",
		"AppVersion",
		"VersionInfoTextVersion",
		NULL,
	};
	int i;
	char filename[MAX_PATH * 2], buf[64];
	char revision[64] = {0};
	char header_line[64]= {0}, *p;

	// PuTTYのバージョンを取得する。
	_snprintf_s(filename, sizeof(filename), _TRUNCATE,
	            "%s%s", path, "\\libs\\putty\\windows\\putty.iss");

	if (fopen_s(&fp, filename, "r") != 0) {
		goto write;
	}

	while(!feof(fp)){
		char tmp[64];
		fgets(buf, sizeof(buf), fp);
		for (i = 0 ; keywords[i] ; i++) {
			_snprintf_s(tmp, sizeof(tmp), _TRUNCATE,
			            "%s%s", keywords[i], "=%[^\n]s");
			ret = sscanf_s(buf, tmp, revision, sizeof(revision));
			if (ret != 1) 
				continue;
			printf("%s\n", revision);
			goto close;
		}
	}

close:
	fclose(fp);

	_snprintf_s(filename, sizeof(filename), _TRUNCATE,
	            "%s%s", path, "\\ttssh2\\ttxssh\\puttyversion.h");

	// バージョンをチェックし、変更がなければ抜ける
	if (fopen_s(&fp, filename, "r") != 0) {
		goto write;
	}

	memset(header_line, 0, sizeof(header_line));
	if (fread(header_line, sizeof(char), sizeof(header_line)-1, fp) == 0) {
		fclose(fp);
		goto write;
	}

	if ( (p = strchr(header_line, '"')) == NULL ) {
		fclose(fp);
		goto write;
	}

	p++;
	if (strncmp(p, revision, strlen(p)-2) == 0) {
		fclose(fp);
		goto end;
	}

	fclose(fp);

write:
	_snprintf_s(filename, sizeof(filename), _TRUNCATE,
	            "%s%s", path, "\\ttssh2\\ttxssh\\puttyversion.h");

	// バージョンをヘッダに書き込む。
	if (fopen_s(&fp, filename, "w+") != 0) {
		goto end;
	}

	if (revision[0] != '\0') {
		fprintf(fp, "#define PUTTYVERSION \"%s\"\n", revision);
	}
	else {
		fprintf(fp, "#undef PUTTYVERSION\n");
	}

	fclose(fp);

end:;
}