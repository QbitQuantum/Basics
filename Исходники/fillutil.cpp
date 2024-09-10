void AreaFiller::strokeFill(TStroke *stroke, int colorId, bool onlyUnfilled,
                            bool fillPaints, bool fillInks) {
  stroke->transform(TTranslation(convert(m_ras->getCenter())));
  m_ras->lock();

  std::vector<std::pair<TPoint, int>> seeds;
  computeSeeds(m_ras, stroke, seeds);

  TVectorImage app;
  app.addStroke(stroke);
  app.findRegions();
  for (UINT i = 0; i < app.getRegionCount(); i++)
    fillArea(m_ras, app.getRegion(i), colorId, onlyUnfilled, fillPaints,
             fillInks);
  app.removeStroke(0);

  stroke->transform(TTranslation(convert(-m_ras->getCenter())));
  restoreColors(m_ras, seeds);
  m_ras->unlock();
}