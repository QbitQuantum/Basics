	void CFileReceiver::_dealWithReceivedFile(TProxyPtr sender,TFileRequestPtr theRequest,const NLNET::TBinBuffer& data)
	{
		// log progress..
		_clearDownloadLog(theRequest->FileName);
		_log("receivedFile: "+theRequest->FileName+NLMISC::toString("(%d bytes)",data.getBufferSize()));

		// call the user callback for the file data
		NLMISC::CMemStream memStream;
		memStream.fill(data.getBuffer(),data.getBufferSize());
		memStream.invert();
		cbFileDownloadSuccess(theRequest->FileName,memStream);

		// look for the proxy record for the emitter
		TProxies::iterator pit= _Proxies.find(sender);
		BOMB_IF(pit==_Proxies.end(),"ERROR: Failed to identify the sender for the received file: "+theRequest->FileName,return);

		// liberate this request
		for (TFileRequests::iterator fit=_FileRequests.begin(); fit!=_FileRequests.end();++fit)
		{
			if (*fit==theRequest)
			{
				_FileRequests.erase(fit);
				break;
			}
		}

		// cleanup the emitter
		pit->second.CurrentRequest= NULL;

		// look for a new job for the sender
		_lookForNewJob(pit->second);
	}