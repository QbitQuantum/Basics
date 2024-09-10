void WMICOL::ReadColumn(PGLOBAL g)
  {
  // Get the value of the Name property
  Res = Tdbp->ClsObj->Get(_bstr_t(Name), 0, &Prop, &Ctype, 0);

  switch (Prop.vt) {
    case VT_EMPTY:
    case VT_NULL:
    case VT_VOID:
      Value->Reset();
      break;
    case VT_BSTR:
      Value->SetValue_psz(_com_util::ConvertBSTRToString(Prop.bstrVal));
      break;
    case VT_I4:
    case VT_UI4:
      Value->SetValue(Prop.lVal);
      break;
    case VT_I2:
    case VT_UI2:
      Value->SetValue(Prop.iVal);
      break;
    case VT_INT:
    case VT_UINT:
      Value->SetValue((int)Prop.intVal);
      break;
    case VT_BOOL:
      Value->SetValue(((int)Prop.boolVal) ? 1 : 0);
      break;
    case VT_R8:
      Value->SetValue(Prop.dblVal);
      break;
    case VT_R4:
      Value->SetValue((double)Prop.fltVal);
      break;
    case VT_DATE:
      switch (Value->GetType()) {
        case TYPE_DATE:
         {SYSTEMTIME stm;
          struct tm  ptm;
          int        rc = VariantTimeToSystemTime(Prop.date, &stm);

          ptm.tm_year = stm.wYear;
          ptm.tm_mon  = stm.wMonth;
          ptm.tm_mday  = stm.wDay;
          ptm.tm_hour = stm.wHour;
          ptm.tm_min  = stm.wMinute;
          ptm.tm_sec  = stm.wSecond;
          ((DTVAL*)Value)->MakeTime(&ptm);
         }break;
        case TYPE_STRING:
         {SYSTEMTIME stm;
          char       buf[24];
          int        rc = VariantTimeToSystemTime(Prop.date, &stm);

          sprintf(buf, "%02d/%02d/%d %02d:%02d:%02d", 
                       stm.wDay, stm.wMonth, stm.wYear,
                       stm.wHour, stm.wMinute, stm.wSecond);
          Value->SetValue_psz(buf);
         }break;
        default:
          Value->SetValue((double)Prop.fltVal);
        } // endswitch Type

      break;
    default:
      // This will reset numeric column value
      Value->SetValue_psz("Type not supported");
      break;
    } // endswitch vt

  VariantClear(&Prop);
  } // end of ReadColumn