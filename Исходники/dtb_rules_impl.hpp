double DTBRules<MetricType, TreeType>::Score(const size_t queryIndex,
                                             TreeType& referenceNode,
                                             const double baseCaseResult)
{
  // I don't really understand the last argument here
  // It just gets passed in the distance call, otherwise this function
  // is the same as the one above.
  size_t queryComponentIndex = connections.Find(queryIndex);

  // If the query belongs to the same component as all of the references,
  // then prune.
  if (queryComponentIndex == referenceNode.Stat().ComponentMembership())
    return DBL_MAX;

  const arma::vec queryPoint = dataSet.unsafe_col(queryIndex);
  const double distance = referenceNode.MinDistance(queryPoint,
                                                    baseCaseResult);

  // If all the points in the reference node are farther than the candidate
  // nearest neighbor for the query's component, we prune.
  return (neighborsDistances[queryComponentIndex] < distance) ? DBL_MAX :
      distance;
}