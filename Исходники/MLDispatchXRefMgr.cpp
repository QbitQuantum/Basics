//virtual
int
MLDispatchXRefMgr::acceptQBP(MHL7Msg& message, const MString& event)
{
  MLogClient logClient;
  logClient.log(MLogClient::MLOG_CONVERSATION,
		"peer",
		"MLDispatchXRefMgr::acceptQBP",
		__LINE__,
		MString("Accepting QBP event ")+event);

  MString queryName = message.getValue("QPD", 1, 0);
  MString queryTag  = message.getValue("QPD", 2, 0);
  MString personID  = message.getValue("QPD", 3, 1);
  MString personIDIssuer  = message.getValue("QPD", 3, 4);

  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE, "XRef Mgr: Query Parameters from inbound query");
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE, "Query Name: " + queryName);
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE, "Query Tag:  " + queryTag);
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE, "Person ID:  " + personID);
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE, "PID Issuer: " + personIDIssuer);


  int status = 0;
  MPatientVector v;
  status = mDatabase->crossReferenceLookup(v, personID, personIDIssuer);
#if 0
  if (status != 0) {
    return status;
  }
#endif
  MPatientVector::iterator p = v.begin();
  for (; p != v.end(); p++) {
    MString xrPatID = (*p).patientID();
    MString xrIssuer = (*p).issuerOfPatientID();
    MString identifierType = (*p).identifierType();
  }
  // Let the base class see the XXX; it will generate the ACK
  // Moore 2005.09.20 Remove the 3 lines below.
  // As of ITI TF 2.0, 2005.08.15, we use Immediate mode with no ACK
//  MHL7Msg* ack = mFactory.produceACK(message);
//  mHandler->sendHL7Message(*ack);
//  delete ack;

  MHL7Msg* rsp = mFactory.produceRSP(message);
  if (status == 2) {		// We did not recognize the domain
    this->updateRSPMessageUnknownIssuer(rsp);
  } else {
    this->updateRSPMessage(rsp, personID, personIDIssuer, v);
  }
  mHandler->sendHL7Message(*rsp);
  delete rsp;

  return status;
}