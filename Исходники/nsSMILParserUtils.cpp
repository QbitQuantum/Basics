nsresult
nsSMILParserUtils::ParseClockValue(const nsAString& aSpec,
                                   nsSMILTimeValue* aResult,
                                   PRUint32 aFlags,   // = 0
                                   PRBool* aIsMedia)  // = nsnull
{
  nsSMILTime offset = 0L;
  double component = 0.0;

  PRInt8 sign = 0;
  PRUint8 colonCount = 0;

  PRBool started = PR_FALSE;
  PRBool isValid = PR_TRUE;

  PRInt32 metricMultiplicand = MSEC_PER_SEC;

  PRBool numIsReal = PR_FALSE;
  PRBool prevNumCouldBeMin = PR_FALSE;
  PRBool numCouldBeMin = PR_FALSE;
  PRBool numCouldBeSec = PR_FALSE;
  PRBool isIndefinite = PR_FALSE;

  if (aIsMedia) {
    *aIsMedia = PR_FALSE;
  }

  NS_ConvertUTF16toUTF8 spec(aSpec);
  const char* start = spec.BeginReading();
  const char* end = spec.EndReading();

  while (start != end) {
    if (IsSpace(*start)) {
      if (started) {
        ++start;
        break;
      }
      // else, we haven't started yet, ignore initial whitespace
      ++start;

    } else if ((aFlags & kClockValueAllowSign)
               && (*start == '+' || *start == '-')) {
      if (sign != 0) {
        // sign has already been set
        isValid = PR_FALSE;
        break;
      }

      if (started) {
        // sign appears in the middle of the string
        isValid = PR_FALSE;
        break;
      }

      sign = (*start == '+') ? 1 : -1;
      ++start;
    // The NS_IS_DIGIT etc. macros are not locale-specific
    } else if (NS_IS_DIGIT(*start)) {
      prevNumCouldBeMin = numCouldBeMin;

      if (!ParseClockComponent(start, end, component, numIsReal, numCouldBeMin,
                               numCouldBeSec)) {
        isValid = PR_FALSE;
        break;
      }

      started = PR_TRUE;
    } else if (*start == ':') {
      ++colonCount;

      // Neither minutes nor hours can be reals
      if (numIsReal) {
        isValid = PR_FALSE;
        break;
      }

      // Clock value can't start with a ':'
      if (!started) {
        isValid = PR_FALSE;
        break;
      }

      // Can't have more than two colons
      if (colonCount > 2) {
        isValid = PR_FALSE;
        break;
      }

      // Multiply the offset by 60 and add the last accumulated component
      offset = offset * 60 + PRInt64(component);

      component = 0.0;
      ++start;
    } else if (NS_IS_ALPHA(*start)) {
      if (colonCount > 0) {
        isValid = PR_FALSE;
        break;
      }

      if ((aFlags & kClockValueAllowIndefinite)
          && ConsumeSubstring(start, end, "indefinite")) {
        // We set a separate flag because we don't know what the state of the
        // passed in time value is and we shouldn't change it in the case of a
        // bad input string (so we can't initialise it to 0ms for example).
        isIndefinite = PR_TRUE;
        if (aResult) {
          aResult->SetIndefinite();
        }
      } else if (aIsMedia && ConsumeSubstring(start, end, "media")) {
        *aIsMedia = PR_TRUE;
      } else if (!ParseMetricMultiplicand(start, end, metricMultiplicand)) {
        isValid = PR_FALSE;
        break;
      }

      // Nothing must come after the string except whitespace
      break;
    } else {
      isValid = PR_FALSE;
      break;
    }
  }

  if (!started) {
    isValid = PR_FALSE;
  }

  // Process remainder of string (if any) to ensure it is only trailing
  // whitespace (embedded whitespace is not allowed)
  SkipBeginWsp(start, end);
  if (start != end) {
    isValid = PR_FALSE;
  }

  // No more processing required if the value was "indefinite" or "media".
  if (isIndefinite || (aIsMedia && *aIsMedia))
    return NS_OK;

  // If there is more than one colon then the previous component must be a
  // correctly formatted minute (i.e. two digits between 00 and 59) and the
  // latest component must be a correctly formatted second (i.e. two digits
  // before the .)
  if (colonCount > 0 && (!prevNumCouldBeMin || !numCouldBeSec)) {
    isValid = PR_FALSE;
  }

  if (isValid) {
    // Tack on the last component
    if (colonCount > 0) {
      offset = offset * 60 * 1000;
      component *= 1000;
      // rounding
      component = (component >= 0) ? component + 0.5 : component - 0.5;
      offset += PRInt64(component);
    } else {
      component *= metricMultiplicand;
      // rounding
      component = (component >= 0) ? component + 0.5 : component - 0.5;
      offset = PRInt64(component);
    }

    if (aResult) {
      nsSMILTime millis = offset;

      if (sign == -1) {
        millis = -offset;
      }

      aResult->SetMillis(millis);
    }
  }

  return (isValid) ? NS_OK : NS_ERROR_FAILURE;
}