void inPointCallback(const geometry_msgs::Point& pt_msg) {

    g_O_entry_point(0) = pt_msg.x;
    g_O_entry_point(1) = pt_msg.y;
    g_O_entry_point(2) = pt_msg.z;
    g_got_new_entry_point = true;

    cout << "received new entry point = " << g_O_entry_point.transpose() << endl;
}