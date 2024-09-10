/*******************************************************************
 *	顯示 <BBS_User_xxxxx> TAG
 *	目前 UserQuery ,UserData 用的TAG一樣, 靠URLParaType區分 
 *
 *	in UserQuery mode , curuser is target for query, not original userdata
 *******************************************************************/
void 
ShowUser(char *tag, USEREC * curuser)
{
	if (request_rec->URLParaType != UserQuery && PSCorrect != Correct)
		return;

	if (!strcasecmp(tag, "ID"))
	{
		fputs(curuser->userid, fp_out);
	}
	else if (!strcasecmp(tag, "Name"))
	{
		char buf[STRLEN];
#if defined(NSYSUBBS1)
		if (request_rec->URLParaType == UserQuery && curuser->ident != 7)
			fputs("中山遊客", fp_out);
		else
#endif	
		{
			xstrncpy(buf, curuser->username, STRLEN);
			fputs(buf, fp_out);
		}
	}
	else if (!strcasecmp(tag, "Level"))
	{
		fprintf(fp_out, "%d", curuser->userlevel);
	}
	else if (!strcasecmp(tag, "Login"))
	{
		fprintf(fp_out, "%d", curuser->numlogins);
	}
	else if (!strcasecmp(tag, "Post"))
	{
		fprintf(fp_out, "%d", curuser->numposts);
	}
#ifdef USE_IDENT
	else if (!strcasecmp(tag, "Ident"))
		{
		fputs(curuser->ident == 7 ? MSG_HasIdent : MSG_NotIdent, fp_out);
	}
#endif
	else if (!strcasecmp(tag, "LastLogin"))
	{
		fputs(Ctime(&(curuser->lastlogin)), fp_out);
	}
	else if (!strcasecmp(tag, "LastHost"))
	{
		fputs(curuser->lasthost, fp_out);
	}
	else if (!strcasecmp(tag, "NewMail"))
	{
		if (curuser->flags[0] & FORWARD_FLAG)
			fputs(MSG_MailForwardON, fp_out);
		else if (!strcmp(curuser->userid, "guest"))
			fputs(MSG_MailHasRead, fp_out);
		else
		{
			if ((request_rec->URLParaType != UserQuery && PSCorrect != Correct)
				|| !CheckNewmail(curuser->userid, TRUE))
			{
				fputs(MSG_MailHasRead, fp_out);
			}
			else
			{
				fputs(MSG_MailNotRead, fp_out);
			}
		}
	}
	else if (!strcasecmp(tag, "Status"))	/* print user online status */
	{
		USER_INFO *quinf;

		if ((quinf = search_ulist(cmp_userid, curuser->userid)) && !(quinf->invisible))
		{
			fprintf(fp_out, "線上狀態: %s, 呼喚鈴: %s.",
				modestring(quinf, 1),
				(quinf->pager != PAGER_QUIET) ? MSG_ON : MSG_OFF);
		}				
		else
			fprintf(fp_out, "目前不在線上");
	}
	else if (!strcasecmp(tag, "Plan"))
	{
		char userfile[PATHLEN];

		sethomefile(userfile, curuser->userid, UFNAME_PLANS);
		if (request_rec->URLParaType == UserData)
			ShowArticle(userfile, FALSE, FALSE);
		else
			ShowArticle(userfile, FALSE, TRUE);
	}
	else
	{
		if (request_rec->URLParaType == UserQuery)	/* bug fixed */
			return;
			
		if (!strcasecmp(tag, "Email"))
		{
			fputs(curuser->email, fp_out);
		}
		else if (!strcasecmp(tag, "MailForward"))	/* use in UserData only */
		{
			fputs(curuser->flags[0] & FORWARD_FLAG ? "ON" : "OFF", fp_out);
		}
		else if (!strcasecmp(tag, "Friend"))
		{
			char userfile[PATHLEN];

			sethomefile(userfile, curuser->userid, UFNAME_OVERRIDES);
			ShowArticle(userfile, FALSE, TRUE);
		}
		else if (strstr(tag, "Sign"))
		{
			FILE *fp;
			char fname[PATHLEN];

			sethomefile(fname, curuser->userid, UFNAME_SIGNATURES);
			if ((fp = fopen(fname, "r")) != NULL)
			{
				int line = 0, num;			
				char buffer[512];
				
				GetPara3(buffer, "NUM", tag, 3, "-1");
				num = atoi(buffer);

				for (line = 0; line < num * MAX_SIG_LINES 
						&& fgets(buffer, sizeof(buffer), fp); line++)
				{
					if (line < (num - 1) * MAX_SIG_LINES)
						continue;
					fprintf(fp_out, "%s", buffer);
				}

				fclose(fp);
			}
		}
	}
}