int farthestPoint(const tf::Vector3& point, const std::vector<tf::Vector3>& hand_positions)
{
  double dist, max_distant = 0;
  size_t index = 0;
  for (size_t i = 0; i < hand_positions.size(); i++)
  {
    dist = point.distance(hand_positions[i]);
    if (dist > max_distant)
    {
      max_distant = dist;
      index = i;
    }
  }
  return index;
}