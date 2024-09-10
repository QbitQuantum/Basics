bool CNoiseReduction::ScanAverage(Spectrum& sp, char* file, int width, float cutoff){
  
  Spectrum ts;
  Spectrum ps=sp;
  MSReader r;
 
  int i;
  int j;
  int k;
  int widthCount=0;
  int numScans=1;
  double dif;
  double prec;
  double dt;
  double c=CParam(ps,3);

  bool bLeft=true;
  int posLeft=ps.getScanNumber()-1;
  int posRight=ps.getScanNumber()+1;
  char cFilter1[256];
  char cFilter2[256];

  ps.getRawFilter(cFilter1,256);

  while(widthCount<(width*2)){

    //Alternate looking left and right
    if(bLeft){
      bLeft=false;
      widthCount++;
      while(posLeft>0){
        r.readFile(file,ts,posLeft);
        if(ts.getScanNumber()==0) break;
        ts.getRawFilter(cFilter2,256);
        if(strcmp(cFilter1,cFilter2)==0) break;
        posLeft--;
      }
    } else {
      bLeft=true;
      widthCount++;
      while(true){
        r.readFile(file,ts,posRight);
        if(ts.getScanNumber()==0) break;
        ts.getRawFilter(cFilter2,256);
        if(strcmp(cFilter1,cFilter2)==0) break;
        posRight++;
      }
    }
    if(ts.getScanNumber()==0) continue;

    numScans++;

    //Match peaks between pivot scan and temp scan
    k=0;
    for(i=0;i<ps.size();i++){
      dif=100000.0;
      prec = c * ps.at(i).mz * ps.at(i).mz / 2;

      for(j=k;j<ts.size();j++){
        dt=fabs(ps.at(i).mz-ts.at(j).mz);
        if(dt<=dif) {
          if(dt<prec) {
            ps.at(i).intensity+=ts.at(j).intensity;
            ts.at(j).mz=-1.0;
            k=j+1;
            break;
          }
          dif=dt;
        } else {
          k=j-1;
          break;
        }
      }
    }

    //Add unmatched peaks from temp scan
    for(i=0;i<ts.size();i++){
      if(ts.at(i).mz>-1.0) ps.add(ts.at(i));
    }

    //Sort pivot scan peaks for fast traversal against next temp scan
    ps.sortMZ();

  }

  //Average points and apply cutoff
  sp.clear();
  for(i=0;i<ps.size();i++) {
    ps.at(i).intensity/=numScans;
    if(ps.at(i).intensity>=cutoff) sp.add(ps.at(i));
  }

  sp.setScanNumber(ps.getScanNumber());
  sp.setScanNumber(ps.getScanNumber(true),true);
  sp.setRTime(ps.getRTime());

  return true;
}