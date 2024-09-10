DWORD CLotusNote::Attachment_GetInfo(char *file_name, WORD *index, BLOCKID *blockid, DWORD *file_size, WORD *file_attr, WORD *host_type, TIMEDATE *date_create, TIMEDATE *date_modified)
{
	if (m_hnote == NULL) return Error_Handle("Attachment_GetInfo ... failed");

	char	file[MAXPATH+1];
	char	fname[100];
	WORD	i;
	BLOCKID	bid,*pbid;

	strcpy(fname,file_name);
	_strupr(fname);
	if (blockid == NULL) pbid = &bid; else pbid = blockid;

	for (i = 0;;i++)
	{
		if (!MailGetMessageAttachmentInfo(m_hnote,i,pbid,file,file_size,file_attr,host_type,date_create,date_modified))
		{
			sprintf(m_err_msg,"Attachment_GetInfo ... file not found with FileName = %s",file_name);
			glog.log_strings(LOG_ERROR,m_err_msg);
			return ERR_FATAL;
		}
		// llevar a mayusculas el fichero
		strupr(file);
		if (strcmp(file,fname) != 0) continue;
		*index = i;
		return ERR_OK;
	}
	return ERR_FATAL;

}