void putChar2TX(u8 data)
{
    chkSumTX ^= data;
    putChar(&mTxRingBuf, data);
}