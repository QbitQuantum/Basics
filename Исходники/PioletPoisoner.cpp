void PioletPoisoner::CheckPerformanceCounters()
{
    UINT i;

    // Collect the pdh query data
    if(PdhCollectQueryData(m_pdh))
    {
        MessageBox(NULL,"Error collecting pdh query data","Error",MB_OK);
        return;
    }

    // Check the processor usage counter
    PDH_FMT_COUNTERVALUE value;
    PDH_STATUS error;

    error=PdhGetFormattedCounterValue(m_pdh_counters[0],PDH_FMT_LONG,0,&value);
    if(error)
    {
//		MessageBox("Error formatting pdh counter data");
//		m_dlg.SetWindowText("Error formatting pdh coutner data");
        return;
    }

    m_proc_percent_usage=value.longValue;

    /*
    	// If less than 50 % kick off another mod if there is less than min count of them
    	if((m_proc_percent_usage<50) & (m_connection_manager.ReturnModCount()<(UINT)m_min_module_count))	// was 60
    	{
    		m_connection_manager.AddModule();

    		char log[1024];
    		sprintf(log,"Module Added : (Current Count : %u) : (Proc % Usage : %u%%) : (Min Mod Count : %u)\n",
    			m_connection_manager.ReturnModCount(),m_proc_percent_usage,m_min_module_count);
    		m_log_window_manager.Log(log,0x00888888);
    	}
    */
    // Check the bandwidth counter
    error=PdhGetFormattedCounterValue(m_pdh_counters[1],PDH_FMT_LONG,0,&value);
    if(error)
    {
//		MessageBox("Error formatting pdh counter data");
//		m_dlg.SetWindowText("Error formatting pdh coutner data");
        return;
    }

    m_bandwidth_in_bytes=value.longValue;

    // Check the current bandwidth in bits per second
    error=PdhGetFormattedCounterValue(m_pdh_counters[2],PDH_FMT_LONG,0,&value);
    if(error)
    {
        return;
    }

    m_current_bandwdith_in_bits_per_second=value.longValue;	// this should be 100 Mbps

    double bps=m_bandwidth_in_bytes*8;

    // Measure the processes mem usage
    HANDLE hHandle;
    DuplicateHandle(GetCurrentProcess(),GetCurrentProcess(),GetCurrentProcess(),&hHandle,0,FALSE,DUPLICATE_SAME_ACCESS);

    PROCESS_MEMORY_COUNTERS pmc;
    pmc.cb=sizeof(PROCESS_MEMORY_COUNTERS);
    GetProcessMemoryInfo(hHandle,&pmc,sizeof(PROCESS_MEMORY_COUNTERS));

    CloseHandle(hHandle);

    m_mem_usage=(UINT)pmc.WorkingSetSize;	// in bytes

    // Put commas in the mem measurement value
    char mem_buf[100];
    string mem;
    _itoa(m_mem_usage/1024,mem_buf,10);
    strrev(mem_buf);
    for(i=0; i<strlen(mem_buf); i++)
    {
        if((i>0) && (i%3==0))
        {
            mem+=",";
        }

        mem+=mem_buf[i];
    }
    strcpy(mem_buf,mem.c_str());
    strrev(mem_buf);

    // Display the status
    char buf[1024];
    sprintf(buf,"[ %u %% ] - [ %.2f KB/sec - %.2f %% ] - [ %s KB ]",m_proc_percent_usage,((double)m_bandwidth_in_bytes)/1024,
            (100*bps)/m_current_bandwdith_in_bits_per_second,mem_buf);
    m_dlg.GetDlgItem(IDC_Computer_Status_Static)->SetWindowText(buf);

//	sprintf(buf, "Poison Entries Size: %u", v_poison_entries.size());
//	m_dlg.GetDlgItem(IDC_POISON_ENTRIES_SIZE_STATIC)->SetWindowText(buf);

}