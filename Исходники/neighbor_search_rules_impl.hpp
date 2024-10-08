inline double NeighborSearchRules<SortPolicy, MetricType, TreeType>::
    CalculateBound(TreeType& queryNode) const
{
  // We have five possible bounds, and we must take the best of them all.  We
  // don't use min/max here, but instead "best/worst", because this is general
  // to the nearest-neighbors/furthest-neighbors cases.  For nearest neighbors,
  // min = best, max = worst.
  //
  // (1) worst ( worst_{all points p in queryNode} D_p[k],
  //             worst_{all children c in queryNode} B(c) );
  // (2) best_{all points p in queryNode} D_p[k] + worst child distance +
  //        worst descendant distance;
  // (3) best_{all children c in queryNode} B(c) +
  //      2 ( worst descendant distance of queryNode -
  //          worst descendant distance of c );
  // (4) B_1(parent of queryNode)
  // (5) B_2(parent of queryNode);
  //
  // D_p[k] is the current k'th candidate distance for point p.
  // So we will loop over the points in queryNode and the children in queryNode
  // to calculate all five of these quantities.

  // Hm, can we populate our distances vector with estimates from the parent?
  // This is written specifically for the cover tree and assumes only one point
  // in a node.
//  if (queryNode.Parent() != NULL && queryNode.NumPoints() > 0)
//  {
//    size_t parentIndexStart = 0;
//    for (size_t i = 0; i < neighbors.n_rows; ++i)
//    {
//      const double pointDistance = distances(i, queryNode.Point(0));
//      if (pointDistance == DBL_MAX)
//      {
//      // Cool, can we take an estimate from the parent?
//        const double parentWorstBound = distances(distances.n_rows - 1,
//              queryNode.Parent()->Point(0));
//        if (parentWorstBound != DBL_MAX)
//        {
//          const double parentAdjustedDistance = parentWorstBound +
//              queryNode.ParentDistance();
//          distances(i, queryNode.Point(0)) = parentAdjustedDistance;
//        }
//      }
//    }
//  }

  double worstPointDistance = SortPolicy::BestDistance();
  double bestPointDistance = SortPolicy::WorstDistance();

  // Loop over all points in this node to find the best and worst distance
  // candidates (for (1) and (2)).
  for (size_t i = 0; i < queryNode.NumPoints(); ++i)
  {
    const double distance = distances(distances.n_rows - 1,
        queryNode.Point(i));
    if (SortPolicy::IsBetter(distance, bestPointDistance))
      bestPointDistance = distance;
    if (SortPolicy::IsBetter(worstPointDistance, distance))
      worstPointDistance = distance;
  }

  // Loop over all the children in this node to find the worst bound (for (1))
  // and the best bound with the correcting factor for descendant distances (for
  // (3)).
  double worstChildBound = SortPolicy::BestDistance();
  double bestAdjustedChildBound = SortPolicy::WorstDistance();
  const double queryMaxDescendantDistance =
      queryNode.FurthestDescendantDistance();

  for (size_t i = 0; i < queryNode.NumChildren(); ++i)
  {
    const double firstBound = queryNode.Child(i).Stat().FirstBound();
    const double secondBound = queryNode.Child(i).Stat().SecondBound();
    const double childMaxDescendantDistance =
        queryNode.Child(i).FurthestDescendantDistance();

    if (SortPolicy::IsBetter(worstChildBound, firstBound))
      worstChildBound = firstBound;

    // Now calculate adjustment for maximum descendant distances.
    const double adjustedBound = SortPolicy::CombineWorst(secondBound,
        2 * (queryMaxDescendantDistance - childMaxDescendantDistance));
    if (SortPolicy::IsBetter(adjustedBound, bestAdjustedChildBound))
      bestAdjustedChildBound = adjustedBound;
  }

  // This is bound (1).
  const double firstBound =
      (SortPolicy::IsBetter(worstPointDistance, worstChildBound)) ?
      worstChildBound : worstPointDistance;

  // This is bound (2).
  const double secondBound = SortPolicy::CombineWorst(
      SortPolicy::CombineWorst(bestPointDistance, queryMaxDescendantDistance),
      queryNode.FurthestPointDistance());

  // Bound (3) is bestAdjustedChildBound.

  // Bounds (4) and (5) are the parent bounds.
  const double fourthBound = (queryNode.Parent() != NULL) ?
      queryNode.Parent()->Stat().FirstBound() : SortPolicy::WorstDistance();
//  const double fifthBound = (queryNode.Parent() != NULL) ?
//      queryNode.Parent()->Stat().SecondBound() -
//      queryNode.Parent()->FurthestDescendantDistance() -
//      queryNode.Parent()->FurthestPointDistance() + queryMaxDescendantDistance +
//      queryNode.FurthestPointDistance() + queryNode.ParentDistance() :
//      SortPolicy::WorstDistance();

  // Now, we will take the best of these.  Unfortunately due to the way
  // IsBetter() is defined, this sort of has to be a little ugly.
  // The variable interA represents the first bound (B_1), which is the worst
  // candidate distance of any descendants of this node.
  // The variable interC represents the second bound (B_2), which is a bound on
  // the worst distance of any descendants of this node assembled using the best
  // descendant candidate distance modified using the furthest descendant
  // distance.
  const double interA = (SortPolicy::IsBetter(firstBound, fourthBound)) ?
      firstBound : fourthBound;
  const double interB =
      (SortPolicy::IsBetter(bestAdjustedChildBound, secondBound)) ?
      bestAdjustedChildBound : secondBound;
//  const double interC = (SortPolicy::IsBetter(interB, fifthBound)) ? interB :
//      fifthBound;

  // Update the first and second bounds of the node.
  queryNode.Stat().FirstBound() = interA;
  queryNode.Stat().SecondBound() = interB;

  // Update the actual bound of the node.
  queryNode.Stat().Bound() = (SortPolicy::IsBetter(interA, interB)) ? interB :
      interB;

  return queryNode.Stat().Bound();
}