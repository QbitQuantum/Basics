SetOf<Word>& unsymmetrise(SetOf<Word>& S)
// @dp provisional implementation, too expensive.
{
  SetOf<Word> SymSet(S);
  SetOf<Word> result;
  
  while( SymSet.cardinality() > 0 ) {
	 	Word w = arbitraryElementOf(SymSet);
	 	Word wInv = w.inverse();
		SymSet -= w;
		SymSet -= wInv;
		// delete all the cyclic permutations of w and wInv from SymSet
	 	for(int i=1; i<w.length(); i++) {
		  SymSet -= w.cyclicallyPermute(i);
		  SymSet -= wInv.cyclicallyPermute(i);
	  	}
		result |= w;
	      }
  S = result;
  return S;
}