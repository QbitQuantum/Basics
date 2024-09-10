//-----------------------------------------------------------------------------
void AIBaseController::checkPosition(const Vec3 &point, posData *pos_data,
                                     Vec3 *lc, bool use_front_xyz) const
{
    // Convert to local coordinates from the point of view of current kart
    btQuaternion q(btVector3(0, 1, 0), -m_kart->getHeading());
    Vec3 p = point -
        (use_front_xyz ? m_kart->getFrontXYZ() : m_kart->getXYZ());
    Vec3 local_coordinates = quatRotate(q, p);

    // Save local coordinates for later use if needed
    if (lc) *lc = local_coordinates;

    if (pos_data == NULL) return;
    // lhs: tell whether it's left or right hand side
    if (local_coordinates.getX() < 0)
        pos_data->lhs = true;
    else
        pos_data->lhs = false;

    // behind: tell whether it's behind or not
    if (local_coordinates.getZ() < 0)
        pos_data->behind = true;
    else
        pos_data->behind = false;

    pos_data->angle = atan2(fabsf(local_coordinates.getX()),
        fabsf(local_coordinates.getZ()));
    pos_data->distance = p.length();

}   //  checkPosition