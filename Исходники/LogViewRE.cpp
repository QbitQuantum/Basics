void LogViewRE::Log(LogFacility logType, LPCWSTR aName, SAFEARRAY* pVals, LPDISPATCH pOptions)
{
  LogIntro(logType, aName);

  ATLASSERT(0 == pVals->rgsabound[0].lLbound);
  VARIANT* pVariants = (VARIANT*)pVals->pvData;

  // see if we can do a printf
  ULONG valueCount = pVals->rgsabound[0].cElements;
  ULONG currentValueIndex = 0;

  if ((valueCount > 1) && (VT_BSTR == pVariants[0].vt)) {
    ++currentValueIndex;
    CStringW sIn(pVariants[0].bstrVal), sOut;
    int pos = sIn.Find(L'%');
    int posLast = 0;
    int sInLength = sIn.GetLength();
    while((-1 != pos) && (pos < sInLength-1) && (currentValueIndex < valueCount)) {
      // add everything before
      sOut += sIn.Mid(posLast, (pos - posLast));
      ++pos;
      wchar_t format = sIn[pos];
      CComVariant vt(pVariants[currentValueIndex]);
      HRESULT hr = E_FAIL;
      switch(format) {
        case L's':
          // a string: change to string type and log as it is
          hr = vt.ChangeType(VT_BSTR);
          if (SUCCEEDED(hr)) {
            sOut += vt.bstrVal;
          }
          ++currentValueIndex;
          ++pos;
          break;
        case L'd':
        case L'i':
          // an integer number
          // check for type, set "undefined" if empty, "NaN" if can't be converted to a number
          {
            CStringW s;
            switch (vt.vt) {
              case VT_I1:
              case VT_I2:
              case VT_I4:
              case VT_INT:
                s.Format(L"%i", vt.lVal);
                break;
              case VT_UI1:
              case VT_UI2:
              case VT_UI4:
              case VT_UINT:
                s.Format(L"%u", vt.ulVal);
                break;
              case VT_EMPTY:
                s = L"-undefined-";
                break;
              default:
                if (SUCCEEDED(vt.ChangeType(VT_UI4))) {
                  s.Format(L"%u", vt.ulVal);
                }
                else if (SUCCEEDED(vt.ChangeType(VT_I4))) {
                  s.Format(L"%u", vt.lVal);
                }
                else {
                  s = L"NaN";
                }
                break;
            }
            ++currentValueIndex;
            sOut += s;
          }
          ++pos;
          break;
        case L'f':
          // a float number
          // check for type, set "undefined" if empty, "NaN" if can't be converted to a number
          {
            CStringW s;
            switch (vt.vt) {
              case VT_R4:
                s.Format(L"%f", vt.fltVal);
                break;
              case VT_R8:
                s.Format(L"%f", vt.dblVal);
                break;
              case VT_EMPTY:
                s = L"-undefined-";
                break;
              default:
                if (SUCCEEDED(vt.ChangeType(VT_R8))) {
                  s.Format(L"%f", vt.dblVal);
                }
                else {
                  s = L"NaN";
                }
                break;
            }
            ++currentValueIndex;
            sOut += s;
          }
          ++pos;
          break;
        case L'o':
          // an object
          // check for type, set "undefined" if empty, "NaO" if can't be converted to string representation
          if (VT_DISPATCH == vt.vt) {
            CStringW s, s2;
            s2.Format(L"[Object at 0x%%0%ix]", sizeof(vt.pdispVal) * 2);
            s.Format(s2, (IUnknown*)(vt.pdispVal));
            sOut += s;
          }
          else if (VT_EMPTY == vt.vt) {
            sOut += L"-undefined-";
          }
          else if (SUCCEEDED(vt.ChangeType(VT_BSTR))) {
            sOut += vt.bstrVal;
          }
          else {
            sOut += L"NaO";
          }
          ++currentValueIndex;
          ++pos;
          break;
        default:
          // all other cases: not a format spec, take it as it is
          sOut += L'%';
          sOut += format;
          ++pos;
          break;
      }
      posLast = pos;
      pos = sIn.Find(L'%', pos);
    }
    // append the rest
    sOut += sIn.Mid(posLast);
    LogVariant(CComVariant(sOut));
    AppendText(_T(" "));
  }

  // log all the rest
  for(ULONG n = currentValueIndex; n < pVals->rgsabound[0].cElements; n++)
  {
    LogVariant(pVariants[n]);
    AppendText(_T(" "));
  }

  LogExtro();
}