float ClassAdCollection::GetClassAdRank(ClassAd* Ad, const MyString& RankExpr)
{
  if (RankExpr.Length()==0) return 0.0;
  AttrList RankingAd;
  RankingAd.AssignExpr( ATTR_RANK, RankExpr.Value() );
  float Rank;
  if (!RankingAd.EvalFloat(ATTR_RANK,Ad,Rank)) Rank=0.0;
  return Rank;
}