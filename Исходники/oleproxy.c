static HRESULT WINAPI RemUnkStub_Invoke(LPRPCSTUBBUFFER iface,
				     PRPCOLEMESSAGE pMsg,
				     LPRPCCHANNELBUFFER pChannel)
{
  RemUnkStub *This = (RemUnkStub *)iface;
  ULONG iMethod = pMsg->iMethod;
  LPBYTE buf = pMsg->Buffer;
  HRESULT hr = RPC_E_INVALIDMETHOD;

  TRACE("(%p)->Invoke(%p,%p) method %ld\n", This, pMsg, pChannel, iMethod);
  switch (iMethod)
  {
  case 3: /* RemQueryInterface */
  {
    IPID ipid;
    ULONG cRefs;
    USHORT cIids;
    IID *iids;
    REMQIRESULT *pQIResults = NULL;

    /* in */
    memcpy(&ipid, buf, sizeof(ipid));
    buf += sizeof(ipid);
    memcpy(&cRefs, buf, sizeof(cRefs));
    buf += sizeof(cRefs);
    memcpy(&cIids, buf, sizeof(cIids));
    buf += sizeof(cIids);
    iids = (IID *)buf;

    hr = IRemUnknown_RemQueryInterface(This->iface, &ipid, cRefs, cIids, iids, &pQIResults);

    /* out */
    pMsg->cbBuffer = cIids * sizeof(REMQIRESULT) + sizeof(HRESULT);

    I_RpcGetBuffer((RPC_MESSAGE *)pMsg);

    buf = pMsg->Buffer;
    *(HRESULT *)buf = hr;
    buf += sizeof(HRESULT);
    
    if (hr) return hr;
    /* FIXME: pQIResults is a unique pointer so pQIResults can be NULL! */
    memcpy(buf, pQIResults, cIids * sizeof(REMQIRESULT));

    break;
  }
  case 4: /* RemAddRef */
  {
    USHORT cIids;
    REMINTERFACEREF *ir;
    HRESULT *pResults;

    /* in */
    memcpy(&cIids, buf, sizeof(USHORT));
    buf += sizeof(USHORT);
    ir = (REMINTERFACEREF*)buf;
    pResults = CoTaskMemAlloc(cIids * sizeof(HRESULT));
    if (!pResults) return E_OUTOFMEMORY;

    hr = IRemUnknown_RemAddRef(This->iface, cIids, ir, pResults);

    /* out */
    pMsg->cbBuffer = cIids * sizeof(HRESULT);

    I_RpcGetBuffer((RPC_MESSAGE *)pMsg);
    if (!hr)
    {
        buf = pMsg->Buffer;
        memcpy(buf, pResults, cIids * sizeof(HRESULT));
    }

    CoTaskMemFree(pResults);

    break;
  }
  case 5: /* RemRelease */
  {
    USHORT cIids;
    REMINTERFACEREF *ir;

    /* in */
    memcpy(&cIids, buf, sizeof(USHORT));
    buf += sizeof(USHORT);
    ir = (REMINTERFACEREF*)buf;

    hr = IRemUnknown_RemRelease(This->iface, cIids, ir);

    /* out */
    pMsg->cbBuffer = 0;
    break;
  }
  }
  return hr;
}