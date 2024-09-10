static void
cleartoel (GtkViScreen *vi, guint row, guint col)
{
    CHAR_T *p, *e;

    if (MEMCMP(p = CharAt(vi,row,col), e = CharAt(vi,vi->rows,0), 
		vi->cols - col)) {
	MEMMOVE(p, e, vi->cols - col);
	memset(FlagAt(vi,row,col), COLOR_STANDARD, vi->cols - col);
	mark_lines(vi, row, col, row+1, vi->cols);
    }
}