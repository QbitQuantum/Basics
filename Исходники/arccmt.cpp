bool Archive::GetComment(Array<byte> *CmtData,Array<wchar> *CmtDataW)
{
  if (!MainComment)
    return(false);
  SaveFilePos SavePos(*this);

#ifndef SFX_MODULE
  ushort CmtLength;
  if (OldFormat)
  {
    Seek(SFXSize+SIZEOF_OLDMHD,SEEK_SET);
    CmtLength=GetByte();
    CmtLength+=(GetByte()<<8);
  }
  else
#endif
  {
    if (NewMhd.Flags & MHD_COMMENT)
    {
      // Old style (RAR 2.9) archive comment embedded into the main 
      // archive header.
      Seek(SFXSize+SIZEOF_MARKHEAD+SIZEOF_NEWMHD,SEEK_SET);
      ReadHeader();
    }
    else
    {
      // Current (RAR 3.0+) version of archive comment.
      Seek(SFXSize+SIZEOF_MARKHEAD+NewMhd.HeadSize,SEEK_SET);
      return(SearchSubBlock(SUBHEAD_TYPE_CMT)!=0 && ReadCommentData(CmtData,CmtDataW)!=0);
    }
#ifndef SFX_MODULE
    // Old style (RAR 2.9) comment header embedded into the main 
    // archive header.
    if (CommHead.HeadCRC!=HeaderCRC)
    {
      Log(FileName,St(MLogCommHead));
      Alarm();
      return(false);
    }
    CmtLength=CommHead.HeadSize-SIZEOF_COMMHEAD;
#endif
  }
#ifndef SFX_MODULE
  if (OldFormat && (OldMhd.Flags & MHD_PACK_COMMENT) || !OldFormat && CommHead.Method!=0x30)
  {
    if (!OldFormat && (CommHead.UnpVer < 15 || CommHead.UnpVer > UNP_VER || CommHead.Method > 0x35))
      return(false);
    ComprDataIO DataIO;
    Unpack Unpack(&DataIO);
    Unpack.Init();
    DataIO.SetTestMode(true);
    uint UnpCmtLength;
    if (OldFormat)
    {
#ifdef RAR_NOCRYPT
      return(false);
#else
      UnpCmtLength=GetByte();
      UnpCmtLength+=(GetByte()<<8);
      CmtLength-=2;
      DataIO.SetCmt13Encryption();
#endif
    }
    else
      UnpCmtLength=CommHead.UnpSize;
    DataIO.SetFiles(this,NULL);
    DataIO.EnableShowProgress(false);
    DataIO.SetPackedSizeToRead(CmtLength);
    Unpack.SetDestSize(UnpCmtLength);
    Unpack.DoUnpack(CommHead.UnpVer,false);

    if (!OldFormat && ((~DataIO.UnpFileCRC)&0xffff)!=CommHead.CommCRC)
    {
      Log(FileName,St(MLogCommBrk));
      Alarm();
      return(false);
    }
    else
    {
      byte *UnpData;
      size_t UnpDataSize;
      DataIO.GetUnpackedData(&UnpData,&UnpDataSize);
      CmtData->Alloc(UnpDataSize);
      memcpy(&((*CmtData)[0]),UnpData,UnpDataSize);
    }
  }
  else
  {
    CmtData->Alloc(CmtLength);
    
    Read(&((*CmtData)[0]),CmtLength);
    if (!OldFormat && CommHead.CommCRC!=(~CRC(0xffffffff,&((*CmtData)[0]),CmtLength)&0xffff))
    {
      Log(FileName,St(MLogCommBrk));
      Alarm();
      CmtData->Reset();
      return(false);
    }
  }
#endif
#if defined(_WIN_ALL) && !defined(_WIN_CE)
  if (CmtData->Size()>0)
  {
    size_t CmtSize=CmtData->Size();
    char *DataA=(char *)CmtData->Addr();
    OemToCharBuffA(DataA,DataA,(DWORD)CmtSize);

    if (CmtDataW!=NULL)
    {
      CmtDataW->Alloc(CmtSize+1);
      CmtData->Push(0);
      CharToWide(DataA,CmtDataW->Addr(),CmtSize+1);
      CmtData->Alloc(CmtSize);
      CmtDataW->Alloc(wcslen(CmtDataW->Addr()));
    }
  }
#endif
  return(CmtData->Size()>0);
}