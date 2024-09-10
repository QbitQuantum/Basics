void FB_TOF::executeEvent(int pa_nEIID){
  if(scm_nEventREQID == pa_nEIID){
    if(IN() == true){
      Q() = true;
      ET() = 0;
      fallingEdge = false;
      notFirstRisingEdge = true;
      start = 0;
    }
    else{
      if(true == notFirstRisingEdge){
        if(fallingEdge == false){
          fallingEdge = true;
          start = TIME();
        }
        else{
          count = TIME() - start;
          if(PT() <= count){
            Q() = false;
            ET() = PT();
          }else{
            ET() = count;
          }
        }
      }
    }
    sendOutputEvent(scm_nEventCNFID);
  }
}