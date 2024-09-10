// 将采集到的数据保存到文件中
void CTabSample::OnSaveToFile(int iMathValueIdNum, int iGraphViewNum, char** cppSelectObjectName, vector <double>* dSampleData)
{
	CString strFileName = "";
	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);
	strFileName.Format("%s\\%04d%02d%02d%02d%02d%02d%04d.text", m_csSaveFilePath,sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	// 将ADC采样数据及运算结果保存成ANSI格式的文件
	errno_t err;
	FILE * savefile;
	CString strTemp = "";
	unsigned int iDataLength = 0;
	if((err = fopen_s(&savefile,strFileName,"w+"))==NULL)
	{
		CString strOutput = "";
		// 输出仪器标签
		for (int i=0; i<iGraphViewNum; i++)
		{
			strTemp.Format("%s\t\t",cppSelectObjectName[i]);
			strOutput += strTemp;
		}
		strOutput += "\r\n";

		// 输出各仪器采样数据
		for (unsigned int i=0; i<(m_iMaxLength-iMathValueIdNum); i++)
		{
			for (int j=0; j<iGraphViewNum; j++)
			{
				if (m_iSelectObject[j] == 1)
				{
					if (m_iSelectObjectNoise[j] == 0)
					{
						iDataLength = dSampleData[j].size()-iMathValueIdNum;
						if (iDataLength <= 0 )
						{
							strOutput += "\t\t";
							continue;
						}
						if (iDataLength > i)
						{	
							strTemp.Format("%2.9f\t",dSampleData[j][i]);
							strOutput += strTemp;
						}
						else
						{
							strOutput += "\t\t";
						}
					}
					else
					{
						strOutput += "\t\t";
					}
				}
				else
				{
					strOutput += "\t\t";
				}
			}
			strOutput += "\r\n";
		}

		strOutput += "\r\n数据处理结果：\r\n";

		// 输出仪器标签
		for (int i=0; i<iGraphViewNum; i++)
		{
			strTemp.Format("%s\t\t",cppSelectObjectName[i]);
			strOutput += strTemp;
		}
		strOutput += "\r\n";

		for (int i=0; i<iMathValueIdNum; i++)
		{
			if (i == 0)
			{
				strOutput += "平均值：\r\n";
			}
			else if (i == 1)
			{
				strOutput += "均方根：\r\n";
			}
			else if (i == 2)
			{
				strOutput += "最大值：\r\n";
			}
			else if (i == 3)
			{
				strOutput += "最小值：\r\n";
			}
			for (int j=0; j<iGraphViewNum; j++)
			{
				if (m_iSelectObject[j] == 1)
				{
					if (m_iSelectObjectNoise[j] == 0)
					{

						iDataLength = dSampleData[j].size()-iMathValueIdNum;
						if (iDataLength < 0)
						{
							strOutput += "\t\t";
							continue;
						}
						strTemp.Format("%2.9f\t",dSampleData[j][iDataLength+i]);
						strOutput += strTemp;
					}
					else
					{
						strOutput += "\t\t";
					}
				}
				else
				{
					strOutput += "\t\t";
				}
			}
			strOutput += "\r\n\r\n";
		}
		fprintf(savefile,"%s", strOutput); 
	}
	fclose(savefile); 
	//	数据采集结束后存ADC采样文件
	OnSaveADCDataToFile(iMathValueIdNum, iGraphViewNum, cppSelectObjectName, dSampleData, sysTime);
}