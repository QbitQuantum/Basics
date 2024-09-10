inline double
OrderedTask::ScanDistanceMin(const GeoPoint &location, bool full)
{
  if (!full && location.IsValid() && last_min_location.IsValid() &&
      DistanceIsSignificant(location, last_min_location)) {
    const TaskWaypoint *active = GetActiveTaskPoint();
    if (active != nullptr) {
      const GeoPoint &target = active->GetWaypoint().location;
      const unsigned last_distance =
        (unsigned)last_min_location.Distance(target);
      const unsigned cur_distance =
        (unsigned)location.Distance(target);

      /* do the full scan only if the distance to the active task
         point has changed by more than 5%, otherwise we don't expect
         any relevant changes */
      if (last_distance < 2000 || cur_distance < 2000 ||
          last_distance * 20 >= cur_distance * 21 ||
          cur_distance * 20 >= last_distance * 21)
        full = true;
    }
  }

  if (full) {
    RunDijsktraMin(location);
    last_min_location = location;
  }

  return task_points.front()->ScanDistanceMin();
}