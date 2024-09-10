void VPathHandleFilePath(STREAM *S,HTTPSession *Session, TPathItem *VPath, int SendData)
{
char *Tempstr=NULL, *ptr;
char *LocalPath=NULL, *ExternalPath=NULL, *DocName=NULL;

//Document name here is whatever part of the Path is *beyond* the VPath component
DocName=HTTPServerSubstituteArgs(DocName, Session->Path+StrLen(VPath->URL), Session);


ptr=GetToken(VPath->Path,":",&Tempstr,0);
while (ptr)
{
	if (*Tempstr=='/') ExternalPath=MCatStr(ExternalPath,Tempstr,":",NULL);
	else 
	{
		if (StrLen(Tempstr)==0) LocalPath=CatStr(LocalPath,"/:");
		else LocalPath=MCatStr(LocalPath,Tempstr,":",NULL);
	}
	ptr=GetToken(ptr,":",&Tempstr,0);
}

Tempstr=CopyStr(Tempstr,"");
if (StrLen(LocalPath)) Tempstr=FindFileInPath(Tempstr,DocName,LocalPath);

if (StrLen(Tempstr)) HTTPServerSendDocument(S, Session, Tempstr, HEADERS_SENDFILE|HEADERS_USECACHE|HEADERS_KEEPALIVE);
else if (StrLen(ExternalPath))
{
	if (strcmp(Session->Method,"POST")==0)
	{
		if (VPath->Flags & PATHITEM_UPLOAD)
		{
		LogToFile(Settings.LogPath,"%s@%s (%s) uploading to %s in VPATH %s", Session->UserName,Session->ClientHost,Session->ClientIP,DocName,ExternalPath);
		ChrootProcessRequest(S, Session, "POST", DocName, ExternalPath);
		}
		else 
		{
			LogToFile(Settings.LogPath,"%s@%s (%s) uploading DENIED to %s in VPATH %s", Session->UserName,Session->ClientHost,Session->ClientIP,DocName,ExternalPath);
			HTTPServerSendHTML(S, Session, "403 Forbidden","Uploads not allowed to this path.");
		}
	}
	else
	{
	LogToFile(Settings.LogPath,"%s@%s (%s) asking for external document %s in Search path %s", Session->UserName,Session->ClientHost,Session->ClientIP,DocName,ExternalPath);
	ChrootProcessRequest(S, Session, "GETF", DocName, ExternalPath);
	}
}
//This will send '404'
else HTTPServerSendDocument(S, Session, DocName, HEADERS_SENDFILE|HEADERS_USECACHE|HEADERS_KEEPALIVE);

DestroyString(DocName);
DestroyString(Tempstr);
DestroyString(LocalPath);
DestroyString(ExternalPath);
}