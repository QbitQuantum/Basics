nsresult nsCollationMacUC::EnsureCollator(const int32_t newStrength) 
{
  NS_ENSURE_TRUE(mInit, NS_ERROR_NOT_INITIALIZED);
  if (mHasCollator && (mLastStrength == newStrength))
    return NS_OK;

  nsresult res;
  res = CleanUpCollator();
  NS_ENSURE_SUCCESS(res, res);

  if (mUseICU) {
    NS_ENSURE_TRUE(mLocaleICU, NS_ERROR_NOT_INITIALIZED);

    UErrorCode status;
    status = U_ZERO_ERROR;
    mCollatorICU = ucol_open(mLocaleICU, &status);
    NS_ENSURE_TRUE(U_SUCCESS(status), NS_ERROR_FAILURE);

    UCollationStrength strength;
    UColAttributeValue caseLevel;
    res = ConvertStrength(newStrength, &strength, &caseLevel);
    NS_ENSURE_SUCCESS(res, res);

    status = U_ZERO_ERROR;
    ucol_setAttribute(mCollatorICU, UCOL_STRENGTH, strength, &status);
    NS_ENSURE_TRUE(U_SUCCESS(status), NS_ERROR_FAILURE);
    ucol_setAttribute(mCollatorICU, UCOL_CASE_LEVEL, caseLevel, &status);
    NS_ENSURE_TRUE(U_SUCCESS(status), NS_ERROR_FAILURE);
    ucol_setAttribute(mCollatorICU, UCOL_ALTERNATE_HANDLING, UCOL_DEFAULT, &status);
    NS_ENSURE_TRUE(U_SUCCESS(status), NS_ERROR_FAILURE);
    ucol_setAttribute(mCollatorICU, UCOL_NUMERIC_COLLATION, UCOL_OFF, &status);
    NS_ENSURE_TRUE(U_SUCCESS(status), NS_ERROR_FAILURE);
    ucol_setAttribute(mCollatorICU, UCOL_NORMALIZATION_MODE, UCOL_ON, &status);
    NS_ENSURE_TRUE(U_SUCCESS(status), NS_ERROR_FAILURE);
    ucol_setAttribute(mCollatorICU, UCOL_CASE_FIRST, UCOL_DEFAULT, &status);
    NS_ENSURE_TRUE(U_SUCCESS(status), NS_ERROR_FAILURE);
  } else {
    OSStatus err;
    UCCollateOptions newOptions;
    res = StrengthToOptions(newStrength, &newOptions);
    NS_ENSURE_SUCCESS(res, res);

    LocaleOperationVariant opVariant = 0; // default variant for now
    err = ::UCCreateCollator(mLocale, opVariant, newOptions, &mCollator);
    NS_ENSURE_TRUE((err == noErr), NS_ERROR_FAILURE);
  }

  mHasCollator = true;

  mLastStrength = newStrength;
  return NS_OK;
}