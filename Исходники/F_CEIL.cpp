void FORTE_F_CEIL::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventREQID:
      OUT() = CEIL(X());
      sendOutputEvent(scm_nEventCNFID);
      break;
  }
}