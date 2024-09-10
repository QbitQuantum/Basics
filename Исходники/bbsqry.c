int
bbsqry_main()
{
	FILE *fp;
	char userid[14], filename[80], buf[512];
	struct userec *x;
	struct user_info *u;
	int i, tmp2, num;
	html_header(1);
	check_msg();
	changemode(QUERY);
	strsncpy(userid, getparm("U"), 13);
	if (!userid[0])
		strsncpy(userid, getparm("userid"), 13);
	printf("<body><center>");
	printf("<div class=rhead>%s -- ��ѯ����</div><hr>\n", BBSNAME);
	if (userid[0] == 0) {
		printf("<form action=bbsqry>\n");
		printf
		    ("�������û���: <input name=userid maxlength=12 size=12>\n");
		printf("<input type=submit value=��ѯ�û�>\n");
		printf("</form><hr>\n");
		http_quit();
	}
	x = getuser(userid);
	if (x == 0) {
		int i, j = 0;
		printf("û������û������ѵ�����Щ:<p>");
		printf("<table width=600>");
		for (i = 0; i < shm_ucache->number; i++)
			if (strcasestr(shm_ucache->userid[i], userid) ==
			    shm_ucache->userid[i]) {
				j++;
				if (j % 6 == 1)
					printf("<tr>");
				printf("<td>");
				printf("<a href=bbsqry?userid=%s>%s</a>",
				       shm_ucache->userid[i],
				       shm_ucache->userid[i]);
				printf("</td>");
				sprintf(buf, "bbsqry?userid=%s",
					shm_ucache->userid[i]);
				if (j % 6 == 0)
					printf("</tr>");
				if (j >= 12 * 6)
					break;
			}
		printf("</table>");
		if (!j)
			printf("�����ܣ��϶������ô��ˣ�����û���˰�");
		if (j == 1)
			redirect(buf);
		printf("<p><a href=javascript:history.go(-1)>���ٷ���</a>");
		http_quit();
	}
	printf("</center><pre style='font-size:14px'>\n");
	sprintf(buf,
		"%s ([33m%s[37m) ����վ [1;32m%d[m �Σ��������� [1;32m%d[m ƪ",
		x->userid, x->username, x->numlogins, x->numposts);
	hprintf("%s", buf);
	show_special_web(x->userid);//add by wjbta@bmy  ����id��ʶ
	printf("\n");
	hprintf("�ϴ��� [[1;32m%s[m] �� [[1;32m%s[m] ����վһ�Ρ�\n",
		Ctime(x->lastlogin), x->lasthost);
	mails(userid, &tmp2);
	hprintf("���䣺[[1;32m%s[m]��", tmp2 ? "��" : "  ");
	if (!strcasecmp(x->userid, currentuser.userid)) {
		hprintf("����ֵ��[[1;32m%d[m]([33m%s[m) ", countexp(x),
			cexp(countexp(x)));
		hprintf("����ֵ��[[1;32m%d[m]([33m%s[m) ", countperf(x),
			cperf(countperf(x)));
	}
	hprintf("��������[[1;32m%d[m]��\n", count_life_value(x));
	if (x->userlevel & PERM_BOARDS) {
		hprintf("���ΰ���");
		sethomefile(filename, x->userid, "mboard");
		new_apply_record(filename, sizeof (struct boardmanager),
				 (void *) bm_printboard, NULL);
		if (x->userlevel & !strcmp(x->userid, "SYSOP")) hprintf("[[1;36mϵͳ����Ա[m]");
		else if (x->userlevel & !strcmp(x->userid, "lanboy")) hprintf("[[1;36mϵͳ����Ա[m]");
		else if ((x->userlevel&PERM_SYSOP) && (x->userlevel&PERM_ARBITRATE) )	hprintf("[[1;36m��վ������[m]");
		else if (x->userlevel & PERM_SYSOP)	hprintf("[[1;36m����վ��[m]");
		else if (x->userlevel & PERM_OBOARDS)   hprintf("[[1;36mʵϰվ��[m]");
		else if (x->userlevel & PERM_ARBITRATE)	hprintf("[[1;36m���μ�ί[m]");
		else if (x->userlevel & PERM_SPECIAL4)	hprintf("[[1;36m����[m]");
		else if (x->userlevel & PERM_WELCOME) hprintf("[[1;36mϵͳ����[m]");
		else if (x->userlevel & PERM_SPECIAL7)
		{
		if ( (x->userlevel & PERM_SPECIAL1) && !(x->userlevel & PERM_CLOAK) ) 
		hprintf("[[1;36m���γ���Ա[m]");		
		else		
		hprintf("[[1;36m�������Ա[m]");
		}
		else if (x->userlevel & PERM_ACCOUNTS) hprintf ("[[1;36m�ʺŹ���Ա[m]"); 
		hprintf("\n");
	}
	num = 0;
	for (i = 0; i < MAXACTIVE; i++) {
		u = &(shm_utmp->uinfo[i]);
		if (!strcmp(u->userid, x->userid)) {
			if (u->active == 0 || u->pid == 0
			    || (u->invisible && !HAS_PERM(PERM_SEECLOAK)))
				continue;
			num++;
			if (num == 1)
				hprintf("Ŀǰ��վ��, ״̬����:\n");
			if (u->invisible)
				hprintf("[36mC[37m");
			if (u->mode != USERDF4)
			  hprintf("\033[%dm%s[m ", u->pid == 1 ? 35 : 32,
				ModeType(u->mode));
			else							/* �Զ���״̬ */
			  hprintf("\033[%dm%s[m ", u->pid == 1 ? 35 : 32,
				u->user_state_temp);
			if (num % 5 == 0)
				printf("\n");
		}
	}
	if (num == 0) {
		hprintf("Ŀǰ����վ��, �ϴ���վʱ�� [[1;32m%s[m]\n\n",
			x->lastlogout ? Ctime(x->lastlogout) :
			"�������ϻ��������߲���");
	}
	printf("\n");
	printf("</pre><table width=100%%><tr><td class=f2>");
	sethomefile(filename, x->userid, "plans");
	fp = fopen(filename, "r");
	sprintf(filename, "00%s-plan", x->userid);
	fdisplay_attach(NULL, NULL, NULL, NULL);
	if (fp) {
		while (1) {
			if (fgets(buf, 256, fp) == 0)
				break;
			if (!strncmp(buf, "begin 644 ", 10)) {
				errlog("old attach %s", filename);
				fdisplay_attach(stdout, fp, buf, filename);
				continue;
			}
			fhhprintf(stdout, "%s", buf);
		}
		fclose(fp);
	} else {
		hprintf("[36mû�и���˵����[37m\n");
	}
	printf("</td></tr></table>");
	printf
	    ("<br><br><a href=bbspstmail?userid=%s&title=û����>[�������]</a> ",
	     x->userid);
	printf("<a href=bbssendmsg?destid=%s>[����ѶϢ]</a> ", x->userid);
	printf("<a href=bbsfadd?userid=%s>[�������]</a> ", x->userid);
	printf("<a href=bbsfdel?userid=%s>[ɾ������]</a>", x->userid);
	printf("<hr>");
	printf("<center><form action=bbsqry>\n");
	printf("�������û���: <input name=userid maxlength=12 size=12>\n");
	printf("<input type=submit value=��ѯ�û�>\n");
	printf("</form><hr>\n");
	printf("</body>\n");
	http_quit();
	return 0;
}