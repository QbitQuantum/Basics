STDMETHODIMP LightOPCGroup::Write(DWORD dwCount,
                                  OPCHANDLE  *phServer,
                                  VARIANT *pItemValues,
                                  HRESULT **ppErrors)
{
 HRESULT hr = S_OK;
 HRESULT *err = 0;
 unsigned items_ok = 0;
 loRequest *rq;

 LO_CHECK_STATEz1("SyncIO:Write", ppErrors);
 UL_TRACE((LOG_GRH("SyncIO:Write(%u)..."), dwCount));

 if (!phServer || !pItemValues || !dwCount)
   { hr = E_INVALIDARG; goto Return; }

 err = (HRESULT*)loComAlloc(dwCount * sizeof(HRESULT));
 rq = lo_req_alloc(dwCount, loUPL_variant /*| loUPL_errors*/ | loUPL_tagpair);
 if (!rq || !err) { hr = E_OUTOFMEMORY; goto Return; }
 rq->operation = loRQ_OP_WRITE | loRQ_SYNC | loRQ_DEVICE;
 rq->group_key = ServerHandle;
 rq->serv_key = owner->serv_key;
 rq->com_allocated = rq->upl.errors = err;
 loTagPair_init(rq->upl.tagpair, dwCount);
 rq->upl.rctx = owner->ctxt;

 lock_read();
 rq->upl.rctx.cta.vc_lcid = grLCID;

 if (owner->access_mode & loAM_RDONLY_OP)
   {
    unsigned ii;
    for(ii = 0; ii < dwCount; ii++) err[ii] = OPC_E_BADRIGHTS;
   }
 else
   {
    loService *se = owner->se;
    loTagEntry *tags = se->tags;
    loTagPair *tpl = rq->upl.tagpair;
//    HRESULT *errors = rq->upl.errors;
    VARIANT *variant = rq->upl.variant;
    LightOPCItem *it;
    unsigned ii;

    for(ii = 0; ii < dwCount; ii++, tpl++, pItemValues++)
      if (!(it = by_index(phServer[ii]))) err[ii] = OPC_E_INVALIDHANDLE;
      else
        {
         loTagEntry *te = &tags[it->tid];

#if 0 != LO_CHECK_RIGHTS
         if (!(OPC_WRITEABLE & te->attr.taRights)) err[ii] = OPC_E_BADRIGHTS;
         else
#endif
              if (VT_EMPTY == V_VT(pItemValues) ||/*) *errors = OPC_E_BADTYPE;
         else if (*/ S_OK == (err[ii] =
                       VariantCopy(&variant[ii], pItemValues)))
           {
            err[ii] = S_OK;
            tpl->tpTi = te->attr.taTi;
            tpl->tpRt = te->attr.taRt;
            tpl->tpAP = it->AcPath;
            items_ok++;
           }
         else UL_TRACE((LOG_GRH("SyncIO:Write(%u) [ %x / %x ] %s"),
               ii, V_VT(pItemValues), taVTYPE(&te->attr), loStrError(err[ii])));
       }
    rq->upl.used = dwCount;
   }
 unlock();
// rq->upl.used = dwCount;

 if (0 == items_ok)
   {
//    memcpy(err, rq->upl.errors, dwCount * sizeof(*err));
    rq->com_allocated = 0;
    lo_req_free(rq);
    hr = S_FALSE;
   }
 else
   {
    rq->upl.master_err = items_ok == dwCount? S_OK: S_FALSE;
    err = 0;
    if (rq = lo_req_put_sync(&owner->q_req, &owner->q_ret, rq))
      {
       hr = rq->upl.master_err;
//       memcpy(err, rq->upl.errors, dwCount * sizeof(*err));
       err = rq->upl.errors;
       rq->com_allocated = 0;
       lo_req_free(rq);
      }
    else hr = LO_E_SHUTDOWN;
   }

Return:
  if (SUCCEEDED(hr))
   {
    if (ppErrors) *ppErrors = err, err = 0;
//    if (items_ok != dwCount && hr == S_OK) hr = S_FALSE;
    UL_NOTICE((LOG_GRH("SyncIO:Write(%u) = %u Ok"), dwCount, items_ok));
   }
 else
   {
    UL_INFO((LOG_GRH("SyncIO:Write(%u) = %u /%s"),
               dwCount, items_ok, loStrError(hr)));
   }
 if (err) loComFree(err);
 LO_FINISH();
 return hr;
}