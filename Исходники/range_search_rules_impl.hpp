double RangeSearchRules<MetricType, TreeType>::Score(TreeType& queryNode,
                                                     TreeType& referenceNode)
{
  math::Range distances;
  if (tree::TreeTraits<TreeType>::FirstPointIsCentroid)
  {
    // It is possible that the base case has already been calculated.
    double baseCase = 0.0;
    bool alreadyDone = false;
    if (tree::TreeTraits<TreeType>::HasSelfChildren)
    {
      TreeType* lastQuery = (TreeType*) referenceNode.Stat().LastDistanceNode();
      TreeType* lastRef = (TreeType*) queryNode.Stat().LastDistanceNode();

      // Did the query node's last combination do the base case?
      if ((lastRef != NULL) && (referenceNode.Point(0) == lastRef->Point(0)))
      {
        baseCase = queryNode.Stat().LastDistance();
        alreadyDone = true;
      }

      // Did the reference node's last combination do the base case?
      if ((lastQuery != NULL) && (queryNode.Point(0) == lastQuery->Point(0)))
      {
        baseCase = referenceNode.Stat().LastDistance();
        alreadyDone = true;
      }

      // If the query node is a self-child, did the query parent's last
      // combination do the base case?
      if ((queryNode.Parent() != NULL) &&
          (queryNode.Point(0) == queryNode.Parent()->Point(0)))
      {
        TreeType* lastParentRef = (TreeType*)
            queryNode.Parent()->Stat().LastDistanceNode();
        if ((lastParentRef != NULL) &&
            (referenceNode.Point(0) == lastParentRef->Point(0)))
        {
          baseCase = queryNode.Parent()->Stat().LastDistance();
          alreadyDone = true;
        }
      }

      // If the reference node is a self-child, did the reference parent's last
      // combination do the base case?
      if ((referenceNode.Parent() != NULL) &&
          (referenceNode.Point(0) == referenceNode.Parent()->Point(0)))
      {
        TreeType* lastQueryRef = (TreeType*)
            referenceNode.Parent()->Stat().LastDistanceNode();
        if ((lastQueryRef != NULL) &&
            (queryNode.Point(0) == lastQueryRef->Point(0)))
        {
          baseCase = referenceNode.Parent()->Stat().LastDistance();
          alreadyDone = true;
        }
      }
    }

    if (!alreadyDone)
    {
      // We must calculate the base case.
      baseCase = BaseCase(queryNode.Point(0), referenceNode.Point(0));
    }
    else
    {
      // Make sure that if BaseCase() is called, we don't duplicate results.
      lastQueryIndex = queryNode.Point(0);
      lastReferenceIndex = referenceNode.Point(0);
    }

    distances.Lo() = baseCase - queryNode.FurthestDescendantDistance()
        - referenceNode.FurthestDescendantDistance();
    distances.Hi() = baseCase + queryNode.FurthestDescendantDistance()
        + referenceNode.FurthestDescendantDistance();

    // Update the last distances performed for the query and reference node.
    queryNode.Stat().LastDistanceNode() = (void*) &referenceNode;
    queryNode.Stat().LastDistance() = baseCase;
    referenceNode.Stat().LastDistanceNode() = (void*) &queryNode;
    referenceNode.Stat().LastDistance() = baseCase;
  }
  else
  {
    // Just perform the calculation.
    distances = referenceNode.RangeDistance(&queryNode);
  }

  // If the ranges do not overlap, prune this node.
  if (!distances.Contains(range))
    return DBL_MAX;

  // In this case, all of the points in the reference node will be part of all
  // the results for each point in the query node.
  if ((distances.Lo() >= range.Lo()) && (distances.Hi() <= range.Hi()))
  {
    for (size_t i = 0; i < queryNode.NumDescendants(); ++i)
      AddResult(queryNode.Descendant(i), referenceNode);
    return DBL_MAX; // We don't need to go any deeper.
  }

  // Otherwise the score doesn't matter.  Recursion order is irrelevant in range
  // search.
  return 0.0;
}