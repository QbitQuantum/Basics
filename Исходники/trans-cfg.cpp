/**
 * This function tries to infer the weight of any arc in the arcVec given the
 * weights of other arcs in the list and totalWeight, which is the
 * known sum of all their weights.
 * Returns whether or not the weight of any arc was inferred and, in case of
 * success, the weight of such arc is updated.
 */
static bool inferredArcWeight(const TransCFG::ArcPtrVec& arcVec,
                              int64_t totalWeight) {
  int64_t arcWeight = totalWeight;
  TransCFG::Arc* unknownArc = nullptr;
  for (auto arc : arcVec) {
    if (arc->weight() == TransCFG::Arc::kUnknownWeight) {
      if (unknownArc != nullptr) {
        // More than one arc with unknown weight, so can't infer
        return false;
      }
      unknownArc = arc;
    } else {
      arcWeight -= arc->weight();
    }
  }
  if (unknownArc == nullptr) return false;
  // Avoid creating negative-weight arcs. Node weights are not required to be
  // accurate and, since arc weights are derived from nodes' weights, they
  // aren't accurate either.  This can result in arcWeight to be negative here.
  if (arcWeight < 0) arcWeight = 0;
  unknownArc->setWeight(arcWeight);
  return true;
}