nserror
gui_window_save_link(struct gui_window *g, nsurl *url, const char *title)
{
	char fname[1024];
	STRPTR openurlstring,linkname;
	struct DiskObject *dobj = NULL;

	linkname = ASPrintf("Link_to_%s",FilePart(nsurl_access(url)));

	if(AslRequestTags(savereq,
		ASLFR_Window, g->shared->win,
		ASLFR_SleepWindow, TRUE,
		ASLFR_TitleText,messages_get("NetSurf"),
		ASLFR_Screen,scrn,
		ASLFR_InitialFile,linkname,
		TAG_DONE))
	{
		strlcpy(fname, savereq->fr_Drawer, 1024);
		AddPart(fname,savereq->fr_File,1024);

		ami_set_pointer(g->shared, GUI_POINTER_WAIT, false);

		if(ami_download_check_overwrite(fname, g->shared->win, 0))
		{
			BPTR fh;

			if((fh = FOpen(fname,MODE_NEWFILE,0)))
			{
				/* \todo Should be URLOpen on OS4.1 */
				openurlstring = ASPrintf("openurl \"%s\"\n",nsurl_access(url));
				FWrite(fh,openurlstring,1,strlen(openurlstring));
				FClose(fh);
				FreeVec(openurlstring);
				SetComment(fname, nsurl_access(url));

				dobj = GetIconTags(NULL,ICONGETA_GetDefaultName,"url",
									ICONGETA_GetDefaultType,WBPROJECT,
									TAG_DONE);		

				dobj->do_DefaultTool = "IconX";

				PutIconTags(fname,dobj,
							ICONPUTA_NotifyWorkbench,TRUE,
							TAG_DONE);

				FreeDiskObject(dobj);
			}
			FreeVec(linkname);
		}
		ami_reset_pointer(g->shared);
	}
	return NSERROR_OK;
}