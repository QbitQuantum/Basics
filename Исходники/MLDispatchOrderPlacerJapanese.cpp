// virtual
int
MLDispatchOrderPlacerJapanese::acceptADT(MHL7Msg& message, const MString& event)
{
  MLogClient logClient;
  logClient.log(MLogClient::MLOG_CONVERSATION,
		"peer",
		"MLDispatchOrderPlacerJapanese::acceptADT",
		__LINE__,
		MString("Accepting ADT event ")+event);

  MString charSet = message.getValue("MSH", 18, 0);
  MString charSetRep1 = "";
  MString charSetRep2 = "";
  if (charSet.tokenExists('~', 0)) {
    charSetRep1 = charSet.getToken('~', 0);
  }
  if (charSet.tokenExists('~', 1)) {
    charSetRep2 = charSet.getToken('~', 1);
  }

  if (charSetRep1 != "ISO IR6") {
    logClient.log(MLogClient::MLOG_ERROR,
		"peer",
		"MLDispatchOrderPlacerJapanese::acceptADT",
		__LINE__,
		MString("Wrong value in MSH.18 (Character set)") + charSet);
    MHL7Dispatcher::acceptMessageApplicationError(message, event, "AE", "207");
    return 0;
  } else if (charSetRep2 != "ISO IR87") {
    logClient.log(MLogClient::MLOG_ERROR,
		"peer",
		"MLDispatchOrderPlacerJapanese::acceptADT",
		__LINE__,
		MString("Wrong value in MSH.18 (Character set)") + charSet);
    MHL7Dispatcher::acceptMessageApplicationError(message, event, "AE", "207");
    return 0;
  }

  MHL7DomainXlate xLate;
  MPatient patient;
  MVisit   visit;

  xLate.issuer1("ADT1");
  xLate.issuer2("MPI");
  xLate.translateHL7(message, patient);
  xLate.translateHL7(message, visit);

  MString patientString = patient.patientID() + ":" +
		patient.issuerOfPatientID() + ":" +
		patient.patientName();
  logClient.log(MLogClient::MLOG_VERBOSE,
		"peer",
		"MLDispatchOrderPlacerJapanese::acceptADT",
		__LINE__,
		MString("Patient is: ")+patientString);

  processInfo( event, patient, visit);

  // Let the base class see the ADT; it will generate the ACK
  MHL7Dispatcher::acceptADT(message, event);

  return 0;  
}