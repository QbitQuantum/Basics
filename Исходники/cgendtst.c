static void TestGenderInfo(void) {
  UErrorCode status = U_ZERO_ERROR;
  const UGenderInfo* actual_gi = ugender_getInstance("fr_CA", &status);
  UGender actual;
  if (U_FAILURE(status)) {
    log_err_status(status, "Fail to create UGenderInfo - %s (Are you missing data?)", u_errorName(status));
    return;
  }
  actual = ugender_getListGender(actual_gi, kAllFemale, UPRV_LENGTHOF(kAllFemale), &status);
  if (U_FAILURE(status)) {
    log_err("Fail to get gender of list - %s\n", u_errorName(status));
    return;
  }
  if (actual != UGENDER_FEMALE) {
    log_err("Expected UGENDER_FEMALE got %d\n", actual);
  }
}