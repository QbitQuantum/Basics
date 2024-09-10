void HttpTrans::recvData(const int& code, FILE* fp, const int& id, const int& reDirectCount)
{
	//std::unique_lock<std::mutex> lock(lock_);
	std::wstring rsp;
	if ( fp )
	{
		fseek(fp, 0L, SEEK_END);
		long length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		if ( length > 0 )
		{
			char* szBuf = new char[length+1];
			memset(szBuf, 0, length + 1);
			if (fread_s(szBuf, length + 1, 1, length, fp) > 0){
				rsp = cyjh::UTF8ToUnicode(szBuf);
				delete[]szBuf;
			}
		}
	}
	std::shared_ptr<resp_context_> parm(new resp_context_);
	parm->id_ = id;
	parm->errcode_ = code;
	parm->head_ = " ";
	parm->body_ = " ";

	int i = 0;
	int pos = 0;
	while (i < reDirectCount)
	{
		pos = rsp.find(L"\r\n\r\n");
		if ( pos > 0 )
		{
			rsp.erase(0, pos + 4);
		}
		++i;
	}

	pos = rsp.find(L"\r\n\r\n");
	if ( pos > 0 )
	{
		std::wstring whead = rsp.substr(0, pos);
		int size = rsp.size() - pos - 4;
		if ( size > 0 )
		{
			std::wstring wbody = rsp.substr(pos + 4, size);
			parm->body_ = cyjh::UnicodeToUTF8(wbody);
		}
		parm->head_ = cyjh::UnicodeToUTF8(whead);
	}
	CefPostTask(TID_UI, base::Bind(&ackData, parm));
}