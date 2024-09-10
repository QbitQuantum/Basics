PHPAPI void php_pval_to_variant_ex(pval *pval_arg, VARIANT *var_arg, pval *pval_type, int codepage)
{
      OLECHAR *unicode_str;

      var_arg->vt = (short) pval_type->value.lval;

      switch(var_arg->vt)
      {
         case VT_UI1:
            convert_to_long_ex(&pval_arg);
            var_arg->bVal = (unsigned char)pval_arg->value.lval;
            break;

         case VT_I2:
            convert_to_long_ex(&pval_arg);
            var_arg->iVal = (short)pval_arg->value.lval;
            break;

         case VT_I4:
            convert_to_long_ex(&pval_arg);
            var_arg->lVal = pval_arg->value.lval;
            break;

         case VT_R4:
            convert_to_double_ex(&pval_arg);
            var_arg->fltVal = (float)pval_arg->value.dval;
            break;

         case VT_R8:
            convert_to_double_ex(&pval_arg);
            var_arg->dblVal = pval_arg->value.dval;
            break;

         case VT_BOOL:
            convert_to_boolean_ex(&pval_arg);
            var_arg->boolVal = (short)pval_arg->value.lval;
            break;

         case VT_ERROR:
            convert_to_long_ex(&pval_arg);
            var_arg->scode = pval_arg->value.lval;
            break;

         case VT_CY:
            convert_to_double_ex(&pval_arg);
            VarCyFromR8(pval_arg->value.dval, &(var_arg->cyVal));
            break;

         case VT_DATE:
         {
            SYSTEMTIME wintime;
            struct tm *phptime;

            phptime = gmtime(&(pval_arg->value.lval));

            wintime.wYear = phptime->tm_year + 1900;
            wintime.wMonth = phptime->tm_mon + 1;
            wintime.wDay = phptime->tm_mday;
            wintime.wHour = phptime->tm_hour;
            wintime.wMinute = phptime->tm_min;
            wintime.wSecond = phptime->tm_sec;

            SystemTimeToVariantTime(&wintime, &(var_arg->date));
         }

         case VT_BSTR:
            convert_to_string_ex(&pval_arg);
            unicode_str = php_char_to_OLECHAR(pval_arg->value.str.val, pval_arg->value.str.len, codepage);
            var_arg->bstrVal = SysAllocString(unicode_str);
            efree(unicode_str);
            break;

         case VT_DECIMAL:
            convert_to_string_ex(&pval_arg);
            unicode_str = php_char_to_OLECHAR(pval_arg->value.str.val, pval_arg->value.str.len, codepage);
            VarDecFromStr(unicode_str, LOCALE_SYSTEM_DEFAULT, 0, &(var_arg->decVal));
            break;

         case VT_DECIMAL|VT_BYREF:
            convert_to_string_ex(&pval_arg);
            unicode_str = php_char_to_OLECHAR(pval_arg->value.str.val, pval_arg->value.str.len, codepage);
            VarDecFromStr(unicode_str, LOCALE_SYSTEM_DEFAULT, 0, var_arg->pdecVal);
            break;

         case VT_UNKNOWN:
            php_pval_to_variant(pval_arg, var_arg, codepage);
            if(var_arg->vt != VT_DISPATCH)
               var_arg->vt = VT_EMPTY;
            else
            {
               HRESULT hr;

               hr = var_arg->pdispVal->lpVtbl->QueryInterface(var_arg->pdispVal, &IID_IUnknown, &(var_arg->punkVal));

               if (FAILED(hr))
               {
                  php_error(E_WARNING,"can't query IUnknown");
                  var_arg->vt = VT_EMPTY;
               }
               else
                  var_arg->vt = VT_UNKNOWN;
            }
            break;

         case VT_DISPATCH:
            php_pval_to_variant(pval_arg, var_arg, codepage);
            if(var_arg->vt != VT_DISPATCH)
               var_arg->vt = VT_EMPTY;
            break;

         case VT_UI1|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->pbVal = (unsigned char FAR*) &(pval_arg->value.lval);
            break;

         case VT_I2|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->piVal = (short FAR*) &(pval_arg->value.lval);
            break;

         case VT_I4|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->plVal = (long FAR*) &(pval_arg->value.lval);
            break;

         case VT_R4|VT_BYREF:
            convert_to_double(pval_arg);
            var_arg->pfltVal = (float FAR*) &(pval_arg->value.lval);
            break;

         case VT_R8|VT_BYREF:
            convert_to_double(pval_arg);
            var_arg->pdblVal = (double FAR*) &(pval_arg->value.lval);
            break;

         case VT_BOOL|VT_BYREF:
            convert_to_boolean(pval_arg);
            var_arg->pboolVal = (short FAR*) &(pval_arg->value.lval);
            break;

         case VT_ERROR|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->pscode = (long FAR*) &(pval_arg->value.lval);
            break;

         case VT_CY|VT_BYREF:
            convert_to_double_ex(&pval_arg);
            VarCyFromR8(pval_arg->value.dval, var_arg->pcyVal);
            break;

         case VT_DATE|VT_BYREF:
         {
            SYSTEMTIME wintime;
            struct tm *phptime;

            phptime = gmtime(&(pval_arg->value.lval));

            wintime.wYear   = phptime->tm_year + 1900;
            wintime.wMonth  = phptime->tm_mon + 1;
            wintime.wDay    = phptime->tm_mday;
            wintime.wHour   = phptime->tm_hour;
            wintime.wMinute = phptime->tm_min;
            wintime.wSecond = phptime->tm_sec;

            SystemTimeToVariantTime(&wintime, var_arg->pdate);
         }

         case VT_BSTR|VT_BYREF:
            convert_to_string(pval_arg);
            var_arg->pbstrVal = (BSTR FAR*) emalloc(sizeof(BSTR FAR*));
            unicode_str = php_char_to_OLECHAR(pval_arg->value.str.val, pval_arg->value.str.len, codepage);
            *(var_arg->pbstrVal) = SysAllocString(unicode_str);
            efree(unicode_str);
            break;

         case VT_UNKNOWN|VT_BYREF:
            php_pval_to_variant(pval_arg, var_arg, codepage);
            if(var_arg->vt != VT_DISPATCH)
               var_arg->vt = VT_EMPTY;
            else
            {
               HRESULT hr;

               hr = var_arg->pdispVal->lpVtbl->QueryInterface(var_arg->pdispVal, &IID_IUnknown, &(var_arg->punkVal));

               if (FAILED(hr))
               {
                  php_error(E_WARNING,"can't query IUnknown");
                  var_arg->vt = VT_EMPTY;
               }
               else
                  var_arg->vt = VT_UNKNOWN|VT_BYREF;
            }
            break;

         case VT_DISPATCH|VT_BYREF:
            php_pval_to_variant(pval_arg, var_arg, codepage);
            if(var_arg->vt != VT_DISPATCH)
               var_arg->vt = VT_EMPTY;
            else
               var_arg->vt |= VT_BYREF;
            break;

         case VT_VARIANT|VT_BYREF:
            php_pval_to_variant(pval_arg, var_arg, codepage);
            if(var_arg->vt != (VT_VARIANT | VT_BYREF))
               var_arg->vt = VT_EMPTY;
            break;

         case VT_I1:
            convert_to_long_ex(&pval_arg);
            var_arg->cVal = (char)pval_arg->value.lval;
            break;

         case VT_UI2:
            convert_to_long_ex(&pval_arg);
            var_arg->uiVal = (unsigned short)pval_arg->value.lval;
            break;

         case VT_UI4:
            convert_to_long_ex(&pval_arg);
            var_arg->ulVal = (unsigned long)pval_arg->value.lval;
            break;

         case VT_INT:
            convert_to_long_ex(&pval_arg);
            var_arg->intVal = (int)pval_arg->value.lval;
            break;

         case VT_UINT:
            convert_to_long_ex(&pval_arg);
            var_arg->uintVal = (unsigned int)pval_arg->value.lval;
            break;

         case VT_I1|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->pcVal = (char FAR*) &pval_arg->value.lval;
            break;

         case VT_UI2|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->puiVal = (unsigned short FAR*) &pval_arg->value.lval;
            break;

         case VT_UI4|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->pulVal = (unsigned long FAR*) &pval_arg->value.lval;
            break;

         case VT_INT|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->pintVal = (int FAR*) &pval_arg->value.lval;
            break;

         case VT_UINT|VT_BYREF:
            convert_to_long(pval_arg);
            var_arg->puintVal = (unsigned int FAR*) &pval_arg->value.lval;
            break;

         default:
            php_error(E_WARNING, "Type not supportet or not yet implemented.");
      }
}