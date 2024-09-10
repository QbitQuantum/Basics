bool stroke_autofill_apply(const TVectorImageP &imgToApply, TStroke *stroke,
                           bool selective) {
  if (!imgToApply || !stroke || stroke->getControlPointCount() == 0)
    return false;
  TVectorImage appImg;
  TStroke *appStroke = new TStroke(*stroke);
  appImg.addStroke(appStroke);
  appImg.findRegions();

  if (regionsReference.size() <= 0) return false;

  double pbx, pby;
  double totalArea = 0;
  pbx = pby = 0.0;

  if (!regionsWork.isEmpty()) regionsWork.clear();

  int i, j, index = 0;

  for (i = 0; i < (int)imgToApply->getRegionCount(); i++) {
    TRegion *currentRegion = imgToApply->getRegion(i);
    for (j = 0; j < (int)appImg.getRegionCount(); j++) {
      TRegion *region = appImg.getRegion(j);
      if (contains(region, currentRegion)) {
        scanRegion(currentRegion, index, regionsWork, region->getBBox());
        index++;
        int k, subRegionCount = currentRegion->getSubregionCount();
        for (k = 0; k < subRegionCount; k++) {
          TRegion *subRegion = currentRegion->getSubregion(k);
          if (contains(region, subRegion))
            scanSubRegion(subRegion, index, regionsWork, region->getBBox());
        }
      }
    }
  }

  if (regionsWork.size() <= 0) return false;

  QMap<int, Region>::Iterator it;
  for (it = regionsWork.begin(); it != regionsWork.end(); it++) {
    pbx += it.value().m_barycentre.x;
    pby += it.value().m_barycentre.y;
    totalArea += it.value().m_area;
  }

  workB = TPointD(pbx / totalArea, pby / totalArea);

  std::vector<MatchingProbs> probVector;

  RegionDataList::Iterator refIt, workIt;
  for (refIt = regionsReference.begin(); refIt != regionsReference.end();
       refIt++)
    for (workIt = regionsWork.begin(); workIt != regionsWork.end(); workIt++)
      assignProbs(probVector, refIt.value(), workIt.value(), refIt.key(),
                  workIt.key());

  bool filledRegions = false;
  for (refIt = regionsReference.begin(); refIt != regionsReference.end();
       refIt++) {
    int to = 0, from = 0;
    int valore = 0;
    do
      valore = match(probVector, from, to);
    while ((regionsWork[to].m_match != -1 ||
            regionsReference[from].m_match != -1) &&
           valore > 0);
    if (valore > AMB_TRESH) {
      regionsWork[to].m_match        = from;
      regionsReference[from].m_match = to;
      regionsWork[to].m_styleId      = regionsReference[from].m_styleId;
      TRegion *reg                   = regionsWork[to].m_region;
      if (reg && (!selective || selective && reg->getStyle() == 0)) {
        reg->setStyle(regionsWork[to].m_styleId);
        filledRegions = true;
      }
    }
  }
  return filledRegions;
}