static wchar_t*
ParseVP(wchar_t* aPart, VersionPartW& aResult)
{

  wchar_t* dot;

  aResult.numA = 0;
  aResult.strB = nullptr;
  aResult.strBlen = 0;
  aResult.numC = 0;
  aResult.extraD = nullptr;

  if (!aPart) {
    return aPart;
  }

  dot = wcschr(aPart, '.');
  if (dot) {
    *dot = '\0';
  }

  if (aPart[0] == '*' && aPart[1] == '\0') {
    static wchar_t kEmpty[] = L"";

    aResult.numA = INT32_MAX;
    aResult.strB = kEmpty;
  } else {
    aResult.numA = wcstol(aPart, const_cast<wchar_t**>(&aResult.strB), 10);
  }

  if (!*aResult.strB) {
    aResult.strB = nullptr;
    aResult.strBlen = 0;
  } else {
    if (aResult.strB[0] == '+') {
      static wchar_t kPre[] = L"pre";

      ++aResult.numA;
      aResult.strB = kPre;
      aResult.strBlen = sizeof(kPre) - 1;
    } else {
      const wchar_t* numstart = wcspbrk(aResult.strB, L"0123456789+-");
      if (!numstart) {
        aResult.strBlen = wcslen(aResult.strB);
      } else {
        aResult.strBlen = numstart - aResult.strB;

        aResult.numC = wcstol(numstart, &aResult.extraD, 10);
        if (!*aResult.extraD) {
          aResult.extraD = nullptr;
        }
      }
    }
  }

  if (dot) {
    ++dot;

    if (!*dot) {
      dot = nullptr;
    }
  }

  return dot;
}