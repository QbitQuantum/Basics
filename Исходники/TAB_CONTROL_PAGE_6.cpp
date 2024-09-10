static ErrNo GetMatrix(const HWND hwndEdit,double **pMatrix,const int nRows,const int nColumns)
{
	TCHAR	szBuffer_t[MAXSIZE];
	bool	data = false;
	TCHAR	seps[] = TEXT(" \t");
	TCHAR	*ptemp,*pstr,*pnext_token = NULL,*szBuffer = NULL;
	int		iLine,iLength,iStart,iCount;
	int		iMax = nColumns*20;							//缺憾 获取数据还是有限定的 每行字符个数不能超过iMax个

	szBuffer = new TCHAR[iMax];		//存储每一行获得的字符

	iLine = Edit_GetLineCount(hwndEdit);
	if(iLine == 1)											 //判断是否没有输入数据
	{
		if(!(iLength = Edit_GetText(hwndEdit,szBuffer,iMax)))
		{
			return NO_DATA_INPUT;
		}
	}
	else if(iLine<nRows)
	{
		return WRONG_MATRIX;
	}

	data = false;
	for(int i=0;i<iLine;i++)
	{
		iLength = Edit_GetLine(hwndEdit,i,szBuffer_t,MAXSIZE);
		if(iLength)				//找出第一个有数据的行
		{
			for(int j=0;j<iLength;j++)
			{
				if((szBuffer_t[j] >= TEXT('0') && szBuffer_t[j] <= TEXT('9')) || szBuffer_t[j] == TEXT('.'))
				{
					iStart = i;
					data = true;
					break;
				}
			}
			if(data)
				break;
		}
	}

	for(int i=iStart,k=0;i<iStart+nRows;i++,k++)			//获取每行数据
	{
		iCount = 0;
		iLength = Edit_GetLine(hwndEdit,i,szBuffer,iMax-1);
		szBuffer[iLength]=TEXT('\0');
		//字符串分割
		pstr = wcstok_s(szBuffer,seps,&pnext_token);
		while(pstr!=NULL)
		{
			if(*pstr == TEXT('+'))								//判断是否有分割行							
				return WRONG_MATRIX;	
			else if(!CharacterJudgement(pstr))					//判断是否非法字符输入
				return INCORRECT_DATA;
			if(iCount >= nColumns)								//判断每行输入数据个数是否超出限定矩阵维数
				return WRONG_MATRIX;
			pMatrix[k][iCount] = wcstod(pstr,&ptemp);
			pstr = wcstok_s(NULL,seps,&pnext_token);
			iCount++;
		}
		if(iCount != nColumns)
			return WRONG_MATRIX;
	}

	delete szBuffer;
	szBuffer = NULL;
	return 0;
}