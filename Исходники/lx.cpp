bool TLxChDef::IsNmStr(const TStr& Str) const {
  if (Str.Len()==0){return false;}
  if (!IsAlpha(Str.GetCh(0))){return false;}
  for (int ChN=1; ChN<Str.Len(); ChN++){
    if (!IsAlNum(Str.GetCh(ChN))){return false;}}
  return true;
}