bool UploadDump(const char* file, const char* user, int build, int branch, DelegateI<Prog_s>* progress)
{
	Logger log;
	log.write("---------------------------------------\r\n");

	time_t ltime; /* calendar time */
	ltime=time(NULL); /* get current cal time */

	
#ifdef WIN32
	char buff[255] = {0};

	struct tm t;
	localtime_s(&t, &ltime);
	asctime_s(buff, 255, &t);
#else
	struct tm *t = localtime(&ltime);
	char* buff = asctime(t);
#endif

	log.write("%s\r\n", buff);
	log.write("---------------------------------------\r\n");

	log.write("Uploaded crash dump: [%s]\r\n", file);


	gcString dump(file);

	if (PrepDumpForUpload(dump) == false)
	{
		log.write("Failed to prepare crash dump.\r\n");
		return false;
	}
	else
	{
		log.write("Prepared crash dump to: [%s]\r\n", dump.c_str());
	}

	std::string os = UTIL::OS::getOSString();

	HttpHandle hh(DUMP_UPLOAD_URL);

	if (progress)
		hh->getProgressEvent() += progress;

	hh->setUserAgent(DUMP_UPLOAD_AGENT);

	hh->cleanUp();
	hh->addPostText("os", os.c_str());
	hh->addPostText("build", build);
	hh->addPostText("appid", branch);

	if (user)
		hh->addPostText("user", user);

	hh->addPostFile("crashfile", dump.c_str());

	try
	{
		hh->postWeb();
	}
	catch (gcException &except)
	{
		log.write("Failed to upload crash: %s [%d.%d].\r\n", except.getErrMsg(), except.getErrId(), except.getSecErrId());
		return false;
	}

	TiXmlDocument doc;
	doc.LoadBuffer(const_cast<char*>(hh->getData()), hh->getDataSize());
	
	try
	{
		XML::processStatus(doc, "crashupload");
		log.write("Uploaded dump\r\n");
		UTIL::FS::delFile(UTIL::FS::Path(dump, "", true));		
	}
	catch (gcException &)
	{
		log.write("Bad status returned from upload crash dump.\r\n");

		gcString res;
		res.assign(hh->getData(), hh->getDataSize());

		log.write("Result: \r\n\r\n%s\r\n\r\n", res.c_str());
		
		return false;	
	}

	return true;
}