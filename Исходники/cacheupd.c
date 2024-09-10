loTrid loCacheUpdate(loService *se, unsigned count, loTagValue taglist[], FILETIME *timestamp)
{
 unsigned ii;
 loTagValue *ts;
#if 0 != LO_FILL_TIMESTAMP
 FILETIME ft;
#endif
// UL_DEBUG((LOGID, "loCacheUpdate(%p %u %p)", se, count, taglist));
 if (!loSERVICE_OK(se)) return 0;//EBADF; /*ERROR:EARG*/
 if (!timestamp && (0 >= count || !taglist)) return 0;
#if 0 != LO_FILL_TIMESTAMP
#if 1 == LO_FILL_TIMESTAMP
 se->driver.ldCurrentTime(&se->cactx, &ft);
#else
 if (timestamp) ft = *timestamp;
 else memset(&ft, 0, sizeof(ft));
#endif
#endif

 if (!(ts = loCacheLock(se)))
   {
    UL_INFO((LOGID, "loCacheUpdate() lock failed"));
    return 0;//-1; /*ERROR:out-of-service*/
   }

 for(ii = 0; ii < count; ii++, taglist++)
   {
    loTagId ti;

    if (0 == (ti = taglist->tvTi)) continue;
    else if (ti < 1 || ti > se->lastused/*tag_count*/)
      {
       /*rv = -1;*//*ERROR:BAD ti*/
       UL_INFO((LOGID, "loCacheUpdate(BAD ti:%u)", ii));
       continue;
      }
    else
      {
       HRESULT hr;
       loTagValue *tv = &ts[ti];
       tv->tvState = taglist->tvState;
#if 0 != LO_FILL_TIMESTAMP
       if (!IsFILETIME(tv->tvState.tsTime)) tv->tvState.tsTime = ft;
#endif
/*     hr = (V_ISBYREF(&taglist->tvValue)?
                       VariantCopyInd(&tv->tvValue, &taglist->tvValue):
                       VariantCopy(&tv->tvValue, &taglist->tvValue)); */
       hr = VariantCopy(&tv->tvValue, &taglist->tvValue);
       if (S_OK != hr)
         {
          LO_E_BADTYPE_QUAL(hr, tv->tvState.tsError,
                            tv->tvState.tsQuality);
          /*rv = -1;*//*ERROR:BAD VALUE*/
          UL_WARNING((LOGID, "%!l loCacheUpdate(VariantCopy())", hr));
         }
       tv->tvTi = ti;
      }
   }
 return loCacheUnlock(se, timestamp);
/* return rv; */
}