 void IrreversibleUnimolecularReaction::calcFluxFirstNonZeroIdx(void) {
   double thresh = get_ThresholdEnergy();
   if(thresh<0.0){m_GrnFluxFirstNonZeroIdx = int(-thresh/getEnv().GrainSize);}
   else{m_GrnFluxFirstNonZeroIdx = 0;}
 }