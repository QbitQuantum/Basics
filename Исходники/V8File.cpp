ULONG CV8File::Deflate(unsigned char *DataIn, ULONG DataInSize, unsigned char **DataOut)
{
	// ������� ����� ����� �� string
    HRESULT hr;
    //USES_CONVERSION;

	/*
	IzlibEnginePtr iLibEngine;
	CoInitialize(NULL);
	hr = iLibEngine.CreateInstance(L"V75.zlibEngine");

	if (FAILED(hr))
	{
		AfxMessageBox("err");
		return 0;
	}
	*/
	
    IStreamPtr pStreamNew;
    IStream *pIStrNew;
    if (S_OK == CreateStreamOnHGlobal(NULL, TRUE, &pIStrNew))
	{
		pStreamNew.Attach(pIStrNew, false);
		
		
		ULONG pcbWritten = 0;
		if (pIStrNew->Write(DataIn, DataInSize, &pcbWritten) != S_OK)
		{
			AfxMessageBox("err");
			//pBkEndUI->DoMessageLine("pStreamOut->Read(&lpStr[0], cbStreamSizeOut, &pcbRead) != S_OK", mmBlackErr);	                            
			return 0;
		}              
		
	}
	
    LARGE_INTEGER __zero;
	__zero.QuadPart = __int64(0);
    if (pStreamNew->Seek(__zero, 0, NULL) == S_OK)
    {
	}
	
	
	ULONG cbStreamSizeOut;
    IStreamPtr pStreamOut;
    IStream *pIStrOut;
    if (S_OK == CreateStreamOnHGlobal(NULL, TRUE, &pIStrOut))
    {     
		pStreamOut.Attach(pIStrOut, false);
		try 
		{
			//CoInitialize(NULL);
			//IzlibEnginePtr iLibEngine;
			//hr = iLibEngine.CreateInstance(L"V75.zlibEngine");
			
			//if (FAILED(hr))
			//{
			//	//pBkEndUI->DoMessageLine("error iLibEngine->pkDecompress", mmBlackErr);          
			//	AfxMessageBox("err");
			//	return 0;
			//}
			
			hr = iLibEngine->pkCompress(pStreamNew, pStreamOut);            
			
			if (FAILED(hr))
			{
				//pBkEndUI->DoMessageLine("error iLibEngine->pkDecompress", mmBlackErr);          
				AfxMessageBox("err");
				return 0;
			}          
			else
			{          
				STATSTG St;
				pStreamOut->Stat(&St, STATFLAG_NONAME);
				cbStreamSizeOut = St.cbSize.LowPart;

				LARGE_INTEGER __zero;
				__zero.QuadPart = __int64(0);
				if (pStreamOut->Seek(__zero, 0, NULL) == S_OK)
				{
					
					*DataOut = (unsigned char*)realloc(*DataOut, cbStreamSizeOut);
					ULONG pcbRead = 0;
					if (pStreamOut->Read(*DataOut, cbStreamSizeOut, &pcbRead) != S_OK)
					{
						AfxMessageBox("err");
						//pBkEndUI->DoMessageLine("pStreamOut->Read(&lpStr[0], cbStreamSizeOut, &pcbRead) != S_OK", mmBlackErr);	                            
						return 0;
					}
				}
				else
				{
					AfxMessageBox("err");
					//pBkEndUI->DoMessageLine("pStreamOut->Seek(__zero, 0, NULL) != S_OK", mmBlackErr);	                            
					return 0;
				}
			}
			
		} 
		catch (_com_error& err) 
		{
			//CString str;
			//str.Format("V75.zlibEngine Error:%s", err.ErrorMessage());
			AfxMessageBox(err.ErrorMessage());
			//pBkEndUI->DoMessageLine(str, mmBlackErr);
			return 0;
		}                  
    }
    else
    {
		//pBkEndUI->DoMessageLine("error in CreateStreamOnHGlobal", mmBlackErr);    
		AfxMessageBox("err");
		return 0; 
    }        
    return cbStreamSizeOut;    

}