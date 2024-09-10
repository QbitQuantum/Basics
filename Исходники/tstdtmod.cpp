RBTestDataModule::RBTestDataModule(const char* name, TestLog& log, UErrorCode& status) 
: TestDataModule(name, log, status),
  fModuleBundle(NULL),
  fTestData(NULL),
  fInfoRB(NULL),
  tdpath(NULL)
{
  fNumberOfTests = 0;
  fDataTestValid = TRUE;
  fModuleBundle = getTestBundle(name, status);
  if(fDataTestValid) {
    fTestData = ures_getByKey(fModuleBundle, "TestData", NULL, &status);
    fNumberOfTests = ures_getSize(fTestData);
    fInfoRB = ures_getByKey(fModuleBundle, "Info", NULL, &status);
    if(status != U_ZERO_ERROR) {
      log.errln(UNICODE_STRING_SIMPLE("Unable to initalize test data - missing mandatory description resources!"));
      fDataTestValid = FALSE;
    } else {
      fInfo = new RBDataMap(fInfoRB, status);
    }
  }
}