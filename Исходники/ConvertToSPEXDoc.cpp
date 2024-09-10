BOOL CConvertToSPEXDoc::WriteSpx(CString &spxPath)
{
  // write a spx file

  // for writing 
  short myint16;
  float ftemp;
  int   ntemp;
  CFile SpexFile;

  char buff[1024];
  
  CString cstrT, cstrMsg;
  int nY,nM,nD,nh,nm,ns;

  cstrT = cstrDateTime.Mid(0,2);
  nM = atoi((LPCTSTR)cstrT);
  cstrT = cstrDateTime.Mid(3,2);
  nD = atoi((LPCTSTR)cstrT);
  cstrT = cstrDateTime.Mid(6,4);
  nY = atoi((LPCTSTR)cstrT);

	cstrT = cstrDateTime.Mid(11,2);
	nh = atoi((LPCTSTR)cstrT);
	cstrT = cstrDateTime.Mid(14,2);
	nm = atoi((LPCTSTR)cstrT);
	cstrT = cstrDateTime.Mid(17,2);
	ns = atoi((LPCTSTR)cstrT);

	COleDateTime startTime(nY,nM,nD,nh,nm,ns);


	if(NULL==SpexFile.Open((LPCTSTR)spxPath,CFile::modeCreate|CFile::modeWrite| CFile::typeBinary))
	{
		cstrMsg=_T("Can not create file:\r\n");
		cstrMsg=cstrMsg+spxPath;
		AfxMessageBox((LPCTSTR)cstrMsg);
		return FALSE;
	}

	FillMemory(buff,1024,0);
	SpexFile.Write(buff,444);
	//skip id
	SpexFile.Seek(64,CFile::begin);
	//write comments;
	SpexFile.Write((LPCTSTR)cstrComment,MY_MIN(64,cstrComment.GetLength()));
	//skip fl,dr
	SpexFile.Seek(176,CFile::begin);
	//write operator
	SpexFile.Write((LPCTSTR)cstrUserName,MY_MIN(16,cstrUserName.GetLength()));
	SpexFile.Seek(192,CFile::begin);
	//data length
	myint16=nDA;  
	SpexFile.Write(&myint16,sizeof(WORD));
	//scan num
	myint16=nSN;
	SpexFile.Write(&myint16,sizeof(WORD));
	//CF
	ftemp=(float)dCF;
	SpexFile.Write(&ftemp,sizeof(float));
	//SW
	ftemp=(float)dSW;
	SpexFile.Write(&ftemp,sizeof(float));
	//TM
	ftemp=(float)dTM;
	SpexFile.Write(&ftemp,sizeof(float));
	//FQ  
	ftemp=(float)dFQ;
	SpexFile.Write(&ftemp,sizeof(float));
	//RG
	ftemp=(float)dRG;
	SpexFile.Write(&ftemp,sizeof(float));
	//MA
	ftemp=(float)dMA;
	SpexFile.Write(&ftemp,sizeof(float));
	//MF
	ftemp=(float)dMF;
	SpexFile.Write(&ftemp,sizeof(float));
	//PW
	ftemp=(float)dPW;
	SpexFile.Write(&ftemp,sizeof(float));
	//TC
	ftemp=(float)dTC;
	SpexFile.Write(&ftemp,sizeof(float));
	//PH
	myint16=nPH;
	SpexFile.Write(&myint16,sizeof(WORD));
	//OF
	myint16=nOF;
	SpexFile.Write(&myint16,sizeof(WORD));
	//TE
	ftemp=(float)nTE;
	SpexFile.Write(&ftemp,sizeof(float));


	int np=0;
	COleDateTimeSpan pastTime(0L,0,0, (int)(dTM*np+0.5));
	COleDateTime curTime = startTime + pastTime;

	cstrDateTime.Format(_T("%02d-%02d-%04d %02d:%02d:%02d"),
		curTime.GetMonth(), curTime.GetDay(),
		curTime.GetYear (), curTime.GetHour(),
		curTime.GetMinute(),curTime.GetSecond());

	//DATE
	SpexFile.Write((LPCTSTR)cstrDateTime.Left(10),10);             //DATE
	//TIME
	SpexFile.Seek(6,CFile::current);
	SpexFile.Write((LPCTSTR)cstrDateTime.Right(8),8);             //DATE
	SpexFile.Seek(444,CFile::begin);

	for(int i=np*nDA;i<(np+1)*nDA;i++)
	{
		if(fpdata[i]>0)
			ntemp=(int)(fpdata[i]+0.5);
		else
			ntemp=(int)(fpdata[i]-0.5);
		SpexFile.Write(&ntemp,sizeof(int));
	}

	ntemp=int(MY_MAX(fmax,fabs(fmin))+0.5);
	ntemp=(int)((ceil)(log10((double)ntemp)/log10(2.0)));

	SpexFile.Seek(434,CFile::begin);
	SpexFile.Write(&ntemp,sizeof(int));

	SpexFile.Close();


  return TRUE;
};