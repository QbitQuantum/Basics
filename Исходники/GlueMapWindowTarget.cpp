bool
GlueMapWindow::isClickOnTarget(const RasterPoint pc)
{
    if (task == NULL)
        return false;

    if (XCSoarInterface::SettingsMap().TargetPan) {
        ProtectedTaskManager::Lease task_manager(*task);
        if (!task_manager->target_is_locked(XCSoarInterface::SettingsMap().TargetPanIndex))
            return false;

        const GeoPoint gnull(Angle::native(fixed_zero), Angle::native(fixed_zero));
        const GeoPoint& t = task_manager->get_location_target(
                                XCSoarInterface::SettingsMap().TargetPanIndex, gnull);

        if (t == gnull)
            return false;

        const GeoPoint gp = visible_projection.ScreenToGeo(pc.x, pc.y);
        if (visible_projection.GeoToScreenDistance(gp.distance(t)) <
                unsigned(Layout::Scale(10)))
            return true;
    }
    return false;
}