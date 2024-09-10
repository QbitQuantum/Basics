void CDIP_ProgrammingMyClass::MyClass_EnhancementMedianFilter(void)
{
	UCHAR** ppTemp;

	UCHAR** ppMedianMask;

	int masksize=m_uiMedianFilterMaskSize*m_uiMedianFilterMaskSize;

	ppMedianMask=MyClass_MemoryAlloc2D(m_uiMedianFilterMaskSize, m_uiMedianFilterMaskSize);

	m_ppcPaddedImage=MyClass_MemoryAlloc2D(m_uiHeight+m_uiMedianFilterMaskSize-1, m_uiWidth+m_uiMedianFilterMaskSize-1);

	ppTemp=m_ppcModifiedImage;

	MyClass_Padding(m_ppcLoadedImage);

	m_ppcWindow=MyClass_MemoryAlloc2D(m_uiMedianFilterMaskSize, m_uiMedianFilterMaskSize);

	UCHAR *ucSorted=new UCHAR[masksize];


	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			MyClass_Window(i, j);
			for(int k=0;k<masksize;k++)
			{
				ucSorted[k]=m_ppcWindow[0][k];
			}
			sort(ucSorted, ucSorted+masksize);
			
			ppTemp[i][j]=ucSorted[(masksize)>>1];
			
		}
	}


	m_pcSaveImage=new UCHAR[m_uiHeight*m_uiWidth];

	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			m_pcSaveImage[i*m_uiWidth+j]=m_ppcModifiedImage[i][j];
		}

	}

	char filename[100]="../MedianFilter_";
	char cMasksize[3]="";
	itoa(m_uiMedianFilterMaskSize, cMasksize, 10);
	strcat(filename, cMasksize);
	strcat(filename, ".raw");

	ofstream fWrite(filename, ios::out | ios::binary);



	fWrite.write((const char*) m_pcSaveImage, m_uiHeight*m_uiWidth);

	fWrite.close();

	delete []m_pcSaveImage;

}