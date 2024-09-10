// from PDIS miso library 
// Gets the local device name.
// Arguments:
//  - aName - object to hold the retrieved name.
//
// Returns an error code.
static TInt GetLocalName(TDes& aName)
{
  TInt err = KErrNone;

  RSocketServ socketServ;
  err = socketServ.Connect();
  if (!err) {
    TProtocolName protocolName;
    // address and name queries are apparently supplied
    // by the BT stack's link manager
    _LIT(KBtLinkManager, "BTLinkManager");
    protocolName.Copy(KBtLinkManager);
    TProtocolDesc protocolDesc;
    err = socketServ.FindProtocol(protocolName, protocolDesc);
    if (!err) {
      RHostResolver hostResolver;
      err = hostResolver.Open(socketServ,
				protocolDesc.iAddrFamily,
				protocolDesc.iProtocol);
      if (!err) {
	err = hostResolver.GetHostName(aName);
	hostResolver.Close();
      }
    }
    socketServ.Close();
  }  

  return err;
}