bool
OLCTriangle::FindClosingPairs(unsigned old_size)
{
  if (predict) {
    return closing_pairs.insert(ClosingPair(0, n_points-1));
  }

  struct TracePointNodeAccessor {
    gcc_pure
    int GetX(const TracePointNode &node) const {
      return node.point->GetFlatLocation().longitude;
    }

    gcc_pure
    int GetY(const TracePointNode &node) const {
      return node.point->GetFlatLocation().latitude;
    }
  };

  QuadTree<TracePointNode, TracePointNodeAccessor> search_point_tree;

  for (unsigned i = old_size; i < n_points; ++i) {
    TracePointNode node;
    node.point = &GetPoint(i);
    node.index = i;

    search_point_tree.insert(node);
  }

  search_point_tree.Optimise();

  bool new_pair = false;

  for (unsigned i = old_size; i < n_points; ++i) {
    TracePointNode point;
    point.point = &GetPoint(i);
    point.index = i;

    const unsigned max_range =
      trace_master.ProjectRange(GetPoint(i).GetLocation(), max_distance);

    const GeoPoint start = GetPoint(i).GetLocation();
    const int min_altitude = GetMinimumFinishAltitude(GetPoint(i));
    const int max_altitude = GetMaximumStartAltitude(GetPoint(i));

    unsigned last = 0, first = i;

    const auto visitor = [this, i, start,
                          min_altitude, max_altitude,
                          &first, &last]
      (const TracePointNode &node) {
      const SearchPoint dest = GetPoint(node.index);

      if (node.index + 2 < i &&
          GetPoint(node.index).GetIntegerAltitude() <= max_altitude &&
          start.Distance(dest.GetLocation()) <= max_distance) {
        // point i is last point
        first = std::min(node.index, first);
        last = i;
      } else if (node.index > i + 2 &&
                 GetPoint(node.index).GetIntegerAltitude() >= min_altitude &&
                 start.Distance(dest.GetLocation()) <= max_distance) {
        // point i is first point
        first = i;
        last = std::max(node.index, last);
      }
    };

    search_point_tree.VisitWithinRange(point, max_range, visitor);

    if (last != 0 && closing_pairs.insert(ClosingPair(first, last)))
      new_pair = true;
  }

  return new_pair;
}