static STATUS_t
ValidateXCS(const TCHAR *FileName, GRecord &oGRecord)
{
  STATUS_t eStatus = eValidationFileNotFound;

  FILE *inFile = nullptr;
  inFile = _tfopen(FileName, _T("r"));
  if (inFile == nullptr)
    return eStatus;

  fclose(inFile);

  eStatus = eValidationFailed;

  oGRecord.Initialize();
  if (oGRecord.VerifyGRecordInFile(FileName))
    eStatus = eValidationPassed;

  return eStatus;
}