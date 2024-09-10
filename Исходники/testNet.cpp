int Test_Net_TCP_On_TCP_Connected(Msg_Net_TCP_Connected* pMsg)
{
  Test_Net_TCP_On_Data* d = Test_Net_TCP_On_Data_FindByHandle(pMsg->hConnection);
  if (d != 0) {
    d->bConnected_ = 1;

    if (!pMsg->bSuccess) {
      apLog_Warning((LOG_CHANNEL, LOG_CONTEXT, "Not connected " ApHandleFormat " %s: %s", ApHandlePrintf(pMsg->hConnection), _sz(d->sAddress_), _sz(pMsg->sComment)));
    } else {
      const char* pBuf = "GET / HTTP/1.0\r\nConnection: close\r\n\r\n";
      Msg_Net_TCP_DataOut msg;
      msg.hConnection = pMsg->hConnection;
      msg.sbData.SetData((const unsigned char*) pBuf, ::strlen(pBuf));
      msg.Request();
    }

    {
      unsigned int n = 0;
      for (Test_Net_TCP_On_Data* e = 0; (e = (Test_Net_TCP_On_Data*) lTest_Net_TCP_On_DataList.Next(e)) != 0; ) {
        if (e->bConnected_) {
          n++;
        }
      }
      if (n == lTest_Net_TCP_On_DataList.length() && !bTest_Net_TCP_Connected_Done) {
        AP_UNITTEST_SUCCESS(Test_Net_TCP_Connected);
        bTest_Net_TCP_Connected_Done = 1;
      }
    }
  }

  return 1;
}