void CDlgCapCam::Start(void)
{
	int i;
	printf("capcam start\r\n");	
	UpdateData();

	m_trigger_snatch_time = 0;
	m_trigger_index  = 0;

	//抓拍参数
	m_snatch_count =0 ;
	m_snatch_intertime = 0;
	m_snatch_pretime = 0;

	if (!m_flg_process)
	{
		//使用的设备序号
		m_index_device = m_combo_list_device.GetCurSel();
		//每次start，都生成一个新的事件记录文件
		//设置相关的其他文件路径
		__time32_t cur_time;
		struct tm * now_time;

		_time32(&cur_time);
		now_time = _localtime32(&cur_time);

		i=config_path.ReverseFind(_T('\\'));
		event_file_path = config_path.Left(i) + _T("\\event\\");
		event_file_path.AppendFormat(_T("_CAM%04d%02d%02d-%02d%02d%02d.csv"), now_time->tm_year+1900, now_time->tm_mon+1, now_time->tm_mday, now_time->tm_hour, now_time->tm_min, now_time->tm_sec);

		((CSTEvaluationDlg*)pWndParent)->event_file_path = event_file_path;
		//记录开始时间
		m_start_time = cur_time;
		//抓拍参数
		m_snatch_count =0 ;
		m_snatch_intertime = 0;
		m_snatch_pretime = 0;
		ResetEvent(m_proc_flgexit);
		m_proc_handle = CreateThread( 
			NULL,              // default security attributes
			0,                 // use default stack size  
			thread_proc,          // thread function 
			this,             // argument to thread function 
			0,                 // use default creation flags 
			NULL);   // returns the thread identifier 
		if (m_proc_handle)
		{
			m_flg_process = TRUE;
		}
		else
		{
			printf("create proc thread failed!\r\n");
		}

		Invalidate();
	}
	else
	{
		;
	}

}