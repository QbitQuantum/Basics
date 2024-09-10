int ExynosJpegDecoder::setOutBuf(int *piBuf, int *iSize)
{
    int iRet = ERROR_NONE;
    iRet = setBuf(&t_stJpegOutbuf, piBuf, iSize, t_iPlaneNum);

    if (iRet == ERROR_NONE)
        t_bFlagCreateOutBuf = true;

    return iRet;
}