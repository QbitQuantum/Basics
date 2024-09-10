/***********************************************************
 * SaveMails
 ***********************************************************/
void
HDaemonApp::SaveMail(const char* all_content,
						entry_ref* folder_ref,
						entry_ref *file_ref,
						bool *is_delete)
{
	fGotMails = true;
	if(!fHaveNewMails)
		fHaveNewMails = true;
	BString header(""),subject(""),to(""),date(""),cc(""),from("")
			,priority(""),reply(""),mime("");
	Encoding encode;
	
	bool is_multipart = false;
	int32 org_len = strlen(all_content);
	// Probably deleted with Spam filter
	if(org_len == 0)
	{
		*is_delete = false;
		return;
	}
	//
	int32 header_len = 0;
	for(int32 i = 0;i < org_len;i++)
	{
		if(strncasecmp(&all_content[i],"Subject:",8) == 0 && all_content[i-1] == '\n')
			i = GetHeaderParam(subject,all_content,i+8);
		else if(strncasecmp(&all_content[i],"Date:",5) == 0 && all_content[i-1] == '\n')
			i = GetHeaderParam(date,all_content,i+5);
		else if(strncasecmp(&all_content[i],"Cc:",3) == 0 && all_content[i-1] == '\n')
			i = GetHeaderParam(cc,all_content,i+3);
		else if(strncasecmp(&all_content[i],"To:",3) == 0 && all_content[i-1] == '\n')
			i = GetHeaderParam(to,all_content,i+3);
		else if(strncasecmp(&all_content[i],"From:",5) == 0 && all_content[i-1] == '\n')
			i = GetHeaderParam(from,all_content,i+5);
		else if(strncasecmp(&all_content[i],"X-Priority:",11) == 0 && all_content[i-1] == '\n')
			i = GetHeaderParam(priority,all_content,i+11);
		else if(strncasecmp(&all_content[i],"Mime-Version:",13) == 0 && all_content[i-1] == '\n')
			i = GetHeaderParam(mime,all_content,i+13);
		else if(strncasecmp(&all_content[i],"Reply-To:",9) == 0 && all_content[i-1] == '\n')
			i = GetHeaderParam(reply,all_content,i+9);
		else if(all_content[i] == '\r'||all_content[i] == '\n')
		{
			if(all_content[i-2] == '\r'||all_content[i-1] == '\n')
			{
				header_len = i+2;
				break;
			}
		}
	}
	
	header.Append(all_content,header_len);
	
	if(subject.Length() == 0)
		subject = "Untitled";
	if(strstr(header.String(),"Content-Type: multipart"))
		is_multipart = true;
	
	//PRINT(("From:%s\n",from.String()));
	encode.Mime2UTF8(from);
	//PRINT(("Decoded From:%s\n",from.String()));
	encode.Mime2UTF8(to);
	encode.Mime2UTF8(cc);
	encode.Mime2UTF8(reply);
	// convert mime subject to UTF8
	encode.Mime2UTF8(subject);
	
	// Filter mails
	BString folder_path;
	FilterMail(subject.String(),
				from.String(),
				to.String(),
				cc.String(),
				reply.String(),
				folder_path);
	//PRINT(("path:%s\n",folder_path.String() ));
	
	// Save to disk
	BPath path = folder_path.String();
	::create_directory(path.Path(),0777);
	BDirectory destDir(path.Path());
	path.Append(subject.String());
	//PRINT(("path:%s\n",path.Path() ));
	// create the e-mail file
	BFile file;

	TrackerUtils().SmartCreateFile(&file,&destDir,path.Leaf(),"_");
	// write e-mail attributes
	file.Write(all_content,strlen(all_content));
	file.SetSize(strlen(all_content));
	
	file.WriteAttr(B_MAIL_ATTR_STATUS,B_STRING_TYPE,0,"New",4);
	file.WriteAttrString(B_MAIL_ATTR_PRIORITY,&priority);
	file.WriteAttrString(B_MAIL_ATTR_TO,&to);
	file.WriteAttrString(B_MAIL_ATTR_CC,&cc);
	file.WriteAttrString(B_MAIL_ATTR_FROM,&from);
	file.WriteAttrString(B_MAIL_ATTR_SUBJECT,&subject);
	file.WriteAttrString(B_MAIL_ATTR_REPLY,&reply);
	file.WriteAttrString(B_MAIL_ATTR_MIME,&mime);
	file.WriteAttr(B_MAIL_ATTR_ATTACHMENT,B_BOOL_TYPE,0,&is_multipart,sizeof(bool));
	int32 content_len = strlen(all_content)-header_len;
	//PRINT(("header:%d, content%d\n",header_len,content_len));
	file.WriteAttr(B_MAIL_ATTR_HEADER,B_INT32_TYPE,0,&header_len,sizeof(int32));
	file.WriteAttr(B_MAIL_ATTR_CONTENT,B_INT32_TYPE,0,&content_len,sizeof(int32));	
	time_t when = MakeTime_t(date.String());
	time_t now = time(NULL);
	float diff = difftime(now,when);
	switch(fRetrievingType )
	{
	case 0:
		*is_delete = false;
		break;
	case 1:
		*is_delete = true;
		break;
	case 2:
		*is_delete = ( diff/3600 > fDeleteDays*24)?true:false;
		break;
	}
	file.WriteAttr(B_MAIL_ATTR_WHEN,B_TIME_TYPE,0,&when,sizeof(time_t));
	
	BNodeInfo ninfo(&file);
	ninfo.SetType("text/x-email");
	entry_ref ref;
	::get_ref_for_path(path.Path(),&ref);
	*file_ref = ref;
	
	AddNewMail(new BEntry(file_ref));
	
	path.GetParent(&path);
	::get_ref_for_path(path.Path(),&ref);
	*folder_ref =ref;
	return;
}