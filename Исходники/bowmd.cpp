PBowMd TBowMd::LoadBin(const TStr& FNm, const PBowDocBs& BowDocBs){
  PBowMd BowMd; {TFIn SIn(FNm); BowMd=Load(SIn);}
  if ((!BowDocBs.Empty())&&(BowMd->GetBowDocBsSig()!=BowDocBs->GetSig())){
    TExcept::Throw("Bow-Model and Bow-Data signatures don't match!");}
  return BowMd;
}