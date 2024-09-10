/**
 * Handle this single ARexx message.
 *
 * @param rxmsg
 * @return
 */
static int arexx_message(struct RexxMsg *rxmsg)
{
	STRPTR command_line = (STRPTR)ARG0(rxmsg);
	APTR command_handle;

	struct {
		STRPTR command;
		STRPTR args;
	} command;

	command.command = command.args = NULL;
	rxmsg->rm_Result1 = 0;
	rxmsg->rm_Result2 = 0;

	SM_DEBUGF(5,("Received ARexx command: \"%s\"\n",command_line));

	if ((command_handle = ParseTemplate("COMMAND/A,ARGS/F",command_line,(LONG*)&command)))
	{
		if (!Stricmp("MAINTOFRONT",command.command)) arexx_maintofront(rxmsg,command.args);
		else if (!Stricmp("MAILWRITE",command.command)) arexx_mailwrite(rxmsg,command.args);
		else if (!Stricmp("WRITEATTACH",command.command)) arexx_writeattach(rxmsg,command.args);
		else if (!Stricmp("WRITECLOSE",command.command)) arexx_writeclose(rxmsg,command.args);
		else if (!Stricmp("SETMAIL",command.command)) arexx_setmail(rxmsg,command.args);
		else if (!Stricmp("SETMAILFILE",command.command)) arexx_setmailfile(rxmsg,command.args);
		else if (!Stricmp("SHOW",command.command)) arexx_show(rxmsg,command.args);
		else if (!Stricmp("HIDE",command.command)) arexx_hide(rxmsg,command.args);
		else if (!Stricmp("QUIT",command.command)) arexx_quit(rxmsg,command.args);
		else if (!Stricmp("GETSELECTED",command.command)) arexx_getselected(rxmsg,command.args);
		else if (!Stricmp("GETMAILSTAT",command.command)) arexx_getmailstat(rxmsg,command.args);
		else if (!Stricmp("FOLDERINFO",command.command)) arexx_folderinfo(rxmsg,command.args);
		else if (!Stricmp("REQUEST",command.command)) arexx_request(rxmsg,command.args);
		else if (!Stricmp("REQUESTSTRING",command.command)) arexx_requeststring(rxmsg,command.args);
		else if (!Stricmp("REQUESTFILE",command.command)) arexx_requestfile(rxmsg,command.args);
		else if (!Stricmp("MAILINFO",command.command)) arexx_mailinfo(rxmsg,command.args);
		else if (!Stricmp("SETFOLDER",command.command)) arexx_setfolder(rxmsg,command.args);
		else if (!Stricmp("ADDRGOTO",command.command)) arexx_addrgoto(rxmsg,command.args);
		else if (!Stricmp("ADDRNEW",command.command)) arexx_addrnew(rxmsg,command.args);
		else if (!Stricmp("ADDRSAVE",command.command)) arexx_addrsave(rxmsg,command.args);
		else if (!Stricmp("ADDRLOAD",command.command)) arexx_addrload(rxmsg,command.args);
		else if (!Stricmp("GETURL",command.command)) arexx_geturl(rxmsg,command.args);
		else if (!Stricmp("NEWMAILFILE",command.command)) arexx_newmailfile(rxmsg,command.args);
		else if (!Stricmp("MAILREAD",command.command)) arexx_mailread(rxmsg,command.args);
		else if (!Stricmp("READCLOSE",command.command)) arexx_readclose(rxmsg,command.args);
		else if (!Stricmp("READINFO",command.command)) arexx_readinfo(rxmsg,command.args);
		else if (!Stricmp("READSAVE",command.command)) arexx_readsave(rxmsg,command.args);
		else if (!Stricmp("SCREENTOBACK",command.command)) {struct Screen *scr = (struct Screen *)main_get_screen(); if (scr) ScreenToBack(scr);}
		else if (!Stricmp("SCREENTOFRONT",command.command)) {struct Screen *scr = (struct Screen *)main_get_screen(); if (scr) ScreenToFront(scr);}
		else if (!Stricmp("REQUESTFOLDER",command.command)) arexx_requestfolder(rxmsg,command.args);
		else if (!Stricmp("MAILADD",command.command)) arexx_mailadd(rxmsg,command.args);
		else if (!Stricmp("MAILSETSTATUS",command.command)) arexx_mailsetstatus(rxmsg,command.args);
		else if (!Stricmp("MAILLISTFREEZE",command.command)) main_freeze_mail_list();
		else if (!Stricmp("MAILLISTTHAW",command.command)) main_thaw_mail_list();
		else if (!Stricmp("MAILFETCH",command.command)) arexx_mailfetch(rxmsg,command.args);
		else if (!Stricmp("OPENMESSAGE",command.command)) arexx_openmessage(rxmsg,command.args);
		else if (!Stricmp("VERSION",command.command)) arexx_version(rxmsg,command.args);
		else if (!Stricmp("MAILMOVE",command.command)) arexx_mailmove(rxmsg,command.args);
		else if (!Stricmp("MAILDELETE",command.command)) arexx_maildelete(rxmsg,command.args);
		else rxmsg->rm_Result1 = 20;

		FreeTemplate(command_handle);
	}
	return 0;
}