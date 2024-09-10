void CFirstPageDlg::OnFpTest()
{

	if(bRecording==FALSE){
		//mean that stay in the state of Stop.
		//click the button can triger the behavior of record.
		pBuffer1=(PBYTE)malloc(INP_BUFFER_SIZE);
		pBuffer2=(PBYTE)malloc(INP_BUFFER_SIZE);
		if (!pBuffer1 || !pBuffer2) {
			if (pBuffer1) free(pBuffer1);
			if (pBuffer2) free(pBuffer2);
			MessageBeep(MB_ICONEXCLAMATION);
			AfxMessageBox(TEXT("Memory erro!"));//TEXT()
			return ;
		}
	
		//open waveform audo for input
		//fill in the structure WAVEFORMATEX
		waveform.wFormatTag=WAVE_FORMAT_PCM; //PCM pulse code modulation
		waveform.nChannels=1;
		waveform.nSamplesPerSec=11025;//sample rate =25khz
		waveform.nAvgBytesPerSec=11025;//ave data rate = 25khz
		waveform.nBlockAlign=1;
		waveform.wBitsPerSample=8; //8 bits per sample
		waveform.cbSize=0;

	
		if (waveInOpen(&hWaveIn,WAVE_MAPPER,&waveform,(DWORD)this->m_hWnd,NULL,CALLBACK_WINDOW)) {
			free(pBuffer1);
			free(pBuffer2);
			MessageBeep(MB_ICONEXCLAMATION);
			AfxMessageBox(_T("Audio can not be open!"));
		}
		//PWAVEHDR pWaveHdr1,pWaveHdr2;
		pWaveHdr1->lpData=(LPSTR)pBuffer1;
		pWaveHdr1->dwBufferLength=INP_BUFFER_SIZE;
		pWaveHdr1->dwBytesRecorded=0;
		pWaveHdr1->dwUser=0;
		pWaveHdr1->dwFlags=0;
		pWaveHdr1->dwLoops=1;
		pWaveHdr1->lpNext=NULL;
		pWaveHdr1->reserved=0;
	
		waveInPrepareHeader(hWaveIn,pWaveHdr1,sizeof(WAVEHDR));
	
		pWaveHdr2->lpData=(LPSTR)pBuffer2;
		pWaveHdr2->dwBufferLength=INP_BUFFER_SIZE;
		pWaveHdr2->dwBytesRecorded=0;
		pWaveHdr2->dwUser=0;
		pWaveHdr2->dwFlags=0;
		pWaveHdr2->dwLoops=1;
		pWaveHdr2->lpNext=NULL;
		pWaveHdr2->reserved=0;
	
		waveInPrepareHeader(hWaveIn,pWaveHdr2,sizeof(WAVEHDR));
	
		//////////////////////////////////////////////////////////////////////////
		pSaveBuffer = (PBYTE)realloc (pSaveBuffer, 1) ;
		// Add the buffers
	
		waveInAddBuffer (hWaveIn, pWaveHdr1, sizeof (WAVEHDR)) ;
		waveInAddBuffer (hWaveIn, pWaveHdr2, sizeof (WAVEHDR)) ;
	
		// Begin sampling
		this->showMsg+=_T("Recording...\r\n");
		((CEdit *)GetDlgItem(IDC_FP_TESTOUT))->SetWindowText(this->showMsg);
		dwDataLength = 0 ;
		
		waveInStart (hWaveIn) ;

	}
	else{
		//bRecording == TRUE
		//Recording state,click the button will stop recording and finish the Test.
		if(bRecording){
			//bEnding=TRUE;
			waveInReset(hWaveIn);//stop the record!
		}
		bRecording = FALSE;
		CString filepath;
		filepath = _T("E:\\Speechdata\\Test");
		//find the directory
		if(!PathIsDirectory(filepath)){
			CreateDirectory(filepath,NULL);
		}
		//set the test filename
		CTime current = CTime::GetCurrentTime();
		CString filename;
		int y = current.GetYear();
		int m = current.GetMonth();
		int d = current.GetDay();
		int h = current.GetHour();
		int min = current.GetMinute();
		int s = current.GetSecond();
		filename.Format(_T("%d%d%d%d%d%d"),y,m,d,h,min,s);
		filename+=".wav";
		filepath+=_T("\\")+filename; 
		
		CFileFind find;
		if(!find.FindFile(filepath)){
			save(filepath);
		}
		find.Close();

		USES_CONVERSION;// #define CString to char *
	
		//CStdioFile myfile;
		CString file1;
		CString folderName = _T("E:\\Speechdata\\");
		file1=_T("speakerdata.mat");
		//file2=_T("NameTable.txt");
		file1=folderName+file1;	//E:\\Speechdata\\speakerdata.mat
		//file2=folderName+file2;
		

		//make sure the corresponse of the file1 and file2
		CFileFind find1;
		//CFileException fileException;
		if(!find1.FindFile(file1)){
			Initial();
			/*
			if(find2.FindFile(file2)){
				myfile.Remove(file2);		
				if(!myfile.Open(file2,CFile::modeCreate,&fileException)){
					AfxMessageBox(_T("Create Failure!"));
				}
				
			}
			find2.Close();
			*/
		}	
		find1.Close();

		char* mysph=W2A(filename);
		mwArray speaker;//store the output
		mwArray sphName(mysph);
		try {
			//TestSpeech(int nargout, mwArray& pytest, const mwArray& SpeechName);
			TestSpeech(1,speaker,sphName);

			//conversion from mwArray to CString.
			mwString str=speaker.ToString();
			const char* pytest = (const char*)str;
			CString name;
			name=pytest;
			
			CTime current = CTime::GetCurrentTime();
			CString curtime;
			int h = current.GetHour();
			int min = current.GetMinute();
			int s = current.GetSecond();
			curtime.Format(_T("%02d:%02d:%02d"),h,min,s);
			this->showMsg+=curtime+_T(":")+name+_T("\r\n");//Display the outcome of TEST
			
			((CEdit *)GetDlgItem(IDC_FP_TESTOUT))->SetWindowText(this->showMsg);
			//显示用户信息（姓名，编号，部门等）；

			Users signer;
			if(!signer.isExist(name,_T("train"))){
				AfxMessageBox(_T("Invalid users or the existence of inconformity."));
				return;
			}
			signer.GetUserInfo(name);

			CString signerinfo;
			signerinfo.Format(_T("UserName:%s\r\nUserId:%s\r\nDepartment:%s\r\nEmail:%s\r\n"),signer.getUserName(),signer.getUserId(),signer.getDep(),signer.getEmail());
			UINT inret = MessageBox(signerinfo,_T("测试ing"),MB_ICONQUESTION|MB_OKCANCEL);
			if(inret==IDCANCEL){
				ErrorCnt++;
				if(ErrorCnt == 2){
					AfxMessageBox(_T("Your stored information may have been destroyed.Please contact the Administrator to re-enrollment"));
				}
				AfxMessageBox(_T("SignIn Error: identity discrepancy.Leave %d times to try again!"),2-ErrorCnt);
				return;
			}
			else if(inret == IDOK){
				//flush the signer's signin record.
				//userid timetoarrive
				current = CTime::GetCurrentTime();
				int year = current.GetYear();
				int month = current.GetMonth();
				int day = current.GetDay();

				int hour = current.GetHour();
				int minute = current.GetMinute();
				int second = current.GetSecond();
				CString signtime,signdate;
				signdate.Format(_T("%d/%d/%d"),month,day,year);
				signtime.Format(_T("%02d:%02d:%02d"),hour,minute,second);
				signer.setDTA(signdate);
				signer.setTTA(signtime);

				if(signer.InsertSignIn())
					AfxMessageBox(_T("SignIn Success"));
				else
					AfxMessageBox(_T("SignIn Error"));
				
				this->showMsg="";
				ErrorCnt=0;
			}
			
		}
		catch(const mwException &e){
			 CString ex;
			 char *str=(char *)e.what();
			 str[strlen(e.what())]='\0';
			 ex=str;
			 //display
			 this->showMsg+=ex+_T("\r\n");
			 ((CEdit *)GetDlgItem(IDC_FP_TESTOUT))->SetWindowText(this->showMsg);
			 
			 CString caption=_T("warning");
			 MessageBox(ex,caption);
		}
	}

}