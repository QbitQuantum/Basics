void jointStatesCb(const sensor_msgs::JointState& js_msg) {
    //joint_states_ = js_msg; // does joint-name mapping only once
    if (g_arm_joint_indices.size()<1) {
        int njnts = js_msg.position.size();
        ROS_INFO("finding joint mappings for %d jnts",njnts);
       map_arm_joint_indices(js_msg.name);
    }
       for (int i=0;i<VECTOR_DIM;i++)
       {
        g_q_vec[i] = js_msg.position[g_arm_joint_indices[i]];
        }
        cout<<"CB: q_vec_right_arm: "<<g_q_vec.transpose()<<endl;       
    
}