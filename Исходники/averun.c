int
draw_pic()
{
	char *blk[10] = {
		"£ß", "¡õ", "¡õ", "¡õ", "¡õ",
		"¡õ", "¡õ", "¡õ", "¡õ", "¡õ",
	};
	FILE *fp;
	int max = 0, cr = 0, tm, i, item, j, aver = 0;
	int pic[24];
	char buf[80];
	char sid[11];
	time_t now;

	snprintf(sid, sizeof (sid), "%10s", MY_BBS_ID " BBS");
	time(&now);
	if ((fp = fopen(AVEFLE, "r")) == NULL)
		return -1;
	else {
		bzero(&pic, sizeof (pic));
		i = 0;
		while (fgets(buf, 50, fp) != NULL) {
			cr = atoi(index(buf, ':') + 1);
			tm = atoi(buf);
			pic[tm] = cr;
			aver += cr;
			i++;
			max = (max > cr) ? max : cr;
		}
		aver = aver / (i ? i : 1) + 1;
		fclose(fp);
	}

	if ((fp = fopen(AVEPIC, "w")) == NULL)
		return -1;

	item = (max / MAX_LINE) + 1;

	fprintf(fp,
		"\n [1;36m   ©°¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´[m\n");

	for (i = MAX_LINE; i >= 0; i--) {
		fprintf(fp, "[1;37m%4d[36m©¦[32m", (i + 1) * item);
		for (j = 0; j < 24; j++) {
			if ((item * i > pic[j]) && (item * (i - 1) <= pic[j])
			    && pic[j]) {
				fprintf(fp, "[35m%-3d[32m", (pic[j] % 1000));
				continue;
			}
			if (pic[j] - item * i < item && item * i < pic[j])
				fprintf(fp, "%s ",
					blk[((pic[j] - item * i) * 10) / item]);
			else if (pic[j] - item * i >= item)
				fprintf(fp, "%s ", blk[9]);
			else
				fprintf(fp, "   ");
		}
		fprintf(fp, "[1;36m©¦[m");
		fprintf(fp, "\n");
	}
	time(&now);
	fprintf(fp,
		"[1;37m   0[36m©¸¡ª¡ª[37m%sÆ½¾ù¸ºÔØÈËÊýÍ³¼Æ  [36m¡ª¡ª",
		sid);
	fprintf(fp, "¡ª¡ª[37m %s [36m¡ª¡ª¡ª©¼[m\n", Ctime(now));
	fprintf(fp,
		"[1;36m      00 01 02 03 04 05 06 07 08 09 10 11 [31m12 13 14");
	fprintf(fp, " 15 16 17 18 19 20 21 22 23[m\n\n");
	fprintf(fp,
		"                         [1;36m    1 [32m¡õ[36m = [37m%3d     [36m Æ½¾ùÉÏÕ¾ÈËÊý£º[37m%3d[m\n",
		item, aver);
	fclose(fp);
	return 0;
}