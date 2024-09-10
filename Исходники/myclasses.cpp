int TInetFile::CheckFileSize()
{
if(Error==true)return -1;
char buffer[40];
unsigned long buflen=40;
unsigned long index=0;
if(Protokol==INET_FILE_FTP)
{
FSize=FtpGetFileSize(hUrl,&index);
}else   //Если это HTTP
{
if(HttpQueryInfo(hUrl, HTTP_QUERY_CONTENT_LENGTH, buffer, &buflen, &index))
        {
        FSize=StrToInt(buffer);
        }else
        {
        return -1;
        }
}
return FSize;
}