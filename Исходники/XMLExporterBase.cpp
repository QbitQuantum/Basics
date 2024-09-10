HRESULT CXMLExporterBase::WriteOption(BSTR name, _variant_t value)
{
    HRESULT hr;
    _bstr_t bName(name, true);
    switch( value.vt )
    {
        case VT_I4:
        case VT_I2:
            Write("<Option name=\"%s\" value=\"%d\" />\n",
                  (const char*)bName, (long)value);
            break;
        case VT_R4:
        case VT_R8:
            Write("<Option name=\"%s\" value=\"%g\" />\n",
                  (const char*)bName, (double)value);
            break;
        case VT_BOOL:
            Write("<Option name=\"%s\" value=\"%s\" />\n",
                  (const char*)bName, BoolToText((bool)value));
            break;
        case VT_BSTR:
        {
            _bstr_t bValue = (_bstr_t) value.bstrVal;
            Write("<Option name=\"%s\" value=\"%s\" />\n",
                (const char*)bName, (const char*)bValue);
        }
            break;
        case VT_DATE:
        {
#ifdef _WIN32
            DATE time = (DATE)value;
            SYSTEMTIME sysTime;
            if( VariantTimeToSystemTime(time, &sysTime) )
            {
                TCHAR dateStr[16], timeStr[16];
                GetDateFormat(NULL, 0, &sysTime, _T("MM'/'dd'/'yyyy"), dateStr, 16);
                GetTimeFormat(NULL, 0, &sysTime, _T("HH':'mm':'ss"), timeStr, 16);
                Write("<Option name=\"%s\" value=\"%s %s\" />\n",
                      (const char*)bName, dateStr, timeStr);
            }
            else
            {
                Write("<Option name=\"%s\" value=\"invalid time\" />\n",
                      (const char*)bName);
            }
#else
            // On the Mac, DATE == time_t
            DATE date = value.date;
            Write("<Option name=\"%s\" value=\"%s\" />\n",
                  (const char*)bName, asctime(gmtime((time_t*)&date)));
#endif
        }
            break;
        case VT_UNKNOWN:
            // The unknown can be either a point or a vector
            {
                IUnknown* pUnk = value.punkVal;
                ISkpPoint3d* pPoint = NULL;
                hr = pUnk->QueryInterface(IID_ISkpPoint3d, (void**)&pPoint);
                if( SUCCEEDED(hr) )
                {
                    double p[3];
                    pPoint->Get(p, p+1, p+2);
                    WritePosition( (const char*)bName , p);
                    RELEASE(pPoint);
                }
                else
                {
                    ISkpVector3d* pVec = NULL;
                    hr = pUnk->QueryInterface(IID_ISkpVector3d, (void**)&pVec);
                    if( SUCCEEDED(hr) )
                    {
                        double v[3];
                        pVec->Get(v,v+1,v+2);
                        WriteVector( (const char*)bName , v);
                        RELEASE(pVec);
                    }
                }
            
            }
            break;
        default:
            Write("<Option name=\"%s\" value=\"unknown type\" />\n", (const char*)bName);
    }

    return S_OK;
}