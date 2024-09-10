void inPointsCallback(const geometry_msgs::Polygon& pts_array) {
    if (pts_array.points.size() != 2) {
        ROS_ERROR("wrong number of points in pts_array! should be two");
        return;
    }
    //unpack the points and fill in entry and exit pts
    g_O_entry_point(0) = pts_array.points[0].x;
    g_O_entry_point(1) = pts_array.points[0].y;
    g_O_entry_point(2) = pts_array.points[0].z;
    g_O_exit_point(0) = pts_array.points[1].x;
    g_O_exit_point(1) = pts_array.points[1].y;
    g_O_exit_point(2) = pts_array.points[1].z;

    g_got_new_points = true;

    cout << "received new entry point = " << g_O_entry_point.transpose() << endl;
    cout << "and exit point: " << g_O_exit_point.transpose() << endl;
}