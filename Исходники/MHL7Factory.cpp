int
MHL7Factory::appendRSPK22PatientIdentification(MHL7Msg& msg, MStringMap& m)
{
  MLogClient logClient;
  logClient.log(MLogClient::MLOG_VERBOSE,
	"", "MHL7Factor::appendRSPK22PatientIdentification",
	__LINE__, "Enter method");

  MString pID   = m["pid3"];
  MString pName = m["pid5"];
  MString pDOB  = m["pid7"];
  MString pSex  = m["pid8"];
  MString pAddr = m["pid11"];

  MString debugString = pID + ":" + pName + ":" + pDOB + ":" + pSex + ":" + pAddr;
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE, debugString);
//  cout << "Patient ID   " << pID   << endl;
//  cout << "Patient Name " << pName << endl;
//  cout << "Patient DOB  " << pDOB  << endl;
//  cout << "Patient Sex  " << pSex  << endl;
//  cout << "Patient Addr " << pAddr << endl;

  MString x = msg.firstSegment();
  while (x != "") {
    x = msg.nextSegment();
  }
  msg.insertSegment("PID");
  msg.setValue(3, 0, pID);
  msg.setValue(5, 0, pName);
  msg.setValue(7, 0, pDOB);
  msg.setValue(8, 0, pSex);
  msg.setValue(11, 0, pAddr);

  logClient.log(MLogClient::MLOG_VERBOSE,
	"", "MHL7Factor::appendRSPK22PatientIdentification",
	__LINE__, "Leave method");
  return 0;
}