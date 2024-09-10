// 在播放惯性数据前，将所有的视觉数据读出
void CHybidTrack::Read_M_otherMakers_OffLine()
{
	errno_t err;
	err = fopen_s(&m_OptStream, m_Opt_Path, "r");
	if (err == 0)
	{
		printf("The file '...Opt.txt' was opened\n");
	}
	else
	{
		printf("The file '...Opt.txt' was not opened\n");
	}

	char str[100];
	int min = 0, sec = 0, msec = 0;
	int min_last = 0, sec_last = 0, msec_last = 0;
	int OtherMarkersN;
	float_t x = 0, y = 0, z = 0;
	int res = 1;
	res = fscanf_s(m_OptStream, "%[^\n]%*c", str, _countof(str)); // 第一行是 头
	// 第二行之后是数据
	VisionData.clear();
	
	float fLatency = 0;
	int m_mappingInertial_k;
	int VN;
	while (res != EOF)
	{
		// 读取一个时刻的数据
		res = fscanf_s(m_OptStream, "%d:%d:%d", &min,&sec,&msec);
		res = fscanf_s(m_OptStream, "%d", &OtherMarkersN);
		
		CVisionData_t CVisionData_Cur;
		CVisionData_Cur.m_OtherMarkersN = OtherMarkersN;

		for (int k = 0; k < OtherMarkersN; k++)
		{
			res = fscanf_s(m_OptStream, "%f %f %f", &x, &y, &z);
			Point3D_t OtherMarker_i(x, y, z);
			CVisionData_Cur.m_OtherMarkersP.push_back(OtherMarker_i);  // 更新一个马克点位置
		}
	

		// 计算 fLatency
		if (!VisionData.empty())
		{
			float timeStep = (min-min_last)*60+(sec-sec_last)+(msec-msec_last)/1000.0 ;
			fLatency += timeStep;
		}
		min_last = min;
		sec_last = sec;
		msec_last = msec;

		// 根据 m_fLatency 和惯性的频率计算 m_mappingInertial_k
		m_mappingInertial_k = fLatency*m_I_Frequency + 1;
		VN = VisionData.size();
		for (int i = 0; i < 10; i++)
		{
			int temp = InertialData_visual_k[m_mappingInertial_k - i-1];
			if (temp != VN - 1 && temp!=VN)
				InertialData_visual_k[m_mappingInertial_k - i-1] = VN + 1; // 从当前往前都写 visualN
			else
				break;
		}

		CVisionData_Cur.m_fLatency = fLatency;
		CVisionData_Cur.m_Timecode = 0;
		CVisionData_Cur.m_TimecodeSubframe = 0;
		CVisionData_Cur.m_fTimestamp = 0;

		CVisionData_Cur.m_mappingInertial_k = m_mappingInertial_k; // 需要后续重新计算  m_mappingInertial_k ！！！

		// 更新视觉数据到列表的末尾    不允许自动扩容
		if (VN == V_BufferN)
		{
			VisionData.pop_front();	// 已存储足够多的数据，列表满了，先删除最早的（列表首部）
		}
		VisionData.push_back(CVisionData_Cur);  // 最新的放在最末尾
		// 用 m_fLatency 近似计算频率
		CalVisualFrequency();
		// 将 CVisionData_Cur 更新到 M_otherMakers
		Get_M_otherMakers();
	}

	// Close stream if it is not NULL 
	if (m_OptStream)
	{
		err = fclose(m_OptStream);
		if (err == 0)
		{
			printf("The file '...Opt.txt' was closed\n");
		}
		else
		{
			printf("The file '...Opt.txt' was not closed\n");
		}
	}
	m_fLatency_StartTwo = 0;
}