size_t Room::findClosestSurfaceIndex(const Position &position) const
{
  if (surfaces_.empty())
  {
    throw out_of_range("Room::findClosestSurface : No surfaces exist.");
  } else
  {
    // go through each and check the distance
    double best = numeric_limits<double>::infinity();
    size_t best_index = 0;
    for (size_t i = 0; i < surfaces_.size(); i++)
    {
      // calculate distance
      double distance = position.distance(surfaces_[i].getPose().getPosition());
      if (distance < best)
      {
        best = distance;
        best_index = i;
      }
    }

    return best_index;
  }
}