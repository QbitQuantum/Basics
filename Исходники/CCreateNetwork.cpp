void CCreateNetwork::BackPropagation(void)
{
	CPreferences* pfs=CPreferences::GetPreferences();

//	this->m_cNumThreads=pfs->m_cNumBackpropThreads;	   //初始化系统可以开启的BP线程数上限
	this->m_InitialEta=pfs->m_dInitialEtaLearningRate;  //初始化训练的学习速率
	this->m_MinimumEta=pfs->m_dMinimumEtaLearningRate;  //初始化学习速率的下限值
	this->m_EtaDecay=pfs->m_dLearningRateDecay;		   //初始化学习速率的下降速度
	this->m_AfterEvery=pfs->m_nAfterEveryNBackprops;	   //设定需要每个epoch进行的BP次数，大小达到时则调整学习速率
	this->m_StartingPattern=0;						   //设定首次进行训练的图片在数据集中的索引
	this->m_EstimatedCurrentMSE=0.10;
	
	//this->m_bDistortPatterns=TRUE;					   //是否需要对输入图像序列进行乱序处理
	this->m_bDistortPatterns=FALSE;					   //是否需要对输入图像序列进行乱序处理

	//输出当前网络参数的学习速率以及当前正输入网络参与训练的图片标识
	cout<<endl<<"******************************************************"<<endl;
	CString strInitEta;
	strInitEta.Format("Initial Learning Rate eta (currently, eta = %11.8f)\n", GetCurrentEta());
	cout<<strInitEta;
	cout<<endl<<"******************************************************"<<endl;

	///////////////////////////////////////////////////
	//
	//	在BP开始前，获取参与网络训练的文件目录下的训练文件信息
	//
	//////////////////////////////////////////////////
	CFileFind finder;
	CString filename;
	CString filepath;

	m_InfoFileNames.clear();
	m_InfoFilePaths.clear();
	m_ImageFilePaths.clear();
	
	BOOL isWorking=finder.FindFile(m_TrainInfoPath);
	while(isWorking)
	{
		isWorking=finder.FindNextFileA();
		filename=finder.GetFileName();
		filepath=finder.GetFilePath();

		m_InfoFileNames.push_back(filename);
		m_InfoFilePaths.push_back(filepath);

		//将对应图片的路径也保存下来
		this->m_TrainImagePath=m_TrainFilePath+filename.SpanExcluding(".")+".jpg";
		m_ImageFilePaths.push_back(m_TrainImagePath);
	}

	//////////////////////////////////////////////////
	////
	////   核心处理：m_pDoc->StartBackpropagation
	//////////////////////////////////////////////////
	BOOL bRet= this->StartBackpropagation( m_StartingPattern,
			m_InitialEta, m_MinimumEta, m_EtaDecay, m_AfterEvery, 
			m_bDistortPatterns, m_EstimatedCurrentMSE );
	if(bRet !=FALSE)
	{
		//m_iEpochsCompleted = 0;
		//m_iBackpropsPosted = 0;
		//m_dMSE = 0.0;

		////m_cMisrecognitions = 0;

		//m_dwEpochStartTime = ::GetTickCount();

		////控制台输出：BP周期完成的数目
		//CString str;
		//str.Format( _T("%d Epochs completed\n"), m_iEpochsCompleted );
		//cout<<str;
		
		//cout<<"Backpropagation started... \n";
	}
}