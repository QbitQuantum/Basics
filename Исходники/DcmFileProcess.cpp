int DcmFileProcess::readAllDcm(const char* FilePath, std::vector<float>& position)
{
	//构造类对象  
	CStatDir statdir;
	std::vector<std::string> AllDcmFile;

	position.clear();
	float min_axial = 1000.0f;
	float max_axial = -1000.0f;
	float init_x = 0.0f;
	float init_y = 0.0f;
	float pixelspacing = 0.0f;

	int count = 0;
	//设置要遍历的目录  
	if (!statdir.SetInitDir(FilePath))
	{
		puts("目录不存在");
	}
	//开始遍历,获取该文件夹下所有dcm格式图像，一般为一个病患
	AllDcmFile.clear();
	AllDcmFile = statdir.BeginBrowseFilenames("*.dcm");
	//创建缓冲文件夹
	createCache();
	std::string dirName = GetExePath();
	dirName += "\\cache\\";

	cv::Mat mat[710];

	// 获取原始dcm图像的前缀目录
	std::string subImageName = dirName;
	// 获取原始dcm图像的前缀目录的string转换为char*
	const char *chSubImageName = subImageName.c_str();

	for (auto iter = AllDcmFile.cbegin(); iter != AllDcmFile.cend(); iter++)
	{
		// 将原始dcm图像的string转换为char*
		const char *chImageName = (*iter).c_str();
		// 基于dcmtk实现类
		THU_STD_NAMESPACE::TDcmFileFormat dcm = THU_STD_NAMESPACE::TDcmFileFormat(chImageName);

		std::string result = dcm.getImagePositionPatient();
		std::vector<std::string> ImagePosition;
		split(result, "\\", ImagePosition);
		float axial = (float)atof(ImagePosition[2].c_str());
		if (axial > max_axial) max_axial = axial;
		if (axial < min_axial) min_axial = axial;
		// 得到世界坐标的初始值
		if (count < 1)
		{
			init_x = (float)atof(ImagePosition[0].c_str());
			init_y = (float)atof(ImagePosition[1].c_str());

			// 获取dcm图像的PixelSpacing
			std::string space = dcm.getPixelSpacing();
			std::vector<std::string> PixelSpacing;
			split(space, "\\", PixelSpacing);
			pixelspacing = (float)atof(PixelSpacing[0].c_str());
		}
		
		// 获取dcm图像的InstanceNumber
		int InstancePosition = dcm.getPositionNumber();
		// 生成bmp图像存储路径
		char BmpName[256];
		sprintf_s(BmpName, "%s%06d.bmp", chSubImageName, InstancePosition);
		// 进行图像转换
		dcm.setWindow(715, 3478);
		dcm.saveToBmp(BmpName);
		//读取所有dcm图像构造三维数组
		cv::Mat temp = cv::imread(BmpName, cv::IMREAD_GRAYSCALE);
		mat[InstancePosition - 1] = temp;

		count++;
	}

	position.push_back(max_axial);
	position.push_back(min_axial);
	position.push_back((max_axial - min_axial) / count);
	position.push_back(init_x);
	position.push_back(init_y);
	position.push_back(pixelspacing);

	//多线程需要处理的线程数，分别对应矢状位与冠状位
	const int THREAD_NUM = 2;
	HANDLE handle[THREAD_NUM];
	//构造子线程参数结构体
	ThreadInfo threadInfo;
	threadInfo.dirName = dirName;
	threadInfo.count = count;
	for (int i = 0; i < count; i++)
		threadInfo.mat[i] = mat[i];
	//Coronal子线程
	handle[0] = (HANDLE)_beginthreadex(NULL, 0, ThreadCoronal, &threadInfo, 0, NULL);
	//Sigattal子线程
	handle[1] = (HANDLE)_beginthreadex(NULL, 0, ThreadSagittal, &threadInfo, 0, NULL);
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	return count;
}