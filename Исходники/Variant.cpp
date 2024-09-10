STDAPI
VariantChangeType(
    VARIANTARG FAR* pvargDest,
    VARIANTARG FAR* pvargSrc,
    unsigned short wFlags,
    VARTYPE vt)
{
    VARIANT varTmp;
    HRESULT hresult;
    VARTYPE vtSrc;

    if (pvargDest == NULL || pvargSrc == NULL)
      return(E_INVALIDARG);

    vtSrc = V_VT(pvargSrc); // get src vartype

    hresult = NOERROR;          // assume success
    // NOTE: all code after this point must go to LError0 upon Error.

    // should have validated the destination type at this point (to ensure
    // that the below optimized switch statement will work properly).
    switch ( VTSW(vtSrc, vt) )
    {
      case VTSW(VT_BOOL, VT_BOOL):
      case VTSW(VT_I2, VT_I2):
      case VTSW(VT_I4, VT_I4):
      case VTSW(VT_INT, VT_INT):
      case VTSW(VT_I8, VT_I8):
      case VTSW(VT_R4, VT_R4):
      case VTSW(VT_R8, VT_R8):
      case VTSW(VT_CY, VT_CY):
      case VTSW(VT_DECIMAL, VT_DECIMAL):
      case VTSW(VT_I1, VT_I1):
      case VTSW(VT_UI1, VT_UI1):
      case VTSW(VT_UI2, VT_UI2):
      case VTSW(VT_UI4, VT_UI4):
      case VTSW(VT_UINT, VT_UINT):
      case VTSW(VT_UI8, VT_UI8):
        varTmp = *pvargSrc;
        break;

      case VTSW(VT_EMPTY, VT_BSTR):
        hresult = ErrSysAllocString(OASTR(""), &V_BSTR(&varTmp));
        break;

      case VTSW(VT_BOOL, VT_BSTR):
        //fall through to return "0" or "-1"
      case VTSW(VT_I2, VT_BSTR):
        hresult = VarBstrFromI2(V_I2(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_I4, VT_BSTR):
      case VTSW(VT_INT, VT_BSTR):
        hresult = VarBstrFromI4(V_I4(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_I8, VT_BSTR):
        hresult = VarBstrFromI8(V_I8(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_R4, VT_BSTR):
        hresult = VarBstrFromR4(V_R4(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;


      case VTSW(VT_R8, VT_BSTR):
        hresult = VarBstrFromR8(V_R8(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_CY, VT_BSTR):
        hresult = VarBstrFromCy(V_CY(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_DECIMAL, VT_BSTR):
        hresult = VarBstrFromDec(&pvargSrc->n1.decVal, LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_I1, VT_BSTR):
        hresult = VarBstrFromI1(V_I1(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_UI1, VT_BSTR):
        hresult = VarBstrFromUI1(V_UI1(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_UI2, VT_BSTR):
        hresult = VarBstrFromUI2(V_UI2(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_UI4, VT_BSTR):
      case VTSW(VT_UINT, VT_BSTR):
        hresult = VarBstrFromUI4(V_UI4(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_UI8, VT_BSTR):
        hresult = VarBstrFromUI8(V_UI8(pvargSrc), LOCALE_USER_DEFAULT, 0, &V_BSTR(&varTmp));
        break;

      case VTSW(VT_BSTR, VT_BSTR):
        hresult = ErrSysAllocString(V_BSTR(pvargSrc), &V_BSTR(&varTmp));
        break;

      case VTSW(VT_DATE, VT_BSTR):
          _ASSERTE(false);
          hresult = RESULT(DISP_E_TYPEMISMATCH);
          break;

      default:
        if (vtSrc >= VT_VARIANT) {
          IfFailGo(IsLegalVartype(vtSrc), LError0);
        }

        // everybody else gets a type mis-match error
        _ASSERTE(false);
        hresult = RESULT(DISP_E_TYPEMISMATCH);
        break;
    }

    if (FAILED(hresult))
    {
        goto LError0;
    }

    // now set the tag in temp variant.  Errors after this point have to
    // goto LError1 to potentially clear this variant.
    V_VT(&varTmp) = vt;

    // now that we have succeeded, we can go ahead and destroy our
    // destination variant.
    if (V_VT(pvargDest) >= VT_BSTR) {
        IfFailGo(VariantClear(pvargDest), LError1);
    }

    // copy in the variant we just created
    memcpy(pvargDest, &varTmp, sizeof(VARIANT));

    return NOERROR;

LError1:;
    VariantClear(&varTmp);
    // fall through

LError0:;
    return hresult;
}