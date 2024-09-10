UINT Cappacketlivethread(LPVOID pParam)//抓包线程函数
{
	//CMainFrame *p_frame=(CMainFrame*)AfxGetMainWnd();
	//int m_exsn=p_frame->m_myprosheet.m_page2.m_thread_num;
	//int m_stoptime=p_frame->m_myprosheet.m_page2.m_stoptime;
	//int m_thread_index=0;
	for(int i=0;i<m_mystruct.m_packetlimit;i++)//线程数目
	{	
		if (::WaitForSingleObject(m_stoptimeup,0)==WAIT_OBJECT_0)
		{
			//m_thread_index=i;
			m_mystruct.m_count=i;
			break;
		} 
        pcap_next_ex(m_mystruct.pcap_handle,&m_mystruct.protocol_header,&m_mystruct.pkt_data);//句柄，协议头，数据包
		if ((m_mystruct.protocol_header->len)>m_mystruct.m_pl)//判断是否在规定长度以内
		{	
			i--;
			continue;
		}  
		pcap_dump((u_char*)m_mystruct.dumpfile,m_mystruct.protocol_header,m_mystruct.pkt_data);
		m_mystruct.m_count=i;
	} 
	m_eventEnd.SetEvent();
	return 0;
}