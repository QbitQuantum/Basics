void CombatCamera::MouseWheel(const GG::Pt& pt, int move, GG::Flags<GG::ModKey> mod_keys)
{
    Ogre::Real total_move = TotalMove(move, mod_keys, DistanceToLookAtPoint());
    if (0 < move)
    {
        const unsigned int TICKS = GG::GUI::GetGUI()->Ticks();

        const unsigned int ZOOM_IN_TIMEOUT = 750u;
        if (m_initial_zoom_in_position == INVALID_MAP_LOCATION ||
            ZOOM_IN_TIMEOUT < TICKS - m_previous_zoom_in_time)
        {
            std::pair<bool, Ogre::Vector3> intersection = IntersectMouseWithEcliptic(pt);
            m_initial_zoom_in_position = intersection.first ? intersection.second : INVALID_MAP_LOCATION;
        }

        if (m_initial_zoom_in_position != INVALID_MAP_LOCATION) {
            const double CLOSE_FACTOR = move * 0.333 * ZoomFactor(mod_keys);
            Ogre::Vector3 start = Moving() ? m_look_at_point_target : LookAtPoint();
            Ogre::Vector3 delta = m_initial_zoom_in_position - start;
            double delta_length = delta.length();
            double distance = std::min(std::max(1.0, delta_length * CLOSE_FACTOR), delta_length);
            delta.normalise();
            Ogre::Vector3 new_center = start + delta * distance;
            if (new_center.length() < SystemRadius())
                LookAtPositionAndZoom(new_center, ZoomResult(total_move));
        }

        m_previous_zoom_in_time = TICKS;
    } else if (move < 0) {
        ZoomImpl(total_move);
    }
}