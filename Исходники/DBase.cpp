int CDBase::CreateDSN(_ConnStr ConnStr)
{ 
//	'DSN=SQL_DSNName112;DESCRIPTION=SQL DSN description;SERVER=AW\SQLEXPRESS;DATABASE=ADM;'
   int nRetCode;  
   CString s;
   s="DSN="+ConnStr.DSNname+";";
   s=s+"DESCRIPTION="+ConnStr.Desc+";";
   s=s+"SERVER="+ConnStr.Server+";";
   s=s+"DATABASE="+ConnStr.Database+";";
 
   //printf("ConnStr=%s\n",s.GetBuffer());

   char *szAttributes=s.GetBuffer(s.GetLength()); 
    printf("Attributes='%s'\n",szAttributes);
   for(int i=0;i<s.GetLength();i++) 
   { 
	if(*(szAttributes+i)==(unsigned char)';') 
		*(szAttributes+i)=NULL; 
   }  
    try
    {
		nRetCode = SQLConfigDataSource(NULL, ODBC_ADD_DSN, ConnStr.Driver.GetBuffer(), szAttributes);
	}
    catch(CDBException *err)
    {
		//MessageBox(NULL,err->m_strError,"SQL Error"	,MB_OK);
    	printf("%s \n",err->m_strStateNativeOrigin);	
		printf("%s \n",err->m_strError);
		err->Delete();
	}
	{
	   //printf("Error create DSN in registry!\n"); 
    }
   return nRetCode;	
}