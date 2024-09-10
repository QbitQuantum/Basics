int CProxyParse::RunFromMem( wxString content )
{
	char *pBuffer;
	//http://www.51proxied.com/http_non_anonymous.html
	//wxString path = wxT("f:/work/windows/wxUrlRefresh/data/最新透明HTTP代理服务器.htm");
	//wxString path1 = wxT("f:/work/windows/wxUrlRefresh/data/result.xml");

	wxString data_path = wxGetCwd() + "/data/";
	wxString path1 = data_path + "_tmp.xml";

	if (!wxDirExists(data_path))
		wxMkdir(data_path);

	pBuffer = (char*)calloc(content.Length()+1, 1);
	wxStrncpy(pBuffer, content, content.Len()+1);


	wxLogMessage("Run Tidy!");
	TidyBuffer output;
	TidyBuffer errbuf;
	int rc = -1;
	Bool ok;
	TidyDoc tdoc = tidyCreate();                     // Initialize "document"
	tidyBufInit( &output );
	tidyBufInit( &errbuf );
	//printf( "Tidying:\t\%s\\n", input );
	tidySetCharEncoding(tdoc, "utf8");
	ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );  // Convert to XHTML
	if ( ok )
		rc = tidySetErrorBuffer( tdoc, &errbuf );      // Capture diagnostics
	if ( rc >= 0 )
		rc = tidyParseString( tdoc, pBuffer );           // Parse the input
	if ( rc >= 0 )
		rc = tidyCleanAndRepair( tdoc );               // Tidy it up!
	if ( rc >= 0 )
		rc = tidyRunDiagnostics( tdoc );               // Kvetch
	if ( rc > 1 )                                    // If error, force output.
		rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
	if ( rc >= 0 )
		rc = tidySaveBuffer( tdoc, &output );          // Pretty Print
	if ( rc >= 0 )
	{
#ifdef _DEBUG
		//if ( rc > 0 )
		//	WriteAllToFile("f:/work/windows/wxUrlRefresh/data/error.xml", (char*)errbuf.bp, errbuf.size);
		WriteAllToFile(path1, (char*)output.bp, output.size);
#endif

	}
	else
		wxLogError("tidyFail");

	tidyBufFree( &output );
	tidyBufFree( &errbuf );
	tidyRelease( tdoc );
	if (pBuffer) free(pBuffer);


	wxLogMessage("Fetch data!");
	// 解析数据
	TiXmlDocument doc(path1);
	if (doc.LoadFile()) 
	{
		// root
		CTiXmlProxyVistor vistor(&m_array);
		TiXmlElement *pRoot = doc.RootElement();
		pRoot->Accept(&vistor);
	}
	else
	{
		wxLogMessage("shit");
		return -2;
	}
	return 0;
}