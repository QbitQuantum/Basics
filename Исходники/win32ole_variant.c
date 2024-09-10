static void
ole_val2olevariantdata(VALUE val, VARTYPE vt, struct olevariantdata *pvar)
{
    HRESULT hr = S_OK;

    if (((vt & ~VT_BYREF) ==  (VT_ARRAY | VT_UI1)) && RB_TYPE_P(val, T_STRING)) {
        long len = RSTRING_LEN(val);
        void *pdest = NULL;
        SAFEARRAY *p = NULL;
        SAFEARRAY *psa = SafeArrayCreateVector(VT_UI1, 0, len);
        if (!psa) {
            rb_raise(rb_eRuntimeError, "fail to SafeArrayCreateVector");
        }
        hr = SafeArrayAccessData(psa, &pdest);
        if (SUCCEEDED(hr)) {
            memcpy(pdest, RSTRING_PTR(val), len);
            SafeArrayUnaccessData(psa);
            V_VT(&(pvar->realvar)) = (vt & ~VT_BYREF);
            p = V_ARRAY(&(pvar->realvar));
            if (p != NULL) {
                SafeArrayDestroy(p);
            }
            V_ARRAY(&(pvar->realvar)) = psa;
            if (vt & VT_BYREF) {
                V_VT(&(pvar->var)) = vt;
                V_ARRAYREF(&(pvar->var)) = &(V_ARRAY(&(pvar->realvar)));
            } else {
                hr = VariantCopy(&(pvar->var), &(pvar->realvar));
            }
        } else {
            if (psa)
                SafeArrayDestroy(psa);
        }
    } else if (vt & VT_ARRAY) {
        if (val == Qnil) {
            V_VT(&(pvar->var)) = vt;
            if (vt & VT_BYREF) {
                V_ARRAYREF(&(pvar->var)) = &(V_ARRAY(&(pvar->realvar)));
            }
        } else {
            hr = ole_val_ary2variant_ary(val, &(pvar->realvar), (VARTYPE)(vt & ~VT_BYREF));
            if (SUCCEEDED(hr)) {
                if (vt & VT_BYREF) {
                    V_VT(&(pvar->var)) = vt;
                    V_ARRAYREF(&(pvar->var)) = &(V_ARRAY(&(pvar->realvar)));
                } else {
                    hr = VariantCopy(&(pvar->var), &(pvar->realvar));
                }
            }
        }
#if (_MSC_VER >= 1300) || defined(__CYGWIN__) || defined(__MINGW32__)
    } else if ( (vt & ~VT_BYREF) == VT_I8 || (vt & ~VT_BYREF) == VT_UI8) {
        ole_val2variant_ex(val, &(pvar->realvar), (vt & ~VT_BYREF));
        ole_val2variant_ex(val, &(pvar->var), (vt & ~VT_BYREF));
        V_VT(&(pvar->var)) = vt;
        if (vt & VT_BYREF) {
            ole_set_byref(&(pvar->realvar), &(pvar->var), vt);
        }
#endif
    } else if ( (vt & ~VT_BYREF) == VT_ERROR) {
        ole_val2variant_err(val, &(pvar->realvar));
        if (vt & VT_BYREF) {
            ole_set_byref(&(pvar->realvar), &(pvar->var), vt);
        } else {
            hr = VariantCopy(&(pvar->var), &(pvar->realvar));
        }
    } else {
        if (val == Qnil) {
            V_VT(&(pvar->var)) = vt;
            if (vt == (VT_BYREF | VT_VARIANT)) {
                ole_set_byref(&(pvar->realvar), &(pvar->var), vt);
            } else {
                V_VT(&(pvar->realvar)) = vt & ~VT_BYREF;
                if (vt & VT_BYREF) {
                    ole_set_byref(&(pvar->realvar), &(pvar->var), vt);
                }
            }
        } else {
            ole_val2variant_ex(val, &(pvar->realvar), (VARTYPE)(vt & ~VT_BYREF));
            if (vt == (VT_BYREF | VT_VARIANT)) {
                ole_set_byref(&(pvar->realvar), &(pvar->var), vt);
            } else if (vt & VT_BYREF) {
                if ( (vt & ~VT_BYREF) != V_VT(&(pvar->realvar))) {
                    hr = VariantChangeTypeEx(&(pvar->realvar), &(pvar->realvar),
                            cWIN32OLE_lcid, 0, (VARTYPE)(vt & ~VT_BYREF));
                }
                if (SUCCEEDED(hr)) {
                    ole_set_byref(&(pvar->realvar), &(pvar->var), vt);
                }
            } else {
                if (vt == V_VT(&(pvar->realvar))) {
                    hr = VariantCopy(&(pvar->var), &(pvar->realvar));
                } else {
                    hr = VariantChangeTypeEx(&(pvar->var), &(pvar->realvar),
                            cWIN32OLE_lcid, 0, vt);
                }
            }
        }
    }
    if (FAILED(hr)) {
        ole_raise(hr, eWIN32OLERuntimeError, "failed to change type");
    }
}