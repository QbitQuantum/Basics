  //! Elimina i segmenti che non sono contenuti all'interno dello stroke!!!
  void checkSegments(std::vector<TAutocloser::Segment> &segments,
                     TStroke *stroke, const TRasterCM32P &ras,
                     const TPoint &delta) {
    TVectorImage vi;
    TStroke *app = new TStroke();
    *app         = *stroke;
    app->transform(TTranslation(convert(ras->getCenter())));
    vi.addStroke(app);
    vi.findRegions();
    std::vector<TAutocloser::Segment>::iterator it = segments.begin();
    for (; it < segments.end(); it++) {
      if (it == segments.end()) break;

      int i;
      bool isContained = false;
      for (i = 0; i < (int)vi.getRegionCount(); i++) {
        TRegion *reg = vi.getRegion(i);
        if (reg->contains(convert(it->first + delta)) &&
            reg->contains(convert(it->second + delta))) {
          isContained = true;
          break;
        }
      }
      if (!isContained) {
        it = segments.erase(it);
        if (it != segments.end() && it != segments.begin())
          it--;
        else if (it == segments.end())
          break;
      }
    }
  }