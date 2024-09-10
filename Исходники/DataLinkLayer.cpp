UINT BPSThreadFunc(LPVOID lpParam)
{
	CDataLinkLayer* me = (CDataLinkLayer*)lpParam;

	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i = 0;
	pcap_t *adhandle;
	int res;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr *header;
	const u_char *pkt_data;

	/* Retrieve the device list on the local machine */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		CString string;
		string.Format(L"Error in pcap_findalldevs: %s\n", errbuf);
		AfxMessageBox(string);
		return 0;
	}
	
	
	//printf("Enter the interface number (1-%d):", i);
	//scanf_s("%d", &inum);
	int index;
	index = me->m_deviceList->GetCurSel();
	if (index == -1)
	{
		AfxMessageBox(L"Must select a device!");
		return 0;
	}
	else 
	{
		inum = index;
	}
	

	//if (inum < 1 || inum > i)
	//{
	//	printf("\nInterface number out of range.\n");
	//	/* Free the device list */
	//	pcap_freealldevs(alldevs);
	//	return;
	//}

	/* Jump to the selected adapter */
	for (d = alldevs, i = 0; i< inum - 1;d = d->next, i++);

	/* Open the device */
	if ((adhandle = pcap_open(d->name,          // name of the device
		65536,            // portion of the packet to capture. 
						  // 65536 guarantees that the whole packet will be captured on all the link layers
		PCAP_OPENFLAG_PROMISCUOUS,    // promiscuous mode
		1000,             // read timeout
		NULL,             // authentication on the remote machine
		errbuf            // error buffer
		)) == NULL)
	{
		CString string;
		string.Format(L"\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		AfxMessageBox(string);
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return 0;
	}




	//printf("\nlistening on %s...\n", d->description);


	/* Don't care about netmask, it won't be used for this filter */
	//u_int netmask = 0xffffff;


	/* Put the interface in statstics mode */
	if (pcap_setmode(adhandle, MODE_STAT)<0)
	{
		CString string;
		string.Format(L"\nError setting the mode.\n");
		AfxMessageBox(string);
		pcap_close(adhandle);
		/* Free the device list */
		return 0;
	}

	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);

	struct timeval old_ts;
	old_ts.tv_sec = 0;
	old_ts.tv_usec = 0;

	while ((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0 && me->m_runBPSThread) {

		if (res == 0)
			/* Timeout elapsed */
			continue;

		u_int delay;
		LARGE_INTEGER Bps;
		delay = (header->ts.tv_sec - old_ts.tv_sec) * 1000000 - old_ts.tv_usec + header->ts.tv_usec;
		/* Get the number of Bits per second */
		Bps.QuadPart = (((*(LONGLONG*)(pkt_data + 8)) * 8 * 1000000) / (delay));
		old_ts = header->ts;
		CString strTotalLen;
		strTotalLen.Format(L"Byte per second: %I64u bps", Bps.QuadPart);
		me->SetDlgItemTextW(IDC_STATIC_BPS, strTotalLen);
	}

	return 0;
}