int httpd_www_main(int fd, char *raw, char *cgi) {
	proxy_db_stats *cur_db;
	int frag_level;

	cur_db = proxy_get_stats();

	if (!cur_db) {
		httpd_www_syserr(fd, "calloc", raw);
		return 0;
	}

	httpd_start_hmenu(fd, NULL);
	httpd_end_hmenu(fd);

	raw[strlen(raw)-3] = '\0';

	httpd_www_label(fd, "Proxies Status", 17);

 	wprintf(fd, "<TABLE BORDER=\"1\" CELLPADDING=\"0\" CELLSPACING=\"0\" WIDTH=\"15%\" ALIGN=\"CENTER\" VALIGN=\"MIDDLE\">\n");

	if (cur_db->valids) {
		wprintf(fd, "\t<TR>\n");
		wprintf(fd, "\t\t<TD>Valids Proxies </TD>\n");
		wprintf(fd, "\t\t<TD ALIGN=\"CENTER\">%d</TD>\n", cur_db->valids);
		wprintf(fd, "\t</TR>\n");
		wprintf(fd, "\t<TR>\n");
	}

	if (cur_db->deads) {
		wprintf(fd, "\t\t<TD>Dead Proxies </TD>\n");
		wprintf(fd, "\t\t<TD ALIGN=\"CENTER\">%d</TD>\n", cur_db->deads);
		wprintf(fd, "\t</TR>\n");
		wprintf(fd, "\t<TR>\n");
	}

	if (cur_db->broken) {
		wprintf(fd, "\t\t<TD>Broken Proxies </TD>\n");
		wprintf(fd, "\t\t<TD ALIGN=\"CENTER\">%d</TD>\n", cur_db->broken);
		wprintf(fd, "\t</TR>\n");
		wprintf(fd, "\t<TR>\n");
	}

	wprintf(fd, "\t\t<TD>Total Proxies </TD>\n");
	wprintf(fd, "\t\t<TD ALIGN=\"CENTER\">%d</TD>\n", cur_db->valids + cur_db->deads + cur_db->unknowns + cur_db->broken);
	wprintf(fd, "\t</TR>\n");

	if (cur_db->index) {
		wprintf(fd, "\t<TR>\n");
		wprintf(fd, "\t\t<TD>Fragmentation </TD>\n");

		frag_level = 100;

		if (cur_db->holes || cur_db->deads || cur_db->broken) {
			frag_level = ((cur_db->holes + cur_db->deads + cur_db->broken)  * 100 / cur_db->index);
		}

		wprintf(fd, "\t\t<TD ALIGN=\"CENTER\">%d%%</TD>\n", frag_level);
		wprintf(fd, "\t</TR>\n");
	}

	wprintf(fd, "</TABLE>\n");

	httpd_www_label(fd, "Your Browser HTTP Headers", 45);

 	wprintf(fd, "<TABLE BORDER=\"1\" CELLPADDING=\"0\" CELLSPACING=\"0\" WIDTH=\"45%\" ALIGN=\"CENTER\" VALIGN=\"MIDDLE\">\n");
	wprintf(fd, "\t<TR>\n");
	wprintf(fd, "\t\t<TD>\n");
	wprintf(fd, "\t\t\t<PRE>%s</PRE>\n", raw);
	wprintf(fd, "\t\t</TD>\n");
	wprintf(fd, "\t</TR>\n");
	wprintf(fd, "</TABLE>\r\n");

	free(cur_db);

	return 1;
}