    //////////////////////////////////////////////////////////////////////////
    // doHardwareScan
    //
    // Checks available COM ports and scans for MotionTrackers
    int AHRS::doHardwareScan(xsens::Cmt3 &cmt3, CmtDeviceId deviceIds[])
    {
	    XsensResultValue res;
	    List<CmtPortInfo> portInfo;
	    unsigned long portCount = 0;
	    int mtCount;
	    
	    xsens::cmtScanPorts(portInfo);
	    portCount = portInfo.length();
	    
	    if (portCount == 0) {
		    printf("No MotionTrackers found \n\n");
		    return 0; 
	    }

	    for(int p = 0; p < (int)portCount; p++){
		    res = cmt3.openPort(portInfo[p].m_portName, portInfo[p].m_baudrate);
		    EXIT_ON_ERROR(res,"cmtOpenPort");  
	    }

	    //get the Mt sensor count.
	    mtCount = cmt3.getMtCount();

	    // retrieve the device IDs 
	    for(int j = 0; j < mtCount; j++){
		    res = cmt3.getDeviceId((unsigned char)(j+1), deviceIds[j]);
		    EXIT_ON_ERROR(res,"getDeviceId");
	    }
	    
	    return mtCount;
    }