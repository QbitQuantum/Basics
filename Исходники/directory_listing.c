int HTTPServerSendPackedDir(STREAM *S, HTTPSession *Session, const char *Dir)
{
char *Tempstr=NULL, *DirName=NULL, *FileName=NULL, *ptr;
char *Extn=NULL, *PackType=NULL, *Name=NULL, *Value=NULL;
char *PackList=NULL;
TFileMagic *FM;
HTTPSession *Response;
STREAM *Pipe;

	chdir(Dir);
	//unset session reuse, because we will close session to indicate end of package
	Session->Flags &= ~SESSION_REUSE;

	//do this so we can strcmp it
	PackList=CopyStr(PackList,"");

	Response=HTTPSessionResponse(Session);
	Response->ResponseCode=CopyStr(Response->ResponseCode,"200 OK");

	ptr=GetNameValuePair(Session->Arguments, "&","=",&Name,&Value);
	while (ptr)
	{
		if ( StrLen(Name) )
		{
		if	(strcasecmp(Name,"packtype")==0)
		{
			PackType=CopyStr(PackType,Value);
			Extn=MCopyStr(Extn, ".", Value, NULL);
			FM=GetFileMagicForFile(Extn, NULL);
			Response->ContentType=CopyStr(Response->ContentType, FM->ContentType);
		}
		else if (strcasecmp(Name,"selected")==0) 
		{
			if (strcmp(PackList," *") !=0) PackList=MCatStr(PackList, " ", Value, NULL);
		}
		}
		
	ptr=GetNameValuePair(ptr, "&","=",&Name,&Value);
	}

	if (StrLen(PackList)==0) PackList=CopyStr(PackList, " *");
	DirName=CopyStr(DirName,Dir);
	StripDirectorySlash(DirName);
	ptr=GetBasename(DirName);

	if (! StrLen(ptr)) ptr="rootdir";

	FileName=MCopyStr(FileName,Session->Host,"-",Session->UserName,"-",ptr,Extn,NULL);
	strrep(FileName,' ','_');

	Tempstr=MCopyStr(Tempstr,"attachment; filename=",FileName,NULL);
	SetVar(Response->Headers,"Content-disposition",Tempstr);

	ptr=GetNameValuePair(Settings.PackFormats, ",",":", &Name, &Value);
	while (ptr)
	{
	if (strcasecmp(Name, PackType)==0)
	{
		if (strcasecmp(Value,"internal")==0)
		{
			if (strcasecmp(Name,"tar")==0) 
			{
				HTTPServerSendHeaders(S, Response, 0); 
				TarFiles(S, PackList);
			}
		}
		else
		{
		HTTPServerSendHeaders(S, Response, 0); 
		Tempstr=MCopyStr(Tempstr,Value,PackList,NULL);
		Pipe=STREAMSpawnCommand(Tempstr, COMMS_BY_PIPE);
		STREAMSendFile(Pipe, S, 0, SENDFILE_KERNEL| SENDFILE_LOOP);
		STREAMClose(Pipe);
		}
	}
	ptr=GetNameValuePair(ptr, ",",":", &Name, &Value);
	}

	STREAMFlush(S);

DestroyString(FileName);
DestroyString(Tempstr);
DestroyString(DirName);
DestroyString(PackList);
DestroyString(PackType);
DestroyString(Name);
DestroyString(Value);
DestroyString(Extn);


//This true means 'please close the connection' as our tarballs/zips are transferred using
//connection: close to indicate end of transfer
return(STREAM_CLOSED);
}