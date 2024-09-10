int main() {
	cerr << "opening a socket" << endl;
	Socket* masterSocket = new Socket();
	if (masterSocket->Listen(Port) < 0) { 
		// handle error
		cerr << "Error: the listen function has failed, OS cannot accept new connection" << endl; 
		return -1;
	}
	
	iostream sstream;
	ssbuf* ssbuffer = new ssbuf();
	
	string content_type;
	string relURL, relURL_orig;
	string connection;
	string requestedFile;
	char c;
	int response;
	string header;
	int filesize = 0;
	string debugParams[3];

	while (ssbuffer->accept(masterSocket) != 0) {
		sstream.rdbuf(ssbuffer);
		HTTPrequest httpreq;

		while (1) {

			response = httpreq.readAndParse (sstream);

			relURL = httpreq.relURL_orig();

			tempnum = saveUserParam();
			int b = relURL.find_first_of("~",0);
			if (relURL.substr(0,b) == "/" && relURL != "/") {
				int e = relURL.find_first_of("/",b);
				if (relURL == relURL.substr(0,e)) {
					relURL = relURL + "/";
					e = relURL.find_first_of("/",b);
				}
				int e2 = relURL.find_first_of("\r",0);
	
				string temprelURL = relURL.substr(2,e-2);
				if (lookupUserParam(temprelURL) != "") {
					relURL = lookupUserParam(temprelURL) + relURL.substr(e,e2-e);
				}
				else {
					httperror (sstream, 404, "Requested file not found", relURL);
					continue;
				}	
			}

			requestedFile = ROOT_DIR + relURL;
			filesize = FileSize (requestedFile.c_str());

			debugParams[0] = httpreq.method();
			debugParams[1] = relURL;
			debugParams[2] = httpreq.version();

			// send information to be written to debug log
			con.debugLog(debugParams, filesize);		

			// send information to be written to access log
			con.accessLog(masterSocket->address, httpreq.method(), relURL, httpreq.version(), 200, filesize);

			if (response == 0) {
				// see if connection has been terminated
				if (sstream.fail()) {
					cerr << "Seems connection no more" << endl;
					break;
				}
				else {
					httperror (sstream, 400, "Malformed request", relURL);
					continue;
				}
			}
			else {
				if (httpreq.method() != "get") {
					httperror (sstream, 501, "Request method not implemented", relURL);
					continue;
				}
				
				struct stat FileStats;
				lstat(requestedFile.c_str(), &FileStats);
				if (FileStats.st_mode&S_IFDIR) {

					if (relURL.substr (relURL.length() - 1) != "/")
						relURL = relURL + "/";
 
					string indexURL1 = ROOT_DIR + relURL + "index.html";
					string indexURL2 = ROOT_DIR + relURL + "index.htm";
					string indexURL3 = ROOT_DIR + relURL + "index.shtml";

					ifstream indexfile1(indexURL1.c_str(), ios::in);
					ifstream indexfile2(indexURL2.c_str(), ios::in);
					ifstream indexfile3(indexURL3.c_str(), ios::in);
					if (indexfile1.fail()) {
						if (indexfile2.fail()) {
							if (indexfile3.fail()) {
								requestedFile = ROOT_DIR + relURL;
								ifstream inputfile(requestedFile.c_str(), ios::in);
								if (inputfile.fail()) {
									httperror (sstream, 404, "Requested file not found", relURL);
									continue;
								}
								makeDirectory (sstream, relURL);
								continue;
							}
							else {
								relURL = relURL + "index.shtml";
							}
						}
						else {
							relURL = relURL + "index.htm";
						}
					}
					else {
						relURL = relURL + "index.html";
					}

				}

				// appropriately set content type corresponding to file extension
				content_type = "no content";
				if (relURL == relURL.substr (0, relURL.find_first_of (".", 0))) {
					content_type = "text/plain";
				}
				if (relURL.length() >= 4) {
					if (relURL.substr (relURL.length() - 2) == ".h" || relURL.substr (relURL.length() - 2) == ".c") {
						content_type = "text/plain";
					}
					if (relURL.substr (relURL.length() - 2) == ".H" || relURL.substr (relURL.length() - 2) == ".C") {
						content_type = "text/plain";
					}
				}
				if (relURL.length() >= 6) {
					if (relURL.substr (relURL.length() - 4) == ".htm") {
						content_type = "text/html";
					}
					else if (relURL.substr (relURL.length() - 4) == ".jpg") {
						content_type = "image/jpeg";
					}
					else if (relURL.substr (relURL.length() - 4) == ".txt") {
						content_type = "text/plain";
					}
					else if (relURL.substr (relURL.length() - 4) == ".gif") {
						content_type = "image/gif";
					}
					else if (relURL.substr (relURL.length() - 4) == ".mpg") {
						content_type = "video/mpeg";
					}
					else if (relURL.substr (relURL.length() - 4) == ".pdf") {
						content_type = "application/pdf";
					}
				}
				if (relURL.length() >= 7) {
					if (relURL.substr (relURL.length() - 5) == ".html") {
						content_type = "text/html";
					}
					else if (relURL.substr (relURL.length() - 5) == ".jpeg") {
						content_type = "image/jpeg";
					}
				}
				if (relURL.length() >= 8) {
					if (relURL.substr (relURL.length() - 6) == ".class") {
						content_type = "application/java";
					}
					else if (relURL.substr (relURL.length() - 6) == ".shtml") {
						content_type = "text/html";
					}
				}
				if (content_type == "no content") {
					httperror (sstream, 403, "Requested file forbidden", relURL);
					continue;
				}

				requestedFile = ROOT_DIR + relURL;
				filesize = FileSize (requestedFile.c_str());
				ifstream inputfile(requestedFile.c_str(), ios::in);
			
				if (inputfile.fail()) {
					httperror (sstream, 404, "Requested file not found", relURL);
					continue;
				}

				header = "HTTP/1.1 200 OK\r\n";
				sstream.write (header.c_str(), header.size());
	
				header = "Content-Type:" + content_type + "\r\n";
				sstream.write (header.c_str(), header.size());

				header = "Content-Length:" + strconvert(filesize) + "\r\n";
				sstream.write (header.c_str(), header.size());
				
				header = "Connection:" + connection + "\r\n";
				sstream.write (header.c_str(), header.size());
				
				// end with empty line
				sstream.write ("\r\n", 2);

				for (; filesize >0; filesize--) {
					c = inputfile.get();
					sstream.put (c);
					//cout.put(c);
					if (sstream.fail()) {
						// socket stream failed. Closed by client???
						// nothing we can do, but stop
						break;
					}
				}
		
				sstream.flush ();

				inputfile.close ();
			}
			if (httpreq.lookupParam("connection") == "close")
				break;
		}
		break;
	}
	
	return 0;
}