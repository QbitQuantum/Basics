void FB_TP::executeEvent(int pa_nEIID){
  if(pa_nEIID == scm_nEventREQID){
      if (edgeFlag) {
        if(ET() >= PT()){
          Q() = false;
          edgeFlag = false;
          DEVLOG_DEBUG("top\n");
        }else{
          ET() = TIME() - start;
          DEVLOG_DEBUG("rising\n");
        }
      }
      else {
        if(IN() == true && ET() == 0){
          Q() = true;
          edgeFlag = true;
          start = TIME();
          DEVLOG_DEBUG("start\n");
        }
        else
          if((false == IN()) && (ET()>0)) {
            ET() = 0;
            DEVLOG_DEBUG("reset\n");
          }
      }
      sendOutputEvent(scm_nEventCNFID);
  }
}