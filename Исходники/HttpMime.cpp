// a cacheTime of -1 means browser should not cache at all
void HttpMime::makeMime  ( int32_t    totalContentLen    , 
			   int32_t    cacheTime          ,
			   time_t  lastModified       ,
			   int32_t    offset             , 
			   int32_t    bytesToSend        ,
			   char   *ext                ,
			   bool    POSTReply          ,
			   char   *contentType        ,
			   char   *charset            ,
			   int32_t    httpStatus         ,
			   char   *cookie             ) {
	// assume UTF-8
	//if ( ! charset ) charset = "utf-8";
	// . make the content type line
	// . uses a static buffer
	if ( ! contentType ) 
		contentType = (char *)getContentTypeFromExtension ( ext );

	// do not cache plug ins
	if ( contentType && strcmp(contentType,"application/x-xpinstall")==0)
		cacheTime = -2;

	// assume UTF-8, but only if content type is text
	// . No No No!!!  
	// . This prevents charset specification in html files
	// . -partap

	//if ( ! charset && contentType && strncmp(contentType,"text",4)==0) 
	//	charset = "utf-8";
	// this is used for bz2 and gz files (mp3?)
	const char *contentEncoding = getContentEncodingFromExtension ( ext );
	// the string
	char enc[128];
	if ( contentEncoding ) 
		sprintf ( enc , "Content-Encoding: %s\r\n", contentEncoding );
	else
		enc[0] = '\0';
	// get the time now
	//time_t now = getTimeGlobal();
	time_t now;
	if ( isClockInSync() ) now = getTimeGlobal();
	else                   now = getTimeLocal();
	// get the greenwhich mean time (GMT)
	char ns[128];
	struct tm *timeStruct = gmtime ( &now );
	// Wed, 20 Mar 2002 16:47:30 GMT
	strftime ( ns , 126 , "%a, %d %b %Y %T GMT" , timeStruct );
	// if lastModified is 0 use now
	if ( lastModified == 0 ) lastModified = now;
	// convert lastModified greenwhich mean time (GMT)
	char lms[128];
	timeStruct = gmtime ( &lastModified );
	// Wed, 20 Mar 2002 16:47:30 GMT
	strftime ( lms , 126 , "%a, %d %b %Y %T GMT" , timeStruct );
	// . the pragma no cache string (used just for proxy servers?)
	// . also use cache-control: for the browser itself (HTTP1.1, though)
	// . pns = "Pragma: no-cache\nCache-Control: no-cache\nExpires: -1\n";
	char tmp[128];
	char *pns ;
	// with cache-control on, when you hit the back button, it reloads
	// the page, this is bad for most things... so we only avoid the
	// cache for index.html and PageAddUrl.cpp (the main and addurl page)
	if      ( cacheTime == -2 ) pns =  "Cache-Control: no-cache\r\n"
					   "Pragma: no-cache\r\n"
					   "Expires: -1\r\n";
	// so when we click on a control link, it responds correctly.
	// like turning spiders on.
	else if  ( cacheTime == -1 ) pns = "Pragma: no-cache\r\n"
					   "Expires: -1\r\n";
	// don't specify cache times if it's 0 (let browser regulate it)
	else if ( cacheTime == 0 ) pns = "";
	// otherwise, expire tag: "Expires: Wed, 23 Dec 2001 10:23:01 GMT"
	else {
		time_t  expDate = now + cacheTime;
		timeStruct = gmtime ( &expDate );
		strftime ( tmp , 100 , "Expires: %a, %d %b %Y %T GMT\r\n", 
			   timeStruct );
		pns = tmp;
	}
	// . set httpStatus
	// . a reply to a POST (not a GET or HEAD) should be 201
	char *p = m_buf;
	char *smsg = "";
	if ( POSTReply ) {
		if ( httpStatus == -1 ) httpStatus = 200;
		if ( httpStatus == 200 ) smsg = " OK";
		if ( ! charset ) charset = "utf-8";
		//sprintf ( m_buf , 
		p += sprintf ( p,
			  "HTTP/1.0 %"INT32"%s\r\n"
			  "Date: %s\r\n"
			       //"P3P: CP=\"CAO PSA OUR\"\r\n"
			  "Access-Control-Allow-Origin: *\r\n"
			  "Server: Gigablast/1.0\r\n"
			  "Content-Length: %"INT32"\r\n"
			  //"Expires: Wed, 23 Dec 2003 10:23:01 GMT\r\n"
			  //"Expires: -1\r\n"
			  "Connection: Close\r\n"
			  "%s"
			  "Content-Type: %s\r\n",
			  //"Connection: Keep-Alive\r\n"
			  //"%s"
			  //"Location: f**k\r\n"
			  //"Location: http://192.168.0.4:8000/cgi/3.cgi\r\n"
			  //"Last-Modified: %s\r\n\r\n" ,
			  httpStatus , smsg ,
			  ns , totalContentLen , enc , contentType  );
			  //pns ,
	                  //ns );
			  //lms );
	}
	// . is it partial content?
	// . if bytesToSend is < 0 it means "totalContentLen"
	else if ( offset > 0 || bytesToSend != -1 ) {
		if ( httpStatus == -1 ) httpStatus = 206;
		if ( ! charset ) charset = "utf-8";
		//sprintf ( m_buf , 
		p += sprintf( p,
			      "HTTP/1.0 %"INT32" Partial content\r\n"
			      "%s"
			      "Content-Length: %"INT32"\r\n"
			      "Content-Range: %"INT32"-%"INT32"(%"INT32")\r\n"// added "bytes"
			      "Connection: Close\r\n"
			      //"P3P: CP=\"CAO PSA OUR\"\r\n"
			      // for ajax support
			      "Access-Control-Allow-Origin: *\r\n"
			      "Server: Gigablast/1.0\r\n"
			      "%s"
			      "Date: %s\r\n"
			      "Last-Modified: %s\r\n" 
			      "Content-Type: %s\r\n",
			      httpStatus ,
			      enc ,bytesToSend ,
			      offset , offset + bytesToSend , 
			      totalContentLen ,
			      pns ,
			      ns , 
			      lms , contentType );
		// otherwise, do a normal mime
	}
	else {
		char encoding[256];
		if (charset) sprintf(encoding, "; charset=%s", charset);
		else encoding[0] = '\0';
		
		
		if ( httpStatus == -1 ) httpStatus = 200;
		if ( httpStatus == 200 ) smsg = " OK";
		//sprintf ( m_buf , 
		p += sprintf( p,
			      "HTTP/1.0 %"INT32"%s\r\n"
			      , httpStatus , smsg );
		// if content length is not known, as in diffbot.cpp, then
		// do not print it into the mime
		if ( totalContentLen >= 0 )
			p += sprintf ( p , 
				       // make it at least 4 spaces so we can
				       // change the length of the content 
				       // should we insert a login bar in 
				       // Proxy::storeLoginBar()
				       "Content-Length: %04"INT32"\r\n"
				       , totalContentLen );
		p += sprintf ( p ,
			      "%s"
			      "Content-Type: %s",
			       enc , contentType );
		if ( charset ) p += sprintf ( p , "; charset=%s", charset );
		p += sprintf ( p , "\r\n");
		p += sprintf ( p ,
			       //"Connection: Keep-Alive\r\n"
			       "Connection: Close\r\n"
			       //"P3P: CP=\"CAO PSA OUR\"\r\n"
			       "Access-Control-Allow-Origin: *\r\n"
			       "Server: Gigablast/1.0\r\n"
			       "%s"
			       "Date: %s\r\n"
			       "Last-Modified: %s\r\n" ,
			       pns ,
			       ns , 
			       lms );
	}
	// write the cookie if we have one
	if (cookie) {
		// now it is a list of Set-Cookie: x=y\r\n lines
		//p += sprintf ( p, "Set-Cookie: %s\r\n", cookie);
		if ( strncmp(cookie,"Set-Cookie",10 ) )
			p += sprintf(p,"Set-Cookie: ");
		p += sprintf ( p, "%s", cookie);
		if ( p[-1] != '\n' && p[-2] != '\r' ) {
			*p++ = '\r';
			*p++ = '\n';
		}
	}
			
	// write another line to end the mime
	p += sprintf(p, "\r\n");
	// set the mime's length
	//m_bufLen = gbstrlen ( m_buf );
	m_bufLen = p - m_buf;
}