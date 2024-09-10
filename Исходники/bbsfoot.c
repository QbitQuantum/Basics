int
bbsfoot_main()
{
	int dt = 0, mail_total = 0, mail_unread = 0, lasttime = 0;
	char *id = "guest";
	static int r = 0;
	html_header(2);
	printf("<script>function t(){return (new Date()).valueOf();}</script>");
	printf("<body topmargin=1 MARGINHEIGHT=1 class=foot>\n");
	if (loginok) {
		id = currentuser->userid;
		dt = abs(now_t - w_info->login_start_time) / 60;
	}
	printf("时间[%16.16s] ", Ctime(now_t));
	printf("在线[%d] ", count_online());
	printf("帐号[<a href=\"bbsqry?userid=%s\" target=f3>%s</a>] ", id, id);
	if (loginok && !isguest) {
		int thistime;
		lasttime = atoi(getparm("lt"));
		thistime = mails_time(id);
		if (thistime <= lasttime) {
			mail_total = atoi(getparm("mt"));
			mail_unread = atoi(getparm("mu"));
		} else {
			mail_total = mails(id, &mail_unread);
			lasttime = thistime;
		}
		if (mail_unread == 0) {
			printf("信箱[<a href=bbsmail target=f3>%d封</a>] ",
			       mail_total);
		} else {
			printf
			    ("信箱[<a href=bbsmail target=f3>%d(<font color=red>新信%d</font>)</a>] ",
			     mail_total, mail_unread);
		}
		showmyclass();
	}
#ifdef ENABLE_BLOG
	showmyblog();
#endif

	printf("停留[%d小时%d分] ", dt / 60, dt % 60);
	printf
	    ("<a href=# onclick='javascript:{location=location;return false;}'>刷新</a>");
	printf("<script>setTimeout('self.location.replace("
	       "\"bbsfoot?lt=%d&mt=%d&mu=%d&sn='+t()+'\")', %d);</script>",
	       lasttime, mail_total, mail_unread, 900000 + r * 1000);
	r = (r + dt + now_t) % 30;
	printf("</body>");
	return 0;
}