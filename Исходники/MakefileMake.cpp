// main関数
int main(int argc, char* argv[])
{
	// 引数解釈
	const char*	makefile	= NULL;
	const char*	top_dir		= NULL;

	for (int i=1; i < argc; i++) {
		char*	p = argv[i];
		if (*p == '/' || *p =='-') {
			p++;
			if (_strnicmp(p,"file",4) == 0) {
				p += 4;
				if (*p == '\0') {
					if (i < argc) {
						makefile = argv[++i];
					}
				}
				else {
					if (*p == '=') p++;
					makefile = p;
				}
			}
			else if (_strnicmp(p,"dir",3) == 0) {
				p += 3;
				if (*p == '\0') {
					if (i < argc) {
						top_dir = argv[++i];
					}
				}
				else {
					if (*p == '=') p++;
					top_dir = p;
				}
			}
			else {
				printf("Error: 不明な引数[%s]\n", argv[i]);
				return usage();
			}
		}
		else {
			printf("Error: 不明な引数[%s]\n", argv[i]);
			return usage();
		}
	}
	if (makefile == NULL && top_dir != NULL) { return usage(); }
	if (!makefile)	{ printf("Error: makefileを指定してください\n\n");				return usage(); }
	if (!top_dir)	{ printf("Error: トップディレクトリを指定してください\n\n");	return usage(); }


	// トップディレクトリのチェック
	struct stat		st;
	int		ret = stat( top_dir, &st );
	if (ret != 0 || !(st.st_mode & _S_IFDIR)) {
		printf("Error: トップディレクトリ[%s]が見つかりません\n", top_dir);
		return 1;
	}

	// ファイルオープン
	FILE*	in = NULL;
	if (fopen_s( &in, makefile, "rt" ) != 0) {
		printf("Error: 出力ファイル[%s]を開けません\n", makefile);
		return 1;
	}

	// テンポラリファイルの作成
	char	tmp_file[_MAX_PATH];
	char	drive[_MAX_DRIVE], dir[_MAX_DIR];
	if (_splitpath_s( makefile, drive, _countof(drive), dir, _countof(dir), NULL, 0, NULL, 0 )) {
		printf("Error: 一時ファイル名を作れません[%s]\n", makefile);
		return 1;
	}
	if (_makepath_s( tmp_file, _countof(tmp_file), drive, dir, "mfXXXXXX", NULL )) {
		printf("Error: 一時ファイル名を作れません[%s, %s]\n", drive, dir);
		return 1;
	}
	if (_mktemp_s(tmp_file, _countof(tmp_file))) {
		printf("Error: 一時ファイル名を作れません[%s]\n", tmp_file);
		return 1;
	}
	FILE*	out = NULL;
	if (fopen_s( &out, tmp_file, "wt" ) != 0) {
		printf("Error: 一時ファイル[%s]を開けません\n", tmp_file);
		return 1;
	}

	// ファイルリストの作成
	makeFileListTop(top_dir);

	// ファイルの書替え
	int			mode = 0;			// 0:.obj前 1:.obj中 2:.obj後
	bool		change = false;		// 変更あり

	char		line[1024];
	char		mkline[1024];
	char*		wtline;
	const char*	fl_nm;

	while (fgets(line, _countof(line), in) != NULL) {
		wtline = line;
		switch (mode) {
		case 0:
			if (strstr(line, "OBJS")) {
				mode = 1;
			}
			break;
		case 1:
			if (line[0] == '\n' || line[0] == '\0') {
				// リスト終了?
				fl_nm = getFile();
				if (fl_nm != NULL) {
					// ファイルが増えた
					change = true;
					do {
						//出力
						fprintf(out, "%s", makeObjLine( mkline, _countof(mkline), fl_nm ) );
					} while ((fl_nm = getFile()) != NULL);
				}
				mode = 2;
			}
			else {
				fl_nm = getFile();
				if (fl_nm == NULL) {
					// ファイルが減った
					change = true;
					continue;
				}
				makeObjLine( mkline, _countof(mkline), fl_nm );
				// 変更有りか？
				if (!change && strcmp(line, mkline) != 0)
					change = true;
				wtline = mkline;
			}
			break;
		case 2:
			break;
		}
		//出力
		fprintf(out,"%s", wtline);
	}

	// close
	fclose(in);
	fclose(out);
#ifdef _DEBUG
	printf("%d個のオブジェクトファイル名が出力されました\n", file_list.size());
#endif

	// ファイルの入換え
	if (change) {
		if (remove(makefile)) {
			printf("Error: makefile[%s]を削除出来ません\n", tmp_file);
			return 1;
		}
		if (rename( tmp_file, makefile )) {
			printf("Error: 一時ファイル[%s]をmakfile[%s]に出来ません\n", tmp_file, makefile);
			return 1;
		}
	}
	else {
		if (remove(tmp_file)) {
			printf("Warning: 一時ファイル[%s]を削除出来ません\n", tmp_file);
		}
		printf("出力ファイルは最新です\n");
	}

	return 0;
}