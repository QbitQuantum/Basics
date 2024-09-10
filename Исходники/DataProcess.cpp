/**< 打包 */
int Dataprocess::Pack(unsigned char *PackageOut, unsigned int &OutLen)
{
    try
	{
        int iRet;
        char cTemp;
        /**< 不返回35、36、52域 */
        if( pMsg8583recv->FieldExist(35) ) pMsg8583recv->RemoveField(35);
        if( pMsg8583recv->FieldExist(36) ) pMsg8583recv->RemoveField(36);
        if( pMsg8583recv->FieldExist(52) ) pMsg8583recv->RemoveField(52);

        /**< 转换TPDU并进行设置 */
        unsigned char cMsgTpdu[MSGTPDULEN] ={0};
        if((iRet = pMsg8583recv->GetTpdu(cMsgTpdu, MSGTPDULEN)) <= 0)
        {
            trace_log(ERR, "GetTpdu failed...");
            return -1;
        }
        for(int i=1;i<=2;i++)
        {
            cTemp=cMsgTpdu[i+2];
            cMsgTpdu[i+2]=cMsgTpdu[i];
            cMsgTpdu[i]=cTemp;
        }
        if(0 == pMsg8583recv->SetMsgTPDU(cMsgTpdu, MSGTPDULEN))
        {
            trace_log(ERR, "SetTpdu failed...");
            return -1;
        }
        /**< 设置消息类型 */
        myData.cMsgType[2]= myData.cMsgType[2]+1;
        pMsg8583recv->SetValueByStr(0,(char *)myData.cMsgType);
        /**< 打包 */
        OutLen = MAX_BUFFER;
        iRet = pMsg8583recv->Pack(PackageOut, (unsigned &)OutLen);
        if(iRet != 1)
        {
            trace_log(ERR, "Pack8583 failed...");
            return -1;
        }

        /**< 替换新MAC */
        if( pMsg8583recv->FieldExist(FIELDCOUNT - 1) )
        {
            unsigned char 	Mac[16];
            unsigned char *	pMab = PackageOut + LENOFFSET + MSGTPDULEN + MSGHEADLEN;
            int 			MabLen = (int)OutLen - LENOFFSET - MSGTPDULEN - MSGHEADLEN - MACLEN ;

            if(MabLen < 0)
            {
                trace_log(ERR, "error Mablen[%d]", MabLen);
                return -1;
            }
            EnCrypt enCrypt;
            bool enc_ret = enCrypt.CalculateMac((char *)myData.cCardAccepCode, (char *)myData.cCardAccepTerm, pMab, MabLen, Mac);
            if(enc_ret)
            {
                trace_log(NML, "CalculateMac success");
                memcpy(PackageOut + (OutLen - MACLEN), Mac, MACLEN);
            }
			else
			{
                trace_log(ERR, "CalculateMac failed");
                return -1;
            }
        }
        return 0;
    }
	catch(...)
	{
        trace_log(SYS, "Error in Dataprocess::Pack()");
        return -1;
    }
}