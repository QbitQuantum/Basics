/*
 * Fold the contents of standard input to fit within WIDTH columns (or bytes)
 * and write to standard output.
 *
 * If sflag is set, split the line at the last space character on the line.
 * This flag necessitates storing the line in a buffer until the current
 * column > width, or a newline or EOF is read.
 *
 * The buffer can grow larger than WIDTH due to backspaces and carriage
 * returns embedded in the input stream.
 */
void
fold(int width)
{
	static wchar_t *buf;
	static int buf_max;
	int col, i, indx, space;
	wint_t ch;

	col = indx = 0;
	while ((ch = getwchar()) != WEOF) {
		if (ch == '\n') {
			wprintf(L"%.*ls\n", indx, buf);
			col = indx = 0;
			continue;
		}
		if ((col = newpos(col, ch)) > width) {
			if (sflag) {
				i = indx;
				while (--i >= 0 && !iswblank(buf[i]))
					;
				space = i;
			}
			if (sflag && space != -1) {
				space++;
				wprintf(L"%.*ls\n", space, buf);
				wmemmove(buf, buf + space, indx - space);
				indx -= space;
				col = 0;
				for (i = 0; i < indx; i++)
					col = newpos(col, buf[i]);
			} else {
				wprintf(L"%.*ls\n", indx, buf);
				col = indx = 0;
			}
			col = newpos(col, ch);
		}
		if (indx + 1 > buf_max) {
			buf_max += LINE_MAX;
			buf = realloc(buf, sizeof(*buf) * buf_max);
			if (buf == NULL)
				err(1, "realloc()");
		}
		buf[indx++] = ch;
	}

	if (indx != 0)
		wprintf(L"%.*ls", indx, buf);
}