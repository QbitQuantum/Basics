////////////////////////////////////////////////////////////////////////////////////////////////////////////
//函数：处理文件下载请求
//功能：收到文件下载请求，检验文件名合法性，会送合法文件名，文件大小
//输入：
//输出：
short CPRJ3_0613Dlg::StartSendFile(SOCKET s, int i)
{
	int buf_len;
	long retval;
	char *send_buf;
	FILE *fp;
	FilePDU file_pdu;

	fopen_s(&fp, FilePath[i], "rb");
	if (fp == NULL){
		//显示错误信息
		CString show_info;
		show_info += FilePath[i];
		show_info += "不存在！";
		//ShowInfo(show_info);

		///////////////////////////////////////////////告知用户发生错误
		//SendCtlPDU(s, RE_ERR_FILENAME);
		closesocket(s);///////////////////////////////////关闭套接字！还有后续！！！
		return -1;
	}

	//发送首帧
	file_pdu.type = FILE_PDU_TYPE;
	file_pdu.No = 0;
	retval = fread(file_pdu.buf, 1, FILE_BUF_SIZE, fp);
	file_pdu.len = retval;
	buf_len = 1 + 1 + 1 + retval;

	//send_buf = (char*)&file_pdu;
	retval = send(s, (char*)&file_pdu, buf_len, 0);
	if (retval <= 0){
		//返回值判定
		MessageBox(TEXT("数据连接发送数据PDU！"), TEXT("数据连接错误"), MB_OK);
		return retval;
	}

	sock_status[i] = S_SENDFILE_0;
	file_pointer[i] = fp;
	last_len[i] = retval - 3;

	SetTimer(i + 1, TIMEOUT, 0);

	WSAAsyncSelect(s, m_hWnd, WM_SEND_FILE_SOCK, FD_READ | FD_CLOSE);

	//free(file_pdu);
	return i;
}