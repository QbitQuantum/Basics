UINT UploadWorker(LPVOID pVoidUpload)
{
	//AfxMessageBox("Worker Thread Started");
	//TRACE0("*** Upload Thread Started\n");

	CGnuUpload*      pUpload = (CGnuUpload*) pVoidUpload;
	CGnuUploadShell* pShell  = pUpload->m_pShell;
	CGnuNetworks*    pNet    = pShell->m_pNet;
	CGnuPrefs*		 pPrefs  = pShell->m_pPrefs;
	CGnuTransfers*   pTrans  = pShell->m_pTrans;

	int BytesRead = 0;
	int BytesSent = 0;

	byte pBuff[SEND_BUFF];


	// Stream Test
	/*byte chkBuff[SEND_BUFF];
	if(pShell->m_Name == "stream.mp3")
	{
		memset(pBuff, 0, SEND_BUFF);
		memset(chkBuff, 0, SEND_BUFF);
	}*/

	// Transport buffer mod test
	//int sendsize = SEND_BUFF;
	//int varlen = 4;
	//pUpload->SetSockOpt(SO_SNDBUF, &sendsize, varlen);


	while(pShell->m_Status == TRANSFER_SENDING)
		// If bytes still need to be sent
		if(pShell->m_CurrentPos < pShell->m_StopPos)
		{
			// Send chunk of bytes read from file
			if(BytesSent < BytesRead)
			{
				// Stream Test
				//if(pShell->m_Name == "stream.mp3")
				//	if( memcmp(pBuff, chkBuff, SEND_BUFF) != 0 )
				//		pShell->m_pNet->m_pCore->DebugLog("Upload Check Failed at " + CommaIze(NumtoStr(pShell->m_BytesSent)));


				int AttemptSend = pUpload->m_pSocket->Send(pBuff + BytesSent, BytesRead - BytesSent);
					

				if(AttemptSend == SOCKET_ERROR)
				{
					int code = pUpload->m_pSocket->GetLastError();
					if(code != WSAEWOULDBLOCK)
					{
						pShell->m_Error  = "Remotely Canceled";  // Make more descriptive
						pShell->m_Status = TRANSFER_CLOSED;	
					}
					else
					{
						// Send Logging
						//if( pShell->m_Sha1Hash.Left(4) == "F2K5" )
						//	pShell->m_pNet->m_pCore->DebugLog("Block: " + pShell->m_Name + " -- CurrentPos=" + NumtoStr(pShell->m_CurrentPos));

						WaitForSingleObject((HANDLE) pUpload->m_CanWrite, INFINITE);
						pUpload->m_CanWrite.ResetEvent();
						
						if(pShell->m_Status != TRANSFER_SENDING)
							break;
					}
				}
				else
				{
					// Upload post-send integrity check
					/*if(pShell->m_MirrorFile.m_hFile != CFile::hFileNull)
						pShell->m_MirrorFile.Write(pBuff + BytesSent, AttemptSend);

					if(pShell->m_CheckFile.m_hFile != CFile::hFileNull)
					{
						byte* CheckBytes = new byte[AttemptSend];
						
						pShell->m_CheckFile.Seek(pShell->m_CurrentPos, CFile::begin);
						pShell->m_CheckFile.Read(CheckBytes, AttemptSend);

						if( memcmp(pBuff + BytesSent, CheckBytes, AttemptSend) != 0 )
						{
							CString Problem = "Read Check Failed: " + pShell->m_Name + " -- ReadPos=" + NumtoStr(pShell->m_CurrentPos) + ", BytesSent=" + NumtoStr(BytesSent) + ", BytesSent=" + NumtoStr(AttemptSend);
							pShell->m_pTrans->m_pCore->DebugLog(Problem);
						}
						
						delete [] CheckBytes;
					}*/

					// Send Logging
					//if( pShell->m_Sha1Hash.Left(4) == "F2K5" )
					//	pShell->m_pNet->m_pCore->DebugLog("Sent: " + pShell->m_Name + " -- CurrentPos=" + NumtoStr(pShell->m_CurrentPos) + ", SentBytes=" + NumtoStr(AttemptSend));

					BytesSent			 += AttemptSend;
					pShell->m_CurrentPos += AttemptSend;
					pShell->m_BytesSent  += AttemptSend;
					pShell->m_AvgSentBytes.Input(AttemptSend);
				}

				if(!pShell->m_UpdatedInSecond)
					pShell->m_UpdatedInSecond = true;
			}

			// Get next chunk of bytes from file
			else
			{
				BytesSent = 0;
				BytesRead = 0;

				uint64 ReadSize = pShell->m_StopPos - pShell->m_CurrentPos;


				// If theres a bandwidth limit
				if(pPrefs->m_BandwidthUp)
				{
					if(pShell->m_AllocBytes <= 0)
					{
						pShell->m_AllocBytes = 0;

						pUpload->m_MoreBytes.ResetEvent();
						WaitForSingleObject((HANDLE) pUpload->m_MoreBytes, INFINITE);

						if(pShell->m_Status != TRANSFER_SENDING)
							break;
					}


					if(pShell->m_AllocBytes < ReadSize)
						ReadSize = pShell->m_AllocBytes;
				}
	

				if(SEND_BUFF < ReadSize)
					ReadSize = SEND_BUFF;


				// If file being uploaded is a partial
				if(pShell->m_IsPartial)
				{
					std::map<int, CGnuDownloadShell*>::iterator itPart = pTrans->m_DownloadMap.find(pShell->m_PartialID);

					if(itPart != pTrans->m_DownloadMap.end())
						BytesRead = itPart->second->GetRange(pShell->m_CurrentPos , pBuff, ReadSize);
				}
			
				// If tiger tree being sent
				else if(pShell->m_TigerTreeRequest)
				{
					memcpy(pBuff, pShell->m_TigerTree + pShell->m_CurrentPos, ReadSize);
					BytesRead = ReadSize;
				}

				// Normal file being uploaded
				else
				{
					try
					{
						// Stream Test
						/*if(pShell->m_Name == "stream.mp3")
						{
							BytesRead = ReadSize;
						}
						else
						{*/
							BytesRead = pShell->m_File.SeekandRead(pShell->m_CurrentPos, pBuff, ReadSize);
						//}

						// Send Logging
						//if( pShell->m_Sha1Hash.Left(4) == "F2K5" )
						//	pShell->m_pNet->m_pCore->DebugLog("Read: " + pShell->m_Name + " -- CurrentPos=" + NumtoStr(pShell->m_CurrentPos) + ", ReadBytes=" + NumtoStr(BytesRead));
						
					}
					catch(...)
					{
						pShell->m_Error  = "Error Reading File";
						pShell->m_Status = TRANSFER_CLOSED;
					}
				}
				
				
				if(pPrefs->m_BandwidthUp)
					pShell->m_AllocBytes -= BytesRead;


				if(BytesRead == 0)
				{
					pShell->m_Error  = "No Bytes Read from File";
					pShell->m_Status = TRANSFER_CLOSED;
				}
			}
		}

		// Else all bytes sent
		else
		{
			if(pShell->m_KeepAlive)
				pShell->m_Status = TRANSFER_CONNECTED;
			else
				pShell->m_Status = TRANSFER_CLOSED;	
		}


	// Make sure shell still exists
	for(int i = 0; i < pTrans->m_UploadList.size(); i++)
		if(pTrans->m_UploadList[i] == pShell)
		{
			pShell->m_UpdatedInSecond = true;

			if(pShell->m_Socket)
				pUpload->m_ThreadRunning = false;
		}


	//TRACE0("*** Upload Thread Ended\n");

	ExitThread(0);
}