const char *Next(int &kind,int &idx,double &exe,double &heap,double &free,double &inc) {		  
  if(!inp) return 0;
  kind=0;idx=0;exe=0;heap=0;free=0,inc=0;
  TString ts;
  char *endMaker,*clear,*ctr,*doPs,*fr,*to,*and;
  while(fgets(line,500,inp)) {
    doPs = strstr(line,"doPs for");
    if (!doPs) 				continue;
    endMaker = strstr(line,"EndMaker");
    clear    = strstr(line,"Clear");
    ctr      = strstr(line,"constructor");
    kind = 0;
    if (ctr     ) kind = 1;
    if (clear   ) kind = 2;
    if (endMaker) kind = 3;
    if (!kind)				continue;
    fr = doPs+8 +strspn(doPs+8," \t");
    to = strstr(fr,":");
    ts = ""; ts.Append(fr,to-fr);
    if (!ts.Length()) 			continue;
    fr = strstr(fr,"total");  if (!fr) 	continue;
    fr = strstr(fr,"="    );  if (!fr) 	continue;
    exe = atof(fr+1);
    fr  = strstr(fr,"heap" ); if (!fr) 	continue;
    fr  = strstr(fr,"="    ); if (!fr) 	continue;
    heap = atof(fr+1);
    and  = strstr(fr,"and");
    if (and) free = atof(and+3);
    fr  = strstr(fr,"("    ); if (!fr) 	continue;
    inc = atof(fr+1);
    if (kind==1) 			continue;
    TNamed *tn = (TNamed*)hash.FindObject(ts.Data());
    if (!tn) {
      tn = new TNamed(ts.Data(),"");
      hash.Add(tn);
      fNMakers++;
      tn->SetUniqueID((UInt_t)fNMakers);
      mArray.AddAtAndExpand(tn,fNMakers);
    }
    idx = tn->GetUniqueID();
    return tn->GetName();
  }
  fclose(inp); inp = 0;
  return 0;  
}};