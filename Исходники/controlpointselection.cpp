int ControlPointEditorStroke::addControlPoint(const TPointD &pos) {
  TStroke *stroke = getStroke();
  if (!stroke) return -1;
  double d = 0.01;
  int indexAtPos;
  int cpCount = stroke->getControlPointCount();
  if (cpCount <= 3)  // e' un unico chunk e in questo caso rappresenta un punto
  {
    getPointTypeAt(pos, d, indexAtPos);
    return indexAtPos;
  }

  double w       = stroke->getW(pos);
  int pointIndex = stroke->getControlPointIndexAfterParameter(w);

  int i, index;
  for (i = 0; i < getControlPointCount(); i++) {
    // Cerco il ControlPoint corrispondente all'indice pointIndex. OSS.:
    // Effettuo il
    // controllo da zero a getControlPointCount()-1 per gestire il caso del
    // selfLoop
    if (pointIndex == m_controlPoints[i].m_pointIndex + 1 ||
        pointIndex == m_controlPoints[i].m_pointIndex + 2 ||
        pointIndex == m_controlPoints[i].m_pointIndex + 3 ||
        pointIndex == m_controlPoints[i].m_pointIndex + 4)
      index = i;
  }

  ControlPoint precCp = m_controlPoints[index];
  assert(precCp.m_pointIndex >= 0);
  std::vector<TThickPoint> points;

  for (i = 0; i < cpCount; i++) {
    if (i != precCp.m_pointIndex + 1 && i != precCp.m_pointIndex + 2 &&
        i != precCp.m_pointIndex + 3)
      points.push_back(stroke->getControlPoint(i));
    if (i == precCp.m_pointIndex + 2) {
      bool isBeforePointLinear = isSpeedOutLinear(index);
      int nextIndex =
          (isSelfLoop() && index == m_controlPoints.size() - 1) ? 0 : index + 1;
      bool isNextPointLinear =
          nextIndex < (int)m_controlPoints.size() && isSpeedInLinear(nextIndex);

      TThickPoint a0 = stroke->getControlPoint(precCp.m_pointIndex);
      TThickPoint a1 = stroke->getControlPoint(precCp.m_pointIndex + 1);
      TThickPoint a2 = stroke->getControlPoint(precCp.m_pointIndex + 2);
      TThickPoint a3 = stroke->getControlPoint(precCp.m_pointIndex + 3);
      TThickPoint a4 = stroke->getControlPoint(precCp.m_pointIndex + 4);
      double dist2   = tdistance2(pos, TPointD(a2));
      TThickPoint d0, d1, d2, d3, d4, d5, d6;

      if (isBeforePointLinear && isNextPointLinear) {
        // Se sono entrambi i punti lineari  inserisco un punto lineare
        d0 = a1;
        d3 = stroke->getThickPoint(w);
        d6 = a3;
        d2 = computeLinearPoint(d0, d3, 0.01, true);   // SpeedIn
        d4 = computeLinearPoint(d3, d6, 0.01, false);  // SpeedOut
        d1 = 0.5 * (d0 + d2);
        d5 = 0.5 * (d4 + d6);
      } else if (dist2 < 32) {
        // Sono molto vicino al punto che non viene visualizzato
        TThickPoint b0 = 0.5 * (a0 + a1);
        TThickPoint b1 = 0.5 * (a2 + a1);
        TThickPoint c0 = 0.5 * (b0 + b1);

        TThickPoint b2 = 0.5 * (a2 + a3);
        TThickPoint b3 = 0.5 * (a3 + a4);

        TThickPoint c1 = 0.5 * (b2 + b3);
        d0             = b0;
        d1             = c0;
        d2             = b1;
        d3             = a2;
        d4             = b2;
        d5             = c1;
        d6             = b3;
      } else {
        bool isInFirstChunk = true;
        if (pointIndex > precCp.m_pointIndex + 2) {
          // nel caso in cui sono nel secondo chunk scambio i punti
          a0 = a4;
          std::swap(a1, a3);
          isInFirstChunk = false;
        }

        double w0 = (isSelfLoop() && precCp.m_pointIndex + 4 == cpCount - 1 &&
                     !isInFirstChunk)
                        ? 1
                        : stroke->getW(a0);
        double w1 = stroke->getW(a2);
        double t  = (w - w0) / (w1 - w0);

        TThickPoint p  = stroke->getThickPoint(w);
        TThickPoint b0 = TThickPoint((1 - t) * a0 + t * a1,
                                     (1 - t) * a0.thick + t * a1.thick);
        TThickPoint b1 = TThickPoint((1 - t) * a1 + t * a2,
                                     (1 - t) * a1.thick + t * a2.thick);
        TThickPoint c0 =
            TThickPoint(0.5 * a0 + 0.5 * b0, (1 - t) * a0.thick + t * b0.thick);
        TThickPoint c1 =
            TThickPoint(0.5 * b0 + 0.5 * p, (1 - t) * b0.thick + t * p.thick);
        TThickPoint c2 =
            TThickPoint(0.5 * c0 + 0.5 * c1, (1 - t) * c0.thick + t * c1.thick);

        d0 = (isInFirstChunk) ? c0 : a3;
        d1 = (isInFirstChunk) ? c2 : a2;
        d2 = (isInFirstChunk) ? c1 : b1;
        d3 = p;
        d4 = (isInFirstChunk) ? b1 : c1;
        d5 = (isInFirstChunk) ? a2 : c2;
        d6 = (isInFirstChunk) ? a3 : c0;
      }
      if (isBeforePointLinear && !isNextPointLinear)
        d1 = computeLinearPoint(d0, d2, 0.01, false);
      else if (isNextPointLinear && !isBeforePointLinear)
        d5 = computeLinearPoint(d4, d6, 0.01, true);
      points.push_back(d0);
      points.push_back(d1);
      points.push_back(d2);
      points.push_back(d3);
      points.push_back(d4);
      points.push_back(d5);
      points.push_back(d6);
    }
  }

  stroke->reshape(&points[0], points.size());
  resetControlPoints();

  getPointTypeAt(pos, d, indexAtPos);
  return indexAtPos;
}