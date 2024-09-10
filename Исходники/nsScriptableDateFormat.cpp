NS_IMETHODIMP nsScriptableDateFormat::FormatDateTime(
                            const PRUnichar *aLocale, 
                            nsDateFormatSelector dateFormatSelector, 
                            nsTimeFormatSelector timeFormatSelector, 
                            PRInt32 year, 
                            PRInt32 month, 
                            PRInt32 day, 
                            PRInt32 hour, 
                            PRInt32 minute, 
                            PRInt32 second, 
                            PRUnichar **dateTimeString)
{
  // We can't have a valid date with the year, month or day
  // being lower than 1.
  if (year < 1 || month < 1 || day < 1)
    return NS_ERROR_INVALID_ARG;

  nsresult rv;
  nsAutoString localeName(aLocale);
  *dateTimeString = nsnull;

  nsCOMPtr<nsILocale> locale;
  // re-initialise locale pointer only if the locale was given explicitly
  if (!localeName.IsEmpty()) {
    // get locale service
    nsCOMPtr<nsILocaleService> localeService(do_GetService(kLocaleServiceCID, &rv));
    NS_ENSURE_SUCCESS(rv, rv);
    // get locale
    rv = localeService->NewLocale(localeName, getter_AddRefs(locale));
    NS_ENSURE_SUCCESS(rv, rv);
  }

  nsCOMPtr<nsIDateTimeFormat> dateTimeFormat(do_CreateInstance(kDateTimeFormatCID, &rv));
  NS_ENSURE_SUCCESS(rv, rv);

  tm tmTime;
  time_t timetTime;

  memset(&tmTime, 0, sizeof(tmTime));
  tmTime.tm_year = year - 1900;
  tmTime.tm_mon = month - 1;
  tmTime.tm_mday = day;
  tmTime.tm_hour = hour;
  tmTime.tm_min = minute;
  tmTime.tm_sec = second;
  tmTime.tm_yday = tmTime.tm_wday = 0;
  tmTime.tm_isdst = -1;
  timetTime = mktime(&tmTime);

  if ((time_t)-1 != timetTime) {
    rv = dateTimeFormat->FormatTime(locale, dateFormatSelector, timeFormatSelector, 
                                     timetTime, mStringOut);
  }
  else {
    // if mktime fails (e.g. year <= 1970), then try NSPR.
    PRTime prtime;
    char string[32];
    sprintf(string, "%.2d/%.2d/%d %.2d:%.2d:%.2d", month, day, year, hour, minute, second);
    if (PR_SUCCESS != PR_ParseTimeString(string, PR_FALSE, &prtime))
      return NS_ERROR_INVALID_ARG;

    rv = dateTimeFormat->FormatPRTime(locale, dateFormatSelector, timeFormatSelector, 
                                      prtime, mStringOut);
  }
  if (NS_SUCCEEDED(rv))
    *dateTimeString = ToNewUnicode(mStringOut);

  return rv;
}