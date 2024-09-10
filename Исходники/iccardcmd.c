/*******************************************************************
   ��	 ��: 
   ��	 Ȩ: �����¹����ɷ����޹�˾
   ��������: ����APDU
   ��ڲ���: �������� ����, ������� ����, IC������ز���
   �� �� ֵ:
   ��	 ע: 
 ********************************************************************/
u32 TransferApdu(u8 *datain, u16 inlen, u8 *dataout, u16 *outlen, SDK_ICC_PARAM *pstIccParam) {
    TraceHex("Lai", "TransferApdu\r\n", datain, inlen);

    SDK_ICC_APDU_SEND pstApduSend;
    SDK_ICC_APDU_RESP pstApduResp;
    s32 rlt;
    u8 *temp;
    u16 templen;

    temp = (u8 *) sdkGetMem(512);

    if (temp == NULL) {
        return 0x8E03;
    }
    memset(temp, 0, 512);
    memset(&pstApduSend, 0, sizeof(pstApduSend));
    memset(&pstApduResp, 0, sizeof(pstApduResp));

    if (inlen < 5) {
        sdkFreeMem(temp);
        return 0x8E03;
    }
    else if (inlen == 5) {
        memcpy(pstApduSend.Command, datain, 4);
        pstApduSend.Le = datain[4];
    }
    else {
        memcpy(pstApduSend.Command, datain, 4);
        pstApduSend.Lc = datain[4];

        if (pstApduSend.Lc > inlen - 5) {
            sdkFreeMem(temp);
            return 0x8E03;
        }
        else if (pstApduSend.Lc == inlen - 5) {
            memcpy(pstApduSend.DataIn, datain + 5, pstApduSend.Lc);
        }
        else {
            memcpy(pstApduSend.DataIn, datain + 5, pstApduSend.Lc);
            pstApduSend.Le = datain[inlen - 1];
        }
    }
    rlt = sdkIccDealCardData(pstIccParam, &pstApduSend, &pstApduResp);

    if (rlt == SDK_OK) {
        memcpy(temp, pstApduResp.DataOut, pstApduResp.LenOut);
        temp[pstApduResp.LenOut] = pstApduResp.SWA;
        temp[pstApduResp.LenOut + 1] = pstApduResp.SWB;
        templen = pstApduResp.LenOut + 2;
        //templen = FormTlv(buf, "\xFF\x4D", 2, temp, templen); 

        if (*outlen < templen) {
            sdkFreeMem(temp);
            return 0x8E03;
        }
        memcpy(dataout, temp, templen);
        *outlen = templen;
        sdkFreeMem(temp);
        return 0x9000;
    }
    else {
        sdkFreeMem(temp);
        Trace("", "$$$$$$$$$ 6666666666 %d\r\n", rlt);
        return 0x8E03;
    }
}