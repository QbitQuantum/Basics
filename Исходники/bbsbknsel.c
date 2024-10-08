int
bbsbknsel_main()
{
	FILE *fp;
	char board[80], dir[160], genbuf[STRLEN];
	struct boardmem *x1;
	struct bknheader x;
	int i, start, total;
	html_header(1);
	printf("<script src=" BBSJS "></script>\n");
	//check_msg();
	changemode(SELBACKNUMBER);
	getparmboard(board, sizeof (board));
	x1 = getboard(board);
	if (x1 == 0)
		nosuchboard(board, "bbsbknsel");
	else {
		strcpy(board, x1->header.filename);
		sprintf(dir, "boards/.backnumbers/%s/.DIR", board);
		fp = fopen(dir, "r");
		if (fp == NULL)
			http_fatal("错误的讨论区");
		total = file_size(dir) / sizeof (struct bknheader);
		start = getdocstart(total, w_info->t_lines);
		printf("<body topmargin=0><nobr><center>\n");
		sprintf(genbuf, "选择过刊 过刊数[%d]", total);
		printboardtop(x1, 5, genbuf);
		if (total <= 0) {
			fclose(fp);
			http_fatal("本讨论区目前没有过刊");
		}
		printf("<table cellSpacing=0 cellPadding=2>\n");
		printf
		    ("<tr class=docbgcolor><td>序号</td><td>讨论区</td><td>建立日期</td><td>标题　　　　　　　　　　　　　　</td></tr>\n");
		if (fp) {
			fseek(fp, (start - 1) * sizeof (struct bknheader),
			      SEEK_SET);
			for (i = 0; i < w_info->t_lines; i++) {
				if (fread(&x, sizeof (x), 1, fp) <= 0)
					break;
				printf("<tr><td>%d</td><td>%s</td>",
				       start + i, x.boardname);
				if (!i)
					printf("<td><nobr>%12.12s</td>",
					       Ctime(x.filetime) + 4);
				else
					printf("<td>%12.12s</td>",
					       Ctime(x.filetime) + 4);
				printf
				    ("<td><a href=bbsbkndoc?B=%d&bkn=%s&num=%d>○ %s </a></td></tr>",
				     getbnumx(x1), bknh2bknname(&x), start + i - 1,
				     void1(titlestr(x.title)));
			}
			printf("</table>");
			printhr();
			fclose(fp);
		}
		printf("选择过刊 过刊数[%d] ", total);
		sprintf(genbuf, "bbsbknsel?B=%d", getbnumx(x1));
		bbsdoc_helper(genbuf, start, total, w_info->t_lines);
		printdocform("bbsbknsel", getbnumx(x1));
		http_quit();
	}
	return 0;
}