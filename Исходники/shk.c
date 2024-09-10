/* Does this monster follow me downstairs?  (shopkeeper or pet dog) */
Boolean follower(monst_t *mtmp)
{
  UShort mf = mtmp->bitflags;
  return( 
	 (mf & M_IS_TAME) || 
	 StrChr("1TVWZi&, ", mtmp->data->mlet) ||
	 ((mf & M_IS_SHOPKEEPER) && ESHK(mtmp)->following)
	 );
}