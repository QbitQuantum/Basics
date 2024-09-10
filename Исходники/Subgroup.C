Bool SubgroupRep::redundantRelator(const Word& u) {
  if ( relators.contains(u) ) return 1;
  Word v = u;
  for( int i = u.length() - 1; i; i--) {
	 v = v.cyclicallyPermute(1);
    if ( relators.contains(v) ) return TRUE;
  }

  v = u.inverse();
  if ( relators.contains(v) ) return 1;
  for( int i = u.length() - 1; i; i--) {
	 v = v.cyclicallyPermute(1);
    if ( relators.contains(v) ) return TRUE;
  }

  relators |= u;
  return FALSE;
}