//---------------------------------------------------------------------------
//Recv接收请答包
bool JsdGateway::RecvAnswer(tagAnswerPacket *p_pAnswerPacket, bool singlerecord,int countOffset)
{
  int iLen;
  int iPos;
  int iHeadLen;
  DWORD dwDataLen;
  char szTemp[DEF_SBUFLEN];
	memset(m_pSingleRecvBuffer, 0, DEF_LBUFLEN_8192);

  TByteDynArray da;
  da.set_length(0);

  try
  {
      m_pSocket->Socket->ReadBytes(da,-1,true);
  }
  catch(...)
  {
	 return false;
  }

  if (da.Length == 0)
  {
      return false;
  }
  
  const char *buf = (const char*)&da[0];

	spliter sbuf(buf,da.Length,'|');


	if(sbuf.at(0).length()==0 || sbuf.at(0)[0] != 'A') {
    return false;
  }

//  包头取到后，判断序列号字段，以避免串户情况
  char szReqPakSN[DEF_SBUFLEN];
  sprintf(szReqPakSN,"%x:%x", GetCurrentThreadId(), m_dwReqPakSN);

  if (strcmp(szReqPakSN,sbuf.at(2).c_str())!=0)
  {
    //出现这种错误可能是因为错位，所以缓冲区内的数据全部清掉
	  return false;
  }

	if(sbuf[3].c_str()[0]=='N') {

		strcpy(p_pAnswerPacket->szRetMsg, sbuf[4].c_str());
		strcpy(p_pAnswerPacket->szRetCode, sbuf[5].c_str());

		return true;
	}
	else {
		memset(p_pAnswerPacket->szRetCode,0,DEF_SBUFLEN);
  }

  if(singlerecord)  {
    p_pAnswerPacket->bIsNext = 0;
    m_iRecNo = 1;
  }
  else {

    if(p_pAnswerPacket->bIsNext==0) {
			m_iRecNo =  atoi( sbuf[countOffset+2].c_str() )+1;    //记录总数+首条记录

      if(m_iRecNo<=0) {
				p_pAnswerPacket->bIsNext = 0;
      }
      else {
        p_pAnswerPacket->bIsNext = 1;
      }

      //return true;
    }
  }
  p_pAnswerPacket->iRecNum ++;

  if(p_pAnswerPacket->iRecNum==m_iRecNo) {   //数据是否已满
    p_pAnswerPacket->bIsNext = 0;
  }

  //处理数据结果
  for(int i=0;i<(m_iFieldCount+3);i++)  {
    _retData.push_back(sbuf[i]);
  }

  if(unsigned(p_pAnswerPacket->iRecNum*(m_iFieldCount+3))!=_retData.size()) {
    return false;
  }


  return TRUE;
}