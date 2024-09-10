void CyuchuandemoDlg::WriteLog(int hd,CString WriteLog)
	{	
	CEdit *pEdit;	
	pEdit = (CEdit *)GetDlgItem(IDC_EDITLOG);
	int  nLen=0;
	nLen = pEdit->GetWindowTextLength ();
	pEdit->SetFocus ();
    pEdit->SetSel(nLen, nLen);

	if (hd==DAS_OK)
	WriteLog=WriteLog+"    数据接收正常";
	else if (hd==Comm_Init_Err)
	WriteLog=WriteLog+"    错误原因：串口初始化错误！";
	else if (hd==CommPort_Err)
	WriteLog=WriteLog+"    错误原因：端口错误！";
	else if (hd==CommPort_Err)
	WriteLog=WriteLog+"    错误原因：端口错误！";
	else if (hd==Chksum_Err)
	WriteLog=WriteLog+"    错误原因：通讯数据效验错误！";
	else if (hd==Rev_Data_Err)
	WriteLog=WriteLog+"    错误原因：接收数据失败！";
	else if (hd==TIME_OUT_Err)
	WriteLog=WriteLog+"    错误原因：通讯超时错误！";
	else if (hd==Para_Err)
	WriteLog=WriteLog+"    错误原因：参数错误！";
	else if (hd==Send_Data_Err)
	WriteLog=WriteLog+"    错误原因：发送数据失败！";
	else if (hd==Get_status_Err)
	WriteLog=WriteLog+"    错误原因：接收状态位错误！";
	else if ((hd==No_Data_Return)||(hd==No_BIN_Files)||(hd==Read_Files_ERR))
	WriteLog=WriteLog+"    错误原因：没有数据返回！";
	else if (hd==CRC_ERR)
	WriteLog=WriteLog+"    错误原因：CRC效验错误！";
	else if (hd==Rev_LEN_Err)
	WriteLog=WriteLog+"    错误原因：接收长度溢出！";
	else if (hd==Password_Err)
	WriteLog=WriteLog+"    错误原因：授权密码错误！";
	else if (hd==Password_Para_Err)
	WriteLog=WriteLog+"    错误原因：密码格式错误！";
	else if (hd==Encrypt_Err)
	WriteLog=WriteLog+"    错误原因：数据加密错误！";
	else if (hd==Wrong_DEV_Err)
	WriteLog=WriteLog+"    错误原因：设备物理ID号不符！";
	else if (hd==No_Record_Err)
	WriteLog=WriteLog+"    错误原因：没有流水！";
	else
    WriteLog=WriteLog+"    ";
	WriteLog = WriteLog+"\r\n";
	pEdit->ReplaceSel (WriteLog);
	nLen = pEdit->GetLineCount();
	//pEdit->LineScroll(nLen, nLen);
	//pEdit->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_BOTTOM,0),0);
	if( nLen >= 150 )
	{
		pEdit->SetWindowText("");
	}
	}