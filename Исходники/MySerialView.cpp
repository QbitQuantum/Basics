/*串口接收线程*/
DWORD WINAPI serial_rcv(void *arg)
{
	char	str[2048]={0};
	int		index;
	int		len = 0;

	while( ComState != COM_CLOSED )
	{
		memset(str,0,sizeof(str));
		len = myserial.Read(str,512);

		if( HEX == com_rx_format )
		{
			char *p = str;
			char buf[512] = {0};
			memcpy(buf,str,512);
			for( int i =0; i< len ; i++)
			{
				sprintf(p,"%02X ",buf[i]);
				p += 3;
			}
		}

		index = com_rcv_txt.GetWindowTextLengthA();
		com_rcv_txt.SetSel(index, index);
		com_rcv_txt.ReplaceSel(str);

		//计数
		com_rx += len;
		com_rx_counter.SetWindowTextA(ltoa(com_rx,str,10));
	}

	ComState = COM_CLOSED;
	return 0;
}