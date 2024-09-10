int
MHL7DomainXlate::translatePDQQPD3(const MString& s, MPatient& patient) const
{
  MLogClient logClient;
  logClient.log(MLogClient::MLOG_VERBOSE,
	"","MHL7DomainXlate::translatepdQQPD3",
	__LINE__, "Enter method");
  MString queryString = s;
  int idx = 0;
  MString firstName = "";
  MString lastName = "";
  MString patientID = "";
  MString dateOfBirth = "";

  while (queryString.tokenExists('~', idx)) {
    MString x = queryString.getToken('~', idx);
//    cout << idx << ":" << x << endl;
    logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	MString("Next token from query: ") + x);
    MString headerCharacter = x.subString(0, 1);
    if (headerCharacter != "@") {
      continue;
    }
    MString x1 = x.subString(1, 0);
    if (!x1.tokenExists('^', 1)) {
      continue;
    }
    MString fieldName = x1.getToken('^', 0);
    MString fieldValue= x1.getToken('^', 1);
    MString debugString = MString("Field Name: ") + fieldName
	+ " Field Value: " + fieldValue;

    logClient.logTimeStamp(MLogClient::MLOG_VERBOSE, debugString);
//    cout << "Field Name:  " << fieldName << endl;
//    cout << "Field Value: " << fieldValue << endl;
    idx++;
    if (fieldName == "PID.5.1.1") {
      lastName = fieldValue;
    } else if (fieldName == "PID.5.2") {
      firstName = fieldValue;
    } else if (fieldName == "PID.3.1") {
      patientID = fieldValue;
    } else if (fieldName == "PID.7.1") {
      dateOfBirth = fieldValue;
    }
  }
  if (lastName == "" && firstName == "") {
  } else if (firstName == "") {
    patient.patientName(lastName + MString("%"));
  } else if (lastName == "") {
    patient.patientName(MString("%^") + firstName);
  } else {
    patient.patientName(lastName + MString("%^") + firstName + MString("%"));
  }
  patient.patientID(patientID);
  patient.dateOfBirth(dateOfBirth);
  logClient.log(MLogClient::MLOG_VERBOSE,
	"","MHL7DomainXlate::translatepdQQPD3",
	__LINE__, "Exit method");
  return 0;
}