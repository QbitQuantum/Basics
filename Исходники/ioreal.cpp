static void rio_cache_write(loService *se, loUpdList *upl)
{
 HRESULT  *errors = upl->errors;
 VARIANT *variant = upl->variant;
 loTagPair *tpl = upl->tagpair;
 loTagEntry *tags = se->tags;
 unsigned ii, items_fail = 0, items_clamp = 0;
 FILETIME ft;
 VARIANT var; VARIANTINIT(&var);
 loTagValue *ts;
 se->driver.ldCurrentTime(&se->cactx, &ft);

// UL_INFO((LOGID, "rio_cache_write() in %d", upl->master_err));

 if (!(ts = loCacheLock(se))) return;

 for(ii = upl->used; ii--; tpl++, errors++, variant++)
   if (tpl->tpTi)
     {
      loTagValue *tv = &ts[tpl->tpTi];
      VARTYPE cvt = taVTYPE(&tags[tpl->tpTi].attr);
      HRESULT hr;

      if (V_VT(variant) != VT_EMPTY &&
          V_VT(variant) != cvt &&
          S_OK != (hr =
#if 0
              VARIANTCHANGEt(variant, variant, upl->rctx.cta, cvt)
#else
              VariantChangeType(variant, variant, 0, cvt)
#endif
                  ))
        {
         *errors = LO_E_BADTYPE(hr); 
         items_fail = 1;
        }
      else if (tv->tvTi) 
        {
         *errors = OPC_S_CLAMP;
         items_fail = 1;
        }
      else
        {
         VARIANT tvmp;
         tv->tvTi = tpl->tpTi;
         tvmp = tv->tvValue;
         tv->tvValue = *variant;
         *variant = tvmp;
         tv->tvState.tsTime = ft;
         tv->tvState.tsError = *errors = loOPC_S_CLAMP;
         tv->tvState.tsQuality = OPC_QUALITY_LOCAL_OVERRIDE;
         items_clamp = 1;
        }
     }
 loCacheUnlock(se, 0);

 if (items_fail || items_clamp && loOPC_S_CLAMP != S_OK)
   upl->master_err = S_FALSE;
}