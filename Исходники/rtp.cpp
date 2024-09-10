/***********************************************************************************************************
**函数:Rtp_Lock
**功能:
**输入参数:
**返回值:
***********************************************************************************************************/
static int  RtpSetup( uint16_t portbase)
{
    int status;
	
    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/90000.0);
    sessparams.SetMaximumPacketSize(1200);
    transparams.SetPortbase(portbase);
    sess.SetDefaultPayloadType(PLOAD_TYPE);
    sess.SetDefaultMark(false);
    sess.SetDefaultTimestampIncrement(DefaultTimestampIncrement);
    status = sess.Create(sessparams,&transparams);
    checkerror(status);
    return status;
}