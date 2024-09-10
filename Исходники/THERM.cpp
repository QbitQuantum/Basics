PlotLine * THERM::calculateCustom (QString &p, QPtrList<PlotLine> &d)
{
  // format1: MA_TYPE, MA_PERIOD, THRESHOLD, SMOOTHING_TYPE, SMOOTHING_PERIOD

  if (checkFormat(p, d, 5, 5))
    return 0;

  QStringList mal;
  getMATypes(mal);
  maType = mal.findIndex(formatStringList[0]);
  maPeriod = formatStringList[1].toInt();
  threshold = formatStringList[2].toDouble();
  smoothType = mal.findIndex(formatStringList[3]);
  smoothing = formatStringList[4].toInt();

  QPtrList<PlotLine> pll;
  pll.setAutoDelete(FALSE);
  getTHERM(pll);

  int loop;
  for (loop = pll.count() - 1; loop > 0; loop--)
    pll.remove(loop);

  return pll.at(0);
}