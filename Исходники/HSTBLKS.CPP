void CEvBlk::Skip(DWORD DeltaID)
  {
  DeltaID--;
  if (DeltaID<=0x1F)
    {
    pData[pTS->iLen++] = (TS_SKIP_0 | (byte)DeltaID); 
    }
  else if (DeltaID<=0x1FFF)
    {
    pData[pTS->iLen++] = (TS_SKIP_1 | ((byte)DeltaID & 0x1F)); 
    pData[pTS->iLen++] = (byte)_lrotr(DeltaID, 5);
    }
  else if (DeltaID<=0x1FFFFF)
    {
    pData[pTS->iLen++] = (TS_SKIP_2 | ((byte)DeltaID & 0x1F)); 
    *((WORD*)&pData[pTS->iLen]) = (WORD)_lrotr(DeltaID, 5);
    pTS->iLen += 2;
    }
  else if (DeltaID<=0x1FFFFFFF)
    {
    *((DWORD*)&pData[pTS->iLen]) = (DWORD)_lrotr(DeltaID, 5);
    pData[pTS->iLen++] = (TS_SKIP_3 | ((byte)DeltaID & 0x1F)); 
    pTS->iLen += 3;
    }
  else
    {
    dbgpln("DeltaID in historian %d is to large !!!!!", DeltaID);
    VERIFY(FALSE);
    }
  }