void SelectInstVisitor::annotateOneSelectInst(SelectInst &SI) {
  std::vector<uint64_t> &CountFromProfile = UseFunc->getProfileRecord().Counts;
  assert(*CurCtrIdx < CountFromProfile.size() &&
         "Out of bound access of counters");
  uint64_t SCounts[2];
  SCounts[0] = CountFromProfile[*CurCtrIdx]; // True count
  ++(*CurCtrIdx);
  uint64_t TotalCount = UseFunc->getBBInfo(SI.getParent()).CountValue;
  // False Count
  SCounts[1] = (TotalCount > SCounts[0] ? TotalCount - SCounts[0] : 0);
  uint64_t MaxCount = std::max(SCounts[0], SCounts[1]);
  if (MaxCount)
    setProfMetadata(F.getParent(), &SI, SCounts, MaxCount);
}