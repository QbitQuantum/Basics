void
db_iprintf(const char *fmt,...)
{
	int i;
	__va_list listp;

	for (i = db_indent; i >= 8; i -= 8)
		db_printf("\t");
	while (--i >= 0)
		db_printf(" ");
	__va_start(listp, fmt);
	kvcprintf (fmt, db_putchar, NULL, db_radix, listp);
	__va_end(listp);
}