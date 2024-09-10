static void winblitstatusbar(pdfapp_t *app)
{
	if (gapp.issearching)
	{
		char buf[sizeof(gapp.search) + 50];
		sprintf(buf, "Search: %s", gapp.search);
		XSetForeground(xdpy, xgc, WhitePixel(xdpy, xscr));
		fillrect(0, 0, gapp.winw, 30);
		windrawstring(&gapp, 10, 20, buf);
	}
	else if (showingmessage)
	{
		XSetForeground(xdpy, xgc, WhitePixel(xdpy, xscr));
		fillrect(0, 0, gapp.winw, 30);
		windrawstring(&gapp, 10, 20, message);
	}
	else if (showingpage)
	{
		char buf[42];
		snprintf(buf, sizeof buf, "Page %d/%d", gapp.pageno, gapp.pagecount);
		windrawstringxor(&gapp, 10, 20, buf);
	}
}