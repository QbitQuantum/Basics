void TColorStyle::makeIcon(const TDimension &d) {
  checkErrorsByGL;
  TColorStyle *style = this->clone();
  checkErrorsByGL;

  TPaletteP tmpPalette = new TPalette();
  checkErrorsByGL;
  int id = tmpPalette->addStyle(style);
  checkErrorsByGL;

  int contextLx = pow(2.0, tceil(log((double)d.lx) / log(2.0)));
  int contextLy = pow(2.0, tceil(log((double)d.ly) / log(2.0)));
  TDimension dim(contextLx, contextLy);

  TOfflineGL *glContext = TOfflineGL::getStock(dim);

  checkErrorsByGL;
  glContext->clear(TPixel32::White);
  checkErrorsByGL;

  TVectorImageP img = new TVectorImage;
  checkErrorsByGL;
  img->setPalette(tmpPalette.getPointer());
  checkErrorsByGL;

  std::vector<TThickPoint> points(3);

  if (isRegionStyle() && !isStrokeStyle()) {
    points[0]        = TThickPoint(-55, -50, 1);
    points[1]        = TThickPoint(0, -60, 1);
    points[2]        = TThickPoint(55, -50, 1);
    TStroke *stroke1 = new TStroke(points);

    img->addStroke(stroke1);

    points[0]        = TThickPoint(50, -55, 1);
    points[1]        = TThickPoint(60, 0, 1);
    points[2]        = TThickPoint(50, 55, 1);
    TStroke *stroke2 = new TStroke(points);
    img->addStroke(stroke2);

    points[0]        = TThickPoint(55, 50, 1);
    points[1]        = TThickPoint(0, 60, 1);
    points[2]        = TThickPoint(-55, 50, 1);
    TStroke *stroke3 = new TStroke(points);
    img->addStroke(stroke3);

    points[0]        = TThickPoint(-50, 55, 1);
    points[1]        = TThickPoint(-60, 0, 1);
    points[2]        = TThickPoint(-50, -55, 1);
    TStroke *stroke4 = new TStroke(points);
    img->addStroke(stroke4);

    img->fill(TPointD(0, 0), id);
  } else if (isStrokeStyle() && !isRegionStyle()) {
    double rasX05 = d.lx * 0.5;
    double rasY05 = d.ly * 0.5;

    points[0]        = TThickPoint(-rasX05, -rasY05, 7);
    points[1]        = TThickPoint(0, -rasY05, 9);
    points[2]        = TThickPoint(rasX05, rasY05, 12);
    TStroke *stroke1 = new TStroke(points);

    stroke1->setStyle(id);

    img->addStroke(stroke1);
    points.clear();
  } else if (!isRasterStyle()) {
    assert(isStrokeStyle() && isRegionStyle());

    points[0]        = TThickPoint(-60, -30, 0.5);
    points[1]        = TThickPoint(0, -30, 0.5);
    points[2]        = TThickPoint(60, -30, 0.5);
    TStroke *stroke1 = new TStroke(points);
    stroke1->setStyle(id);
    img->addStroke(stroke1);

    points[0]        = TThickPoint(60, -30, 0.5);
    points[1]        = TThickPoint(60, 0, 0.5);
    points[2]        = TThickPoint(60, 30, 0.5);
    TStroke *stroke2 = new TStroke(points);
    stroke2->setStyle(id);
    img->addStroke(stroke2);

    points[0]        = TThickPoint(60, 30, 0.5);
    points[1]        = TThickPoint(0, 30, 0.5);
    points[2]        = TThickPoint(-60, 30, 0.5);
    TStroke *stroke3 = new TStroke(points);
    stroke3->setStyle(id);
    img->addStroke(stroke3);

    points[0]        = TThickPoint(-60, 30, 0.5);
    points[1]        = TThickPoint(-60, 0, 0.5);
    points[2]        = TThickPoint(-60, -30, 0.5);
    TStroke *stroke4 = new TStroke(points);
    stroke4->setStyle(id);
    img->addStroke(stroke4);

    img->fill(TPointD(0, 0), id);
  }

  TRectD bbox = img->getBBox();
  checkErrorsByGL;

  bbox = bbox.enlarge(TDimensionD(-10, -10));
  checkErrorsByGL;

  double scx = 0.9 * d.lx / bbox.getLx();
  double scy = 0.9 * d.ly / bbox.getLy();
  double sc  = std::min(scx, scy);
  double dx  = (d.lx - bbox.getLx() * sc) * 0.5;
  double dy  = (d.ly - bbox.getLy() * sc) * 0.5;
  TAffine aff =
      TScale(scx, scy) * TTranslation(-bbox.getP00() + TPointD(dx, dy));

  checkErrorsByGL;
  if (isRegionStyle() && !isStrokeStyle()) aff = aff * TTranslation(-10, -10);

  checkErrorsByGL;
  const TVectorRenderData rd(aff, TRect(), tmpPalette.getPointer(), 0, true);
  checkErrorsByGL;
  glContext->draw(img, rd);
  checkErrorsByGL;

  TRect rect(d);
  if (!m_icon || m_icon->getSize() != d) {
    checkErrorsByGL;
    m_icon = glContext->getRaster()->extract(rect)->clone();
  } else {
    checkErrorsByGL;
    m_icon->copy(glContext->getRaster()->extract(rect));
  }
}