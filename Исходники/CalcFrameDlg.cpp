void CCalcFrameDlg::OnBnClickedBtJiecheng()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_fact);

	if ( (m_strOutPut.Find('.') != -1) || (m_strOutPut.Find('-') != -1) )
	{
		m_strOutPut = TEXT("无效输入");
		return;
	}

	int nInput = atoi(m_strOutPut);

	if ( nInput*5 > 10000 ) 
	{
		m_strOutPut = TEXT("溢出");
		UpdateData(FALSE);
		return;
	}

	int *pArray = new int[nInput*5];

	for (int i=0;i<nInput*5;i++) pArray[i] = 1;

	int i=0,c=0,m=0;
	for(;nInput;nInput--)
	{
		for(c=i=0;i<=m;i++)
			pArray[i]=(c+=pArray[i]*nInput)%10,c/=10;

		while(c)pArray[++m]=c%10,c/=10;
	}

	m_strOutPut = TEXT("");

	int nValue=0;

	//数字大于28位，用科学表示法显示
	if( m>=32 )
	{
		for (int i=0;i<=32;i++)
		{
			nValue = pArray[m--];
			m_strOutPut.Insert(i,ITOA(nValue));
		}

		m_strOutPut.Insert(1,'.');
		m_strOutPut+=TEXT("e+");

		CString str;
		str.Format(TEXT("%d"),m+33);
		m_strOutPut+=str;
	}
	else
	{
		for(int nIndex=0;m>=0;nIndex++)
		{
			nValue = pArray[m--];
			m_strOutPut.Insert(nIndex,ITOA(nValue));
		}
	}

	SafeDeleteArray(pArray);

	UpdateData(FALSE);
}