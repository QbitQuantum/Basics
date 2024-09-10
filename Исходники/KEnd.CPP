  StrCpy(sys_temp_filename,"HOME/Temp.TXT.Z");
  MemSet(&sys_put_key_root,0,sizeof(CKeyDev));
  QueInit(&sys_put_key_root);
  KeyDevAdd(&AKDInputFilterPutKey,&AKDInputFilterPutS,0x40000000,FALSE);
  KeyDevAdd(&AKDRawDisplayPutKey,&AKDRawDisplayPutS,0x60000000,FALSE);
  #exe {
    if (*kernel_cfg->acct_name)
      StreamPrintF("sys_acct=StrNew(\"%C:/TempleOS/Accts/%s\");",kernel_cfg->sys_acct_drv,kernel_cfg->acct_name);
    else
      StreamPrintF("sys_acct=StrNew(\"%C:/TempleOS/Accts\");",kernel_cfg->sys_acct_drv);
    StreamPutS("#exe{OptOff(OPTf_WARN_PAREN);}");
    StreamPrintF("DskCacheInit(%s);",kernel_cfg->dsk_cache_size_exp);
    StreamPutS("#exe{OptOn(OPTf_WARN_PAREN);}");
  };
  pow10_I64=CAlloc(sizeof(F64)*(308+308+1));
  for (i=-308;i<309;i++)
    pow10_I64[i+309]=Pow10(i);

  QueInit(&snd_record_root);
  snd_record_root.freq=0;
  snd_record_root.time_stamp=tT;

//$AN,"Independent Heap Ctrl Example","Independent Heap Ctrl Example"$
  i=1; //Rqst 1 blk, we might get more.
  m=MemBlksUncachedAlloc(&i,sys_code_bp);
  sys_uncached_heap=HeapCtrlIndependentInit(m,i*0x200000/0x200);
  ProgressBarsRst;
  date_fmt_map=MAlloc(DF_NUM);
  time_fmt_map=MAlloc(TF_NUM);
  DateTimeFmtMapsRst;