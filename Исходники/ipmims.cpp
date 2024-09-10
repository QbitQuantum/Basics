int ipmi_cmdraw_ms(uchar cmd, uchar netfn, uchar lun, uchar sa,
		uchar bus, uchar *pdata, int sdata, uchar *presp, int *sresp, 
		uchar *pcc, char fdebugcmd)
{
   int bRet;
   HRESULT hres;
   IWbemClassObject* pInParams = NULL; /*class definition*/
   IWbemClassObject* pInReq = NULL;    /*instance*/
   IWbemClassObject* pOutResp = NULL;
   VARIANT varCmd, varNetfn, varLun, varSa, varSize, varData;
   SAFEARRAY* psa = NULL;
   long i;
   uchar *p;

   fdebugms = fdebugcmd;
   if (!fmsopen) {
      bRet = ipmi_open_ms(fdebugcmd);
      if (bRet != 0) return(bRet);
   }
   bRet = -1;


   hres = pClass->GetMethod(L"RequestResponse",0,&pInParams,NULL);
   if (FAILED(hres)) {
        if (fdebugcmd) 
	     printf("ipmi_cmdraw_ms: Cannot get RequestResponse method\n");
        return (bRet);
   }

#ifdef WDM_FIXED
   /* see http://support.microsoft.com/kb/951242 for WDM bug info */
   hres = pInParams->SpawnInstance(0,&pInReq);
   if (FAILED(hres)) {
        if (fdebugcmd) 
	     printf("ipmi_cmdraw_ms: Cannot get RequestResponse instance\n");
        return (bRet);
   }
   // also substitute pInReq for pInParams below if this gets fixed.
#endif

   VariantInit(&varCmd);
   varCmd.vt = VT_UI1;
   varCmd.bVal = cmd;
   hres = pInParams->Put(_bstr_t(L"Command"), 0, &varCmd, 0);
   // VariantClear(&varCmd);
   if (FAILED(hres)) goto MSRET;

   VariantInit(&varNetfn);
   varNetfn.vt = VT_UI1;
   varNetfn.bVal = netfn;
   hres = pInParams->Put(_bstr_t(L"NetworkFunction"), 0, &varNetfn, 0);
   // VariantClear(&varNetfn);
   if (FAILED(hres)) goto MSRET;

   VariantInit(&varLun);
   varLun.vt = VT_UI1;
   varLun.bVal = lun;
   hres = pInParams->Put(_bstr_t(L"Lun"), 0, &varLun, 0);
   // VariantClear(&varLun);
   if (FAILED(hres)) goto MSRET;

   VariantInit(&varSa);
   varSa.vt = VT_UI1;
   varSa.bVal = sa;
   hres = pInParams->Put(_bstr_t(L"ResponderAddress"), 0, &varSa, 0);
   // VariantClear(&varSa);
   if (FAILED(hres)) goto MSRET;

   VariantInit(&varSize);
   varSize.vt = VT_I4;
   varSize.lVal = sdata;
   hres = pInParams->Put(_bstr_t(L"RequestDataSize"), 0, &varSize, 0);
   // VariantClear(&varSize);
   if (FAILED(hres)) goto MSRET;

   SAFEARRAYBOUND rgsabound[1];
   rgsabound[0].cElements = sdata;
   rgsabound[0].lLbound = 0;
   psa = SafeArrayCreate(VT_UI1,1,rgsabound);
   if(!psa) {
      printf("ipmi_cmdraw_ms: SafeArrayCreate failed\n");
      goto MSRET;
   }
#ifdef SHOULD_WORK_BUT_NO
   /* The SafeArrayPutElement does not put the data in the right 
    * place, so skip this and copy the raw data below. */
   VARIANT tvar;
   if (fdebugcmd && sdata > 0) 
	{ printf("psa1(%p):",psa); dumpbuf((uchar *)psa,42,1); }   

   for(i =0; i< sdata; i++)
   {
      VariantInit(&tvar);
      tvar.vt = VT_UI1;
      tvar.bVal = pdata[i];
      hres = SafeArrayPutElement(psa, &i, &tvar);
      // VariantClear(&tvar);
      if (FAILED(hres)) { 
         printf("ipmi_cmdraw_ms: SafeArrayPutElement(%d) failed\n",i);
         goto MSRET;
      }
   } /*end for*/
   if (fdebugcmd && sdata > 0) 
	{ printf("psa2(%p):",psa); dumpbuf((uchar *)psa,42,1); }  
#endif

   /* Copy the real RequestData into psa */
   memcpy(psa->pvData,pdata,sdata);

   VariantInit(&varData);
   varData.vt = VT_ARRAY | VT_UI1;
   varData.parray = psa;
   hres = pInParams->Put(_bstr_t(L"RequestData"), 0, &varData, 0);
   // VariantClear(&varData);
   if (FAILED(hres)) {
	printf("Put(RequestData) error %x\n",hres);
        goto MSRET;
   }

#ifdef TEST_METHODS
   IWbemClassObject* pOutSms = NULL;
   if (fdebugcmd) printf("ipmi_cmdraw_ms: calling SMS_Attention(%ls)\n",
			  V_BSTR(&varPath)); 
   hres = pSvc->ExecMethod( V_BSTR(&varPath), _bstr_t(L"SMS_Attention"), 
				0, NULL, NULL, &pOutSms, NULL);
   if (FAILED(hres)) {
	printf("ipmi_cmdraw_ms: SMS_Attention method error %x\n",hres);
        goto MSRET;
   }
   if (fdebugcmd) printf("ipmi_cmdraw_ms: SMS_Attention method ok\n"); 
   /* This does work, without input parameters */
   pOutSms->Release();
#endif

   hres = pSvc->ExecMethod( V_BSTR(&varPath), _bstr_t(L"RequestResponse"), 
				0, NULL, pInParams, &pOutResp, NULL);
   if (fdebugcmd) {
       printf("ipmi_cmdraw_ms(cmd=%x,netfn=%x,lun=%x,sa=%x,sdata=%d)"
	      " RequestResponse ret=%x\n", cmd,netfn,lun,sa,sdata,hres); 
       if (sdata > 0) {
	   printf("ipmi_cmdraw_ms: req data(%d):",sdata); 
	   dumpbuf(pdata,sdata,0); 
       }
   }
   if (FAILED(hres)) {
	printf("ipmi_cmdraw_ms: RequestResponse error %x %s\n",
		hres,res_str(hres));
#ifdef EXTRA_DESC
	/* This does not usually add any meaning for IPMI. */
	BSTR desc;
	IErrorInfo *pIErrorInfo;
	GetErrorInfo(0,&pIErrorInfo);
	pIErrorInfo->GetDescription(&desc);
	printf("ipmi_cmdraw_ms: ErrorInfoDescr: %ls\n",desc);
	SysFreeString(desc);
#endif
	bRet = -1; 
	/*fall through for cleanup and return*/
   }
   else {  /*successful, get ccode and response data */
	VARIANT varByte, varRSz, varRData;
        VariantInit(&varByte);
        VariantInit(&varRSz);
        VariantInit(&varRData);
	long rlen;

	hres = pOutResp->Get(_bstr_t(L"CompletionCode"),0, &varByte, NULL, 0);
	if (FAILED(hres)) goto MSRET;
	if (fdebugcmd) printf("ipmi_cmdraw_ms: CompletionCode %x returned\n",
				V_UI1(&varByte) );
	*pcc = V_UI1(&varByte);

	hres = pOutResp->Get(_bstr_t(L"ResponseDataSize"),0, &varRSz, NULL, 0);
	if (FAILED(hres)) goto MSRET;
        rlen = V_I4(&varRSz);
	if (rlen > 1) rlen--;   /*skip cc*/
	if (rlen > *sresp) {
	   if (fdebugcmd) printf("ResponseData truncated from %d to %d\n",
					rlen,*sresp);
	   rlen = *sresp; /*truncate*/
	}
	*sresp = (int)rlen;

	hres = pOutResp->Get(_bstr_t(L"ResponseData"),0, &varRData, NULL,0);
	if (FAILED(hres)) { /*ignore failure */ 
	   if (fdebugcmd) printf("Get ResponseData error %x\n",hres); 
	} else {  /* success */
#ifdef SHOULD_WORK_BUT_NO
	    uchar *pa;
	    p = (uchar*)varRData.parray->pvData;
	    pa = (uchar*)varRData.parray;
	    printf("pa=%p, pa+12=%p p=%p\n",pa,(pa+12),p);
	    if (fdebugcmd) {   
		 printf("Data.vt = %04x, Data.parray(%p):",
			varRData.vt, varRData.parray); 
	         // 0x2011 means VT_ARRAY | VT_UI1
		 dumpbuf((uchar *)varRData.parray,40,1);
	    }
	    /* The SafeArrayGetElement does not get the data from the right 
	     * place, so skip this and copy the raw data below. */
	    VARIANT rgvar[NVAR];
	    if (rlen > NVAR) *pcc = 0xEE; 
	    for (i = 0; i <= rlen; i++)
         	VariantInit(&rgvar[i]);
	    /* copy the response data from varRData to presp */
	    for( i = 0; i <= rlen; i++)
	    {
		hres = SafeArrayGetElement(varRData.parray, &i, &rgvar[i]);
		if (FAILED(hres)) { 
		   if (fdebugcmd)
		      printf("ipmi_cmdraw_ms: SafeArrayGetElement(%d) failed\n",i);
		   break;
		}
		if (fdebugcmd) {   
		     printf("Data[%d] vt=%02x val=%02x, rgvar(%p):",i,
				rgvar[i].vt, V_UI1(&rgvar[i]),&rgvar[i]);
		     dumpbuf((uchar *)&rgvar[i],12,0);
		}
	        /* skip the completion code */
	    	// if (i > 0) presp[i-1] = V_UI1(&rgvar[i]);
	    } /*end for*/
#endif
	    /* 
	     * parray from a GetDeviceId response:
	     * 0015CEE0: 01 00 80 00 01 00 00 00 00 00 00 00 00 cf 15 00
	     * 0015CEF0: 10 00 00 00 00 00 00 00 03 00 06 00 95 01 08 00
             *           ^- datalen=0x10
	     * 0015CF00: 00 20 01 00 19 02 9f 57 01 ...  
             *           ^- start of data (cc=00, ...)
	     */
	    /* Copy the real ResponseData into presp. */
	    p = (uchar*)varRData.parray->pvData;
	    for( i = 0; i <= rlen; i++) {
	        /* skip the completion code */
	    	if (i > 0) presp[i-1] = p[i];
	    }
	    if (fdebugcmd) {
		printf("ipmi_cmdraw_ms: resp data(%d):",rlen+1); 
		dumpbuf(p,rlen+1,0); 
	    }
	}
	bRet = 0;
   }

MSRET:
#define CLEAN_OK  1
#ifdef CLEAN_OK
   /* VariantClear(&var*) should be done by pInParams->Release() */
   if (psa != NULL) SafeArrayDestroy(psa);
   if (pInParams != NULL) pInParams->Release();
   if (pOutResp != NULL) pOutResp->Release();
#endif
   return(bRet);
}