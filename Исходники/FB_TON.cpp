void FB_TON::executeEvent(int pa_nEIID){
  if(scm_nEventREQID == pa_nEIID){
    if(IN() == false){
      Q() = false;
      ET() = 0;
      risingEdge = false;
      start = 0;
    }
    else{
      if(risingEdge == false){
        risingEdge = true;
        start = TIME();
      }else{
        count = TIME() - start;
        if(PT() <= count){
          Q() = true;
          ET() = PT();
        }else{
          ET() = count;
        }
      }
    }
    sendOutputEvent(scm_nEventCNFID);
  }
}