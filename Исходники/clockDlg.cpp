BOOL CclockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//设置程序运行时不在任务栏的运行区显示图标
	SetWindowLong(this->m_hWnd,GWL_EXSTYLE,WS_EX_TOOLWINDOW); 
	
	//设置控制时针走动的触发器为每秒一次，即引发WM_TIMER消息的频率是每秒一次。
	m_timer = this->SetTimer(1, 1000, NULL);
	
///////////////////////////////////////////////////////////////	
	CRgn  rgn;   
	CRect  rc;   
	GetClientRect(&rc);   
    rgn.CreateEllipticRgn(rc.left,rc.top,rc.right,rc.bottom);   
    SetWindowRgn(rgn,TRUE);   
    rgn.DeleteObject();  
//////////////////////////////////////////////////////////////
	CBitmap   bm;   
	bm.LoadBitmap(IDB_BITMAP1);   //   IDB_BITMAP1为BITMAP资源ID,可以指定bitmap图片的路径   
	m_brush.CreatePatternBrush(&bm);   

	//SoundTime();
	//sndPlaySoundA("AM.wav",SND_ASYNC);
	//将对话框的句柄传递到CWinSunApp类中。sunxin
//	((CclockApp*)AfxGetApp())->m_hwndDlg=m_hWnd;




	DWORD dwParam;
	pThread=AfxBeginThread(ThreadProc,&dwParam,THREAD_PRIORITY_HIGHEST,0,CREATE_SUSPENDED,0);
	if(pThread==NULL)
		AfxMessageBox("创建线程错误!");



	DWORD dwParam2;
	pThread2=AfxBeginThread(ThreadProc2,&dwParam2,THREAD_PRIORITY_HIGHEST,0,CREATE_SUSPENDED,0);
	if(pThread2==NULL)
		AfxMessageBox("创建线程错误!");



	DWORD dwParam3;
	pThread3=AfxBeginThread(ThreadProc3,&dwParam3,THREAD_PRIORITY_HIGHEST,0,CREATE_SUSPENDED,0);
	if(pThread3==NULL)
		AfxMessageBox("创建线程错误!");



	int temp=AfxGetApp()->GetProfileInt("Sound","hoursound",0);
	if(temp==1)
		hoursound=true;
	else
		hoursound=false;
	temp=AfxGetApp()->GetProfileInt("Sound","halfhoursound",0);
	if(temp==1)
		halfhoursound=true;
	else
		halfhoursound=false;



	ringnum=AfxGetApp()->GetProfileIntA("ring","ringnum",0);
	CString time;
	CString temps;
	for(int i=0;i<ringnum;i++)
	{
		temps.Format("ring%d",i+1);
		time=AfxGetApp()->GetProfileStringA("ring",temps);
		mytimearray[i].hour=(time[0]-48)*10+time[1]-48;
		mytimearray[i].minute=(time[3]-48)*10+time[4]-48;
		mytimearray[i].second=(time[6]-48)*10+time[7]-48;
	}

	tasknum=AfxGetApp()->GetProfileIntA("task","tasknum",0);
	CString taskdate;
	CString tasktime;
	for(int i=0;i<tasknum;i++)
	{
		temps.Format("taskdate%d",i+1);
		taskdate=AfxGetApp()->GetProfileStringA("taskdate",temps);
		temps.Format("tasktime%d",i+1);
		tasktime=AfxGetApp()->GetProfileStringA("tasktime",temps);
		mytaskarray[i].year=(taskdate[0]-48)*1000+(taskdate[1]-48)*100+(taskdate[2]-48)*10+taskdate[3]-48;
		mytaskarray[i].month=(taskdate[5]-48)*10+taskdate[6]-48;
		mytaskarray[i].day=(taskdate[8]-48)*10+taskdate[9]-48;
		mytaskarray[i].hour=(tasktime[0]-48)*10+tasktime[1]-48;
		mytaskarray[i].minute=(tasktime[3]-48)*10+tasktime[4]-48;
		mytaskarray[i].second=(tasktime[6]-48)*10+tasktime[7]-48;
		temps.Format("task%d",i+1);
		mytaskarray[i].typle=AfxGetApp()->GetProfileIntA("task",temps,0);
	}





	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}