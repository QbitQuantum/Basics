DWORD CIcmpEcho::PingHost(unsigned long ulIP, int iPingTimeout)
{
    //Task 1:	Open ICMP Handle
    //Task 2:	Create Structure to receive ping reply
    //Task 3:	SendPing (SendEcho)
    //Task 4:	Close ICMP Handle
    //Task 5:	Return RoundTripTime

    unsigned long ip = ulIP;

    HANDLE icmphandle = IcmpCreateFile();

    char reply[sizeof(icmp_echo_reply)+8];

    icmp_echo_reply* iep=(icmp_echo_reply*)&reply;
    iep->RoundTripTime = 0xffffffff;

    IcmpSendEcho(icmphandle,ip,0,0,NULL,reply,sizeof(icmp_echo_reply)+8,iPingTimeout);

    IcmpCloseHandle(icmphandle);

    return iep->RoundTripTime;

}