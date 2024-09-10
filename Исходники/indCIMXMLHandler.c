CMPIStatus
IndCIMXMLHandlerCreateInstance(CMPIInstanceMI * mi,
                               const CMPIContext *ctx,
                               const CMPIResult *rslt,
                               const CMPIObjectPath * cop,
                               const CMPIInstance *ci)
{
  CMPIStatus      st = { CMPI_RC_OK, NULL };
  CMPIArgs       *in,
                 *out = NULL;
  CMPIObjectPath *op;
  unsigned short  persistenceType;

  _SFCB_ENTER(TRACE_INDPROVIDER, "IndCIMXMLHandlerCreateInstance");

  if (interOpNameSpace(cop, &st) == 0)
    _SFCB_RETURN(st);

  CMPIInstance   *ciLocal = CMClone(ci, NULL);
  memLinkInstance(ciLocal);
  CMPIObjectPath* copLocal = CMClone(cop, NULL);
  memLinkObjectPath(copLocal);

  setCCN(copLocal,ciLocal,"CIM_ComputerSystem");

  internalProviderGetInstance(copLocal, &st);
  if (st.rc == CMPI_RC_ERR_FAILED)
    _SFCB_RETURN(st);
  if (st.rc == CMPI_RC_OK) {
    setStatus(&st, CMPI_RC_ERR_ALREADY_EXISTS, NULL);
    _SFCB_RETURN(st);
  }


  CMPIString *sysname=ciLocal->ft->getProperty(ciLocal,"SystemName",&st).value.string;
  if (sysname == NULL || sysname->hdl == NULL) {
    char hostName[512];
    hostName[0]=0;
    gethostname(hostName,511); /* should be the same as SystemName of IndicationService */
    CMAddKey(copLocal, "SystemName", hostName, CMPI_chars);
    CMSetProperty(ciLocal,"SystemName",hostName,CMPI_chars);
  }


  CMPIString     *dest =
      CMGetProperty(ciLocal, "destination", &st).value.string;
  if (dest == NULL || CMGetCharPtr(dest) == NULL) {
    setStatus(&st, CMPI_RC_ERR_FAILED,
              "Destination property not found; is required");
    CMRelease(ciLocal);
    _SFCB_RETURN(st);
  } else {                      /* if no scheme is given, assume http (as
                                 * req. for param by mof) */
    char           *ds = CMGetCharPtr(dest);
    if (strstr(ds, "://") == NULL) {
      char           *prefix = "http://";
      int             n = strlen(ds) + strlen(prefix) + 1;
      char           *newdest = malloc(n * sizeof(*newdest));
      strcpy(newdest, prefix);
      strcat(newdest, ds);
      CMSetProperty(ciLocal, "destination", newdest, CMPI_chars);
      free(newdest);
    }
  }

  CMPIData        persistence =
      CMGetProperty(ciLocal, "persistencetype", &st);
  if (persistence.state == CMPI_nullValue
      || persistence.state == CMPI_notFound) {
    persistenceType = 2;        /* default is 2 = permanent */
  } else if (persistence.value.uint16 < 1 || persistence.value.uint16 > 3) {
    setStatus(&st, CMPI_RC_ERR_FAILED,
              "PersistenceType property must be 1, 2, or 3");
    CMRelease(ciLocal);
    _SFCB_RETURN(st);
  } else {
    persistenceType = persistence.value.uint16;
  }
  CMSetProperty(ciLocal, "persistencetype", &persistenceType, CMPI_uint16);

  if (CMClassPathIsA(_broker, copLocal, "cim_listenerdestination", NULL)) {

    //get the creation timestamp
    struct timeval  tv;
    struct timezone tz;
    char   context[100];
    gettimeofday(&tv, &tz);
    struct tm cttm;
    char * gtime = malloc(15 * sizeof(*gtime));
    memset(gtime, 0, 15 * sizeof(char));
    if (gmtime_r(&tv.tv_sec, &cttm) != NULL) {
      strftime(gtime, 15, "%Y%m%d%H%M%S", &cttm);
    }

    // Even though reliable indications may be disabled, we need to do this 
    // in case it ever gets enabled.
    // Get the IndicationService name
    CMPIObjectPath * isop = CMNewObjectPath(_broker, "root/interop", "CIM_IndicationService", NULL);
    CMPIEnumeration * isenm = _broker->bft->enumerateInstances(_broker, ctx, isop, NULL, NULL);
    CMPIData isinst = CMGetNext(isenm, NULL);
    CMPIData mc = CMGetProperty(isinst.value.inst, "Name", NULL);

    // build the context string
    sprintf (context,"%s#%s#",mc.value.string->ft->getCharPtr(mc.value.string,NULL),gtime);
    CMPIValue scontext;
    scontext.string = sfcb_native_new_CMPIString(context, NULL, 0);
    free(gtime);

    // set the properties
    CMSetProperty(ciLocal, "SequenceContext", &scontext, CMPI_string);
    CMPIValue zarro = {.sint64 = -1 };
    CMSetProperty(ciLocal, "LastSequenceNumber", &zarro, CMPI_sint64);
  }

  _SFCB_TRACE_VAR(CMPIString *str = CDToString(_broker, copLocal, NULL));
  _SFCB_TRACE_VAR(CMPIString *ns = CMGetNameSpace(copLocal, NULL));
  _SFCB_TRACE(1,("--- handler %s %s", (char *) ns->hdl, (char *) str->hdl));

  in = CMNewArgs(_broker, NULL);
  CMAddArg(in, "handler", &ciLocal, CMPI_instance);
  CMAddArg(in, "key", &copLocal, CMPI_ref);
  op = CMNewObjectPath(_broker, "root/interop",
                       "cim_indicationsubscription", &st);
  CBInvokeMethod(_broker, ctx, op, "_addHandler", in, out, &st);

  if (st.rc == CMPI_RC_OK) {
    st = InternalProviderCreateInstance(NULL, ctx, rslt, copLocal, ciLocal);
  }
  else {
    CBInvokeMethod(_broker,ctx,op,"_removeHandler",in,out,NULL);
  }

  _SFCB_RETURN(st);
}

/*
 * ModifyInstance only for ListenerDestination.Destination
 */
CMPIStatus
IndCIMXMLHandlerModifyInstance(CMPIInstanceMI * mi,
                               const CMPIContext *ctx,
                               const CMPIResult *rslt,
                               const CMPIObjectPath * cop,
                               const CMPIInstance *ci,
                               const char **properties)
{
  CMPIStatus st = { CMPI_RC_OK, NULL };
  CMPIString *cn = CMGetClassName(cop, NULL);
  const char *cns = cn->ft->getCharPtr(cn,NULL);
  CMPIArgs *in;
        
  _SFCB_ENTER(TRACE_INDPROVIDER, "IndCIMXMLHandlerModifyInstance");   
   
  if(isa("root/interop", cns, "cim_listenerdestination")) {
    _SFCB_TRACE(1,("--- modify %s", cns));
                
    CMPIData newDest = CMGetProperty(ci, "Destination", &st);
    fprintf(stderr, "new dest is %s\n", CMGetCharPtr(newDest.value.string));

    if(newDest.state != CMPI_goodValue) {
      st.rc = CMPI_RC_ERR_FAILED;
      return st;        
    }
          
    in=CMNewArgs(_broker,NULL);
    CMAddArg(in,"handler",&ci,CMPI_instance);
    CMAddArg(in,"key",&cop,CMPI_ref);
    /* cn needs to be IndicationSub to route the IM call to interopProv */
    CMPIObjectPath* sop=CMNewObjectPath(_broker,"root/interop","cim_indicationsubscription",&st);
    CBInvokeMethod(_broker,ctx,sop,"_updateHandler",in,NULL,&st);

    if (st.rc==CMPI_RC_OK) {
      st=InternalProviderModifyInstance(NULL,ctx,rslt,cop,ci,properties);
    }
    else {
      CBInvokeMethod(_broker,ctx,sop,"_removeHandler",in,NULL,NULL);
    }

  }

  _SFCB_RETURN(st);
}