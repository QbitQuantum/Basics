//  virtual
CONDITION
MLQueryUPS::returnCFindDataSet(DUL_PRESENTATIONCONTEXT* ctx,
                                       MSG_C_FIND_REQ** message,
                                       MSG_C_FIND_RESP* response,
                                       DUL_ASSOCIATESERVICEPARAMETERS* params,
			               const MString& queryLevelString,
                                       int index)
{
  MLogClient logClient;
  logClient.log(MLogClient::MLOG_VERBOSE,
		params->callingAPTitle,
		"MLQueryUPS::returnCFindDataSet",
		__LINE__,
		"Sending C-Find dataset");

  int size = mObjectsVector.size();
  if (index > size) {
    response->status = MSG_K_SUCCESS;
    response->dataSetType = DCM_CMDDATANULL;
  } else {
    response->status = MSG_K_C_FIND_MATCHCONTINUING;
    response->dataSetType = DCM_CMDDATAIDENTIFIER;

    MUPS  ups = mObjectsVector[index-1].ups();
    MUWLScheduledStationNameCodeVector ssnCodeVector = mObjectsVector[index-1].ssnCodeVector();
    MDICOMDomainXlate xlate;
    xlate.translateDICOM(ups, ssnCodeVector, (*message)->identifier, response->identifier);
    MDICOMWrapper x((*message)->identifier);
    MString specificCharacterSet = x.getString(0x00080005);
    if (specificCharacterSet != "") {
      MDICOMWrapper resp(response->identifier);
      resp.setString(0x00080005, specificCharacterSet);
    }
  }
  logClient.log(MLogClient::MLOG_VERBOSE,
		params->callingAPTitle,
		"MLQueryUPS::returnCFindDataSet",
		__LINE__,
		"Sending C-Find dataset complete");

  return SRV_NORMAL;
}