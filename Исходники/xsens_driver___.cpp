//////////////////////////////////////////////////////////////////////////
// doHardwareScan
//
// Checks available COM ports and scans for MotionTrackers
int XSensDriver::doHardwareScan( xsens::Cmt3 &cmt3, CmtDeviceId deviceIds[] )
{
    XsensResultValue res;
    List<CmtPortInfo> portInfo;
    unsigned long portCount = 0;
    int mtCount;

    std::cout << "Scanning for connected Xsens devices..." << std::endl;

//    xsens::cmtScanPorts( portInfo );
    CmtPortInfo target_port = { 0, 0, 0, "" };
    sprintf( target_port.m_portName, "%s", port_.c_str() );

    if( cmtScanPort( target_port, target_port.m_baudrate ) ) portInfo.append( target_port );

    portCount = portInfo.length();
    std::cout << "done" << std::endl;

    if ( portCount == 0 )
    {
        std::cout << "No MotionTrackers found" << std::endl;
        return 0;
    }

    for ( int i = 0; i < (int) portCount; i++ )
    {
        std::cout << "Using COM port at [ " << portInfo[i].m_portName << " ] ";
        std::cout << "baud [ ";

        switch ( portInfo[i].m_baudrate )
        {
        case B9600:
            std::cout << "9k6";
            break;
        case B19200:
            std::cout << "19k2";
            break;
        case B38400:
            std::cout << "38k4";
            break;
        case B57600:
            std::cout << "57k6";
            break;
        case B115200:
            std::cout << "115k2";
            break;
        case B230400:
            std::cout << "230k4";
            break;
        case B460800:
            std::cout << "460k8";
            break;
        case B921600:
            std::cout << "921k6";
            break;
        default:
            std::cout << portInfo[i].m_baudrate;
        }
        std::cout << " ]" << std::endl;
    }

    std::cout << "Opening ports...";
    //open the port which the device is connected to and connect at the device's baudrate.
    for ( int p = 0; p < (int) portCount; p++ )
    {
        res = cmt3.openPort( portInfo[p].m_portName, portInfo[p].m_baudrate );
        //      EXIT_ON_ERROR(res,"cmtOpenPort");
    }
    std::cout << "done" << std::endl;

    //get the Mt sensor count.
    std::cout << "Retrieving MotionTracker count (excluding attached Xbus Master(s))" << std::endl;
    mtCount = cmt3.getMtCount();
    std::cout << "MotionTracker count: " << mtCount << std::endl;

    // retrieve the device IDs
    std::cout << "Retrieving MotionTrackers device ID(s)" << std::endl;
    for ( int j = 0; j < mtCount; j++ )
    {
        res = cmt3.getDeviceId( (unsigned char) ( j + 1 ), deviceIds[j] );
        //      EXIT_ON_ERROR(res,"getDeviceId");
        std::cout << "Device ID at busId " << j + 1 << "," << (long) deviceIds[j] << std::endl;
    }

    return mtCount;
}