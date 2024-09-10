bool CFileCurl::GetContent(const CURI &url, CStdString &content, CStdString useragent)
{
   CFileCurl file;
   if (!useragent.IsEmpty())
     file.SetUserAgent(useragent);

   if( file.Stat(url, NULL) == 0 )
   {
     content = file.GetContent();
     return true;
   }
   
   if (file.GetLastRetCode() > 400 )
   {
	 content = "text/html";
   }
   else
   {
   content = "";
   }

   return false;
}