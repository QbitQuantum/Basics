bool
TargetMapWindow::isClickOnTarget(const RasterPoint pc)
{
  if (task == NULL)
    return false;

  ProtectedTaskManager::Lease task_manager(*task);
  if (!task_manager->has_target(target_index))
    return false;

  const GeoPoint gnull(Angle::zero(), Angle::zero());
  const GeoPoint& t = task_manager->get_location_target(target_index, gnull);

  if (t == gnull)
    return false;

  const GeoPoint gp = projection.ScreenToGeo(pc.x, pc.y);
  if (projection.GeoToScreenDistance(gp.distance(t)) <
      unsigned(Layout::Scale(10)))
    return true;

  return false;
}