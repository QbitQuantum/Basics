bool BuildingPartMergeOp::_compareTags(Tags t1, Tags t2)
{
  // remove all the building tags that are building:part=yes specific.
  for (set<QString>::const_iterator it = _buildingPartTagNames.begin();
    it != _buildingPartTagNames.end(); it++)
  {
    t1.remove(*it);
    t2.remove(*it);
  }

  double score = TagComparator::getInstance().compareTags(t1, t2);
  // check for score near 1.0
  return fabs(1.0 - score) < 0.001;
}