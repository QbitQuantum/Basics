/*
 * 将数据发送地址设置为txAddr,并将txBuf中的数据发送出去
 * 若成功返回1
 * 若失败返回0
 */
uchar nrfSend(uchar* txAddr, volatile uchar* txBuf)
{
    uchar txSta, ret;
    uint iCnt = 0;
    enterTxMode(txAddr, txBuf);

    //接收到数据发送完成中断
    //或者是超过一定的查询次数
    while ((PIND * (1<<IRQ)) || (iCnt ++ > 2000));

    txSta = spiRw(STATUS);
    spiRwReg(WRITE_REG + STATUS, 0xff);

    if (txSta & STA_MARK_TX)
    {
        flushAll();
        ret = 1;
    }
    ret = 0;
    return ret;
}