int EuclidDistHeuristic::GetGoalHeuristic(int state_id)
{
    if (state_id == planningSpace()->getGoalStateID()) {
        return 0;
    }

    if (m_pose_ext) {
        Affine3 p;
        if (!m_pose_ext->projectToPose(state_id, p)) {
            return 0;
        }

        auto& goal_pose = planningSpace()->goal().pose;

        const double dist = computeDistance(p, goal_pose);

        const int h = FIXED_POINT_RATIO * dist;

        double Y, P, R;
        angles::get_euler_zyx(p.rotation(), Y, P, R);
        SMPL_DEBUG_NAMED(LOG, "h(%0.3f, %0.3f, %0.3f, %0.3f, %0.3f, %0.3f) = %d", p.translation()[0], p.translation()[1], p.translation()[2], Y, P, R, h);

        return h;
    } else if (m_point_ext) {
        Vector3 p;
        if (!m_point_ext->projectToPoint(state_id, p)) {
            return 0;
        }

        auto& goal_pose = planningSpace()->goal().pose;
        Vector3 gp(goal_pose.translation());

        double dist = computeDistance(p, gp);

        const int h = FIXED_POINT_RATIO * dist;
        SMPL_DEBUG_NAMED(LOG, "h(%d) = %d", state_id, h);
        return h;
    } else {
        return 0;
    }
}