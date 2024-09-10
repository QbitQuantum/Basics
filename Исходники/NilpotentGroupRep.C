// returns true iff w lies in the group center
bool NilpotentGroupRep::isCentral(const Word& w) const {

  Word wInv = w.inverse();

  for( int i = 1; i <= theNumberOfGenerators; i++ ) {
    Generator g(i);
    Word comm = w * g * wInv * inv(g);
    if( ! wordProblem(comm) ) 
      return false;
  }
  return true;
}