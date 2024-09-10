STATUS FNC::Recv()
{
    struct sockaddr_in fromAddr;
    socklen_t fromAddrLen = sizeof fromAddr;

    int n = recvfrom(m_recvSocket, (char *)&m_recvPkt, sizeof m_recvPkt, 0,
		     (struct sockaddr *)&fromAddr, &fromAddrLen);
    if (n == -1) {
	perror("FRC_NetworkCommunication::Recv::recvfrom");
	return ERROR;
    }

    if (m_recvAddr.sin_addr.s_addr == INADDR_ANY) {
	// fill in my own address based on:
	// DS at 10.TE.AM.xx
	// robot at 10.TE.AM.2
	in_addr_t ipaddr = ntohl(fromAddr.sin_addr.s_addr);
	ipaddr = (ipaddr & 0xFFFFFF00) | 0x02;
	m_recvAddr.sin_addr.s_addr = htonl(ipaddr);
	m_sendAddr.sin_addr.s_addr = htonl(ipaddr);
    }

    m_pcap->write_record(&fromAddr, &m_recvAddr, (char *)&m_recvPkt, n);

    if (n != sizeof m_recvPkt) {
	printf("FRC_NetworkCommunication::Recv: wrong size (%d)\n", n);
	return OK;
    }

    uint32_t recvCRC = ntohl(m_recvPkt.crc);
    m_recvPkt.crc = 0;
    uint32_t calcCRC = crc32(0, Z_NULL, 0);
    calcCRC = crc32(calcCRC, (uint8_t *)&m_recvPkt, sizeof m_recvPkt);

    if (calcCRC != recvCRC) {
	printf("FRC_NetworkCommunication::Recv: bad checksum "
	       "(received 0x%08x, calculated 0x%08x)\n", recvCRC, calcCRC);
	return OK;
    }

    // unpack and copy data to m_recvData
    {
	// begin critical section
	Synchronized sync(m_dataMutex);

	// clear the work area for safety
	memset(&m_recvData, 0, sizeof m_recvData);

	// unpack common header elements
	m_recvData.packetIndex		= ntohs(m_recvPkt.ctrl.packetIndex);

	m_recvData.reset		= m_recvPkt.ctrl.reset;
	m_recvData.notEStop		= m_recvPkt.ctrl.notEStop;
	m_recvData.enabled		= m_recvPkt.ctrl.enabled;
	m_recvData.autonomous		= m_recvPkt.ctrl.autonomous;
	m_recvData.fmsAttached		= m_recvPkt.ctrl.fmsAttached;
	m_recvData.resync		= m_recvPkt.ctrl.resync;
	m_recvData.test			= m_recvPkt.ctrl.test;
	m_recvData.checkVersions	= m_recvPkt.ctrl.checkVersions;

	m_recvData.dsDigitalIn		= m_recvPkt.ctrl.dsDigitalIn;
	m_recvData.teamID		= ntohs(m_recvPkt.ctrl.teamID);
	m_recvData.dsID_Alliance	= m_recvPkt.ctrl.dsID_Alliance;
	m_recvData.dsID_Position	= m_recvPkt.ctrl.dsID_Position;
#if 0
	printf("pkt %u ctrl 0x%02x dig in 0x%02x team %u position %c%c\n",
	       m_recvData.packetIndex, m_recvData.control,
	       m_recvData.dsDigitalIn, m_recvData.teamID,
	       m_recvData.dsID_Alliance, m_recvData.dsID_Position);
#endif

	// unpack data for each of the 4 possible joysticks
	m_recvData.stick0Axis1		= m_recvPkt.ctrl.stick0Axis1;
	m_recvData.stick0Axis2		= m_recvPkt.ctrl.stick0Axis2;
	m_recvData.stick0Axis3		= m_recvPkt.ctrl.stick0Axis3;
	m_recvData.stick0Axis4		= m_recvPkt.ctrl.stick0Axis4;
	m_recvData.stick0Axis5		= m_recvPkt.ctrl.stick0Axis5;
	m_recvData.stick0Axis6		= m_recvPkt.ctrl.stick0Axis6;
	m_recvData.stick0Buttons	= ntohs(m_recvPkt.ctrl.stick0Buttons);
#if 0
	printf("stick0: %02x %02x %02x %02x %02x %02x %04x\n",
		m_recvData.stick0Axis1, m_recvData.stick0Axis2,
		m_recvData.stick0Axis3, m_recvData.stick0Axis4,
		m_recvData.stick0Axis5, m_recvData.stick0Axis6,
		m_recvData.stick0Buttons);
#endif
	m_recvData.stick1Axis1		= m_recvPkt.ctrl.stick1Axis1;
	m_recvData.stick1Axis2		= m_recvPkt.ctrl.stick1Axis2;
	m_recvData.stick1Axis3		= m_recvPkt.ctrl.stick1Axis3;
	m_recvData.stick1Axis4		= m_recvPkt.ctrl.stick1Axis4;
	m_recvData.stick1Axis5		= m_recvPkt.ctrl.stick1Axis5;
	m_recvData.stick1Axis6		= m_recvPkt.ctrl.stick1Axis6;
	m_recvData.stick1Buttons	= ntohs(m_recvPkt.ctrl.stick1Buttons);
#if 0
	printf("stick1: %02x %02x %02x %02x %02x %02x %04x\n",
		m_recvData.stick1Axis1, m_recvData.stick1Axis2,
		m_recvData.stick1Axis3, m_recvData.stick1Axis4,
		m_recvData.stick1Axis5, m_recvData.stick1Axis6,
		m_recvData.stick1Buttons);
#endif
	m_recvData.stick2Axis1		= m_recvPkt.ctrl.stick2Axis1;
	m_recvData.stick2Axis2		= m_recvPkt.ctrl.stick2Axis2;
	m_recvData.stick2Axis3		= m_recvPkt.ctrl.stick2Axis3;
	m_recvData.stick2Axis4		= m_recvPkt.ctrl.stick2Axis4;
	m_recvData.stick2Axis5		= m_recvPkt.ctrl.stick2Axis5;
	m_recvData.stick2Axis6		= m_recvPkt.ctrl.stick2Axis6;
	m_recvData.stick2Buttons	= ntohs(m_recvPkt.ctrl.stick2Buttons);
#if 0
	printf("stick2: %02x %02x %02x %02x %02x %02x %04x\n",
		m_recvData.stick2Axis1, m_recvData.stick2Axis2,
		m_recvData.stick2Axis3, m_recvData.stick2Axis4,
		m_recvData.stick2Axis5, m_recvData.stick2Axis6,
		m_recvData.stick2Buttons);
#endif
	m_recvData.stick3Axis1		= m_recvPkt.ctrl.stick3Axis1;
	m_recvData.stick3Axis2		= m_recvPkt.ctrl.stick3Axis2;
	m_recvData.stick3Axis3		= m_recvPkt.ctrl.stick3Axis3;
	m_recvData.stick3Axis4		= m_recvPkt.ctrl.stick3Axis4;
	m_recvData.stick3Axis5		= m_recvPkt.ctrl.stick3Axis5;
	m_recvData.stick3Axis6		= m_recvPkt.ctrl.stick3Axis6;
	m_recvData.stick3Buttons	= ntohs(m_recvPkt.ctrl.stick3Buttons);
#if 0
	printf("stick3: %02x %02x %02x %02x %02x %02x %04x\n",
		m_recvData.stick3Axis1, m_recvData.stick3Axis2,
		m_recvData.stick3Axis3, m_recvData.stick3Axis4,
		m_recvData.stick3Axis5, m_recvData.stick3Axis6,
		m_recvData.stick3Buttons);
#endif

	// unpack the four analog input channels
	m_recvData.analog1		= ntohs(m_recvPkt.ctrl.analog1);
	m_recvData.analog2		= ntohs(m_recvPkt.ctrl.analog2);
	m_recvData.analog3		= ntohs(m_recvPkt.ctrl.analog3);
	m_recvData.analog4		= ntohs(m_recvPkt.ctrl.analog4);
#if 0
	printf("analog: %04x %04x %04x %04x\n",
		m_recvData.analog1, m_recvData.analog2,
		m_recvData.analog3, m_recvData.analog4);
#endif

	// unpack the cRIO and FPGA checksums (?)
#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
# define ntohll(x) ((uint64_t)(x))
#elif (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
# define ntohll(x) \
	((uint64_t)((((uint64_t)(x) & 0x00000000000000ffLLU) << 56) | \
		    (((uint64_t)(x) & 0x000000000000ff00LLU) << 40) | \
		    (((uint64_t)(x) & 0x0000000000ff0000LLU) << 24) | \
		    (((uint64_t)(x) & 0x00000000ff000000LLU) <<  8) | \
		    (((uint64_t)(x) & 0x000000ff00000000LLU) >>  8) | \
		    (((uint64_t)(x) & 0x0000ff0000000000LLU) >> 24) | \
		    (((uint64_t)(x) & 0x00ff000000000000LLU) >> 40) | \
		    (((uint64_t)(x) & 0xff00000000000000LLU) >> 56)))
#else
#error __BYTE_ORDER__ must be __ORDER_BIG_ENDIAN__ or __ORDER_LITTLE_ENDIAN__
#endif

	m_recvData.cRIOChecksum		= ntohll(m_recvPkt.ctrl.cRIOChecksum);
#if 0
	printf("cRIO checksum: %08lx%08lx\n",
	    (unsigned long)(m_recvData.cRIOChecksum >> 32),
	    (unsigned long)(m_recvData.cRIOChecksum));
#endif
	m_recvData.FPGAChecksum0	= ntohl(m_recvPkt.ctrl.FPGAChecksum0);
	m_recvData.FPGAChecksum1	= ntohl(m_recvPkt.ctrl.FPGAChecksum1);
	m_recvData.FPGAChecksum2	= ntohl(m_recvPkt.ctrl.FPGAChecksum2);
	m_recvData.FPGAChecksum3	= ntohl(m_recvPkt.ctrl.FPGAChecksum3);
#if 0
	printf("FPGA checksums: %08x %08x %08x %08x\n",
		m_recvData.FPGAChecksum0, m_recvData.FPGAChecksum1,
		m_recvData.FPGAChecksum2, m_recvData.FPGAChecksum3);
#endif

	// unpack the DS version string
	// ASCII string, mmddyyvv ("vv"="version" aka "build number")
	memcpy(m_recvData.versionData, m_recvPkt.ctrl.versionData, 8);
#if 0
	printf("DS version %.2s.%.2s.%.2s.%.2s\n",
		&m_recvData.versionData[0], &m_recvData.versionData[2],
		&m_recvData.versionData[4], &m_recvData.versionData[6]);
#endif

	// copy the dynamic extensions
	// we don't know the internal structure of these, so clients are
	// responsible for unpacking their own data
	memcpy(m_extData, m_recvPkt.extData, sizeof m_extData);

	// save sender's address for reply
	memcpy(&m_fromAddr, &fromAddr, sizeof m_fromAddr);

	// tell DriverStation object that new data is available
	if (m_dataAvailable) semFlush(m_dataAvailable);

	// end critical section
    }

    return OK;
}