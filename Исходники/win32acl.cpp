void ExtractACL(Archive &Arc,char *FileName,wchar *FileNameW)
{
  if (!WinNT())
    return;

  SetPrivileges();

  if (Arc.HeaderCRC!=Arc.EAHead.HeadCRC)
  {
    Log(Arc.FileName,St(MACLBroken),FileName);
    ErrHandler.SetErrorCode(CRC_ERROR);
    return;
  }

  if (Arc.EAHead.Method<0x31 || Arc.EAHead.Method>0x35 || Arc.EAHead.UnpVer>PACK_VER)
  {
    Log(Arc.FileName,St(MACLUnknown),FileName);
    ErrHandler.SetErrorCode(WARNING);
    return;
  }

  ComprDataIO DataIO;
  Unpack Unpack(&DataIO);
  Unpack.Init();

  Array<byte> UnpData(Arc.EAHead.UnpSize);
  DataIO.SetUnpackToMemory(&UnpData[0],Arc.EAHead.UnpSize);
  DataIO.SetPackedSizeToRead(Arc.EAHead.DataSize);
  DataIO.EnableShowProgress(false);
  DataIO.SetFiles(&Arc,NULL);
  Unpack.SetDestSize(Arc.EAHead.UnpSize);
  Unpack.DoUnpack(Arc.EAHead.UnpVer,false);

  if (Arc.EAHead.EACRC!=~DataIO.UnpFileCRC)
  {
    Log(Arc.FileName,St(MACLBroken),FileName);
    ErrHandler.SetErrorCode(CRC_ERROR);
    return;
  }

  SECURITY_INFORMATION  si=OWNER_SECURITY_INFORMATION|GROUP_SECURITY_INFORMATION|
                           DACL_SECURITY_INFORMATION;
  if (ReadSacl)
    si|=SACL_SECURITY_INFORMATION;
  SECURITY_DESCRIPTOR *sd=(SECURITY_DESCRIPTOR *)&UnpData[0];

  int SetCode;
  if (FileNameW!=NULL)
    SetCode=SetFileSecurityW(FileNameW,si,sd);
  else
    SetCode=SetFileSecurityA(FileName,si,sd);

  if (!SetCode)
  {
    Log(Arc.FileName,St(MACLSetError),FileName);
    ErrHandler.SysErrMsg();
    ErrHandler.SetErrorCode(WARNING);
  }
}