void Normalize::getStatsWithOutliers(const DataSet& dataset,
                                     const Region& region,
                                     Point& mminPoint,
                                     Point& mmaxPoint,
                                     Point& meanPoint,
                                     Point& varPoint) const {

  G_DEBUG(GAlgorithms, "getting stats with outliers");

  PointLayout layoutCopy = dataset.layout().copy();

  mminPoint.setLayout(layoutCopy);
  mmaxPoint.setLayout(layoutCopy);
  meanPoint.setLayout(layoutCopy);
  varPoint.setLayout(layoutCopy);

  RealDescriptor& fmin  = mminPoint.frealData();
  RealDescriptor& fmax  = mmaxPoint.frealData();
  RealDescriptor& fmean = meanPoint.frealData();
  RealDescriptor& fvar  = varPoint.frealData();

  int nSegments = dataset.totalSegments();
  QVector<Real> dist(nSegments);

  foreach (const Segment& seg, region.segments) {
    for (int didx=seg.begin; didx<seg.end; didx++) {
      int pidx = 0; // point index in distribution

      for (int i=0; i<dataset.size(); i++) {
        const Point* p = dataset.at(i);
        FORSEG(*p) {
          dist[pidx++] = p->frealData(nseg)[didx];
        }
      }

      Q_ASSERT(pidx == nSegments);

      sort(dist);

      int idxFirst = (int)((      _outliers/2.0) * (nSegments-1));
      int idxLast  = (int)((1.0 - _outliers/2.0) * (nSegments-1));
      int nump = idxLast - idxFirst;
      fmin[didx] = dist[idxFirst];
      fmax[didx] = dist[idxLast];
      fmean[didx] = gaia2::mean(dist.constData() + idxFirst, dist.size() - nump);
      fvar[didx] = gaia2::variance(dist.constData() + idxFirst, dist.size() - nump);
    }
  }

  G_DEBUG(GAlgorithms, "done getting stats with outliers");
}