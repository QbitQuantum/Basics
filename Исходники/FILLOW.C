long FAR PASCAL FilSetPos (short sFilHdl, long ulNewPos, unsigned short usPosFlg)
{
    return (_llseek (sFilHdl, ulNewPos, usPosFlg));
}