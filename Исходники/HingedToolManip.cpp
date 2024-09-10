void init(){

    //find the path of config files
    std::string selfpath = get_selfpath();
    //select using normal control mode or psudogravity control mode
    right_rmt = NormalMode;
    //initialize FT sensor ptr
    ft_gama = new gamaFT;
    ft.setZero(6);
    tool_vec_g.setZero();
    axis_end_vec.setZero();
    
    //show toolname
    tn = hingedtool;
    StopFlag = false;
    //initialize the axis vec
    local_hinged_axis_vec.setZero();
    local_hinged_axis_vec(0) = -0.9472;
    local_hinged_axis_vec(1) = 0.0494;
    local_hinged_axis_vec(2) = -0.3166;
    
    des_tm.setZero();
    des_vec.setZero();
    
    //declare the cb function

    boost::function<void(boost::shared_ptr<std::string>)> button_sdh_moveto(sdh_moveto_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_sdhaxisvec_moveto(sdhaxisvec_moveto_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_sdhmaintainF(sdhmaintainF_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_sdhslideX(sdhslideX_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_sdhslideY(sdhslideY_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_sdhfoldtool(sdhfoldtool_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_gamaftcalib(gamaftcalib_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_sdh_grav_comp_ctrl(sdh_grav_comp_ctrl_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_sdh_normal_ctrl(sdh_normal_ctrl_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_brake(brake_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_nobrake(nobrake_cb);
    boost::function<void(boost::shared_ptr<std::string>)> button_closeprog(closeprog_cb);

    //specify controller configure file in order to load it(right kuka + shadow hand)
    std::string config_filename = selfpath + "/etc/right_arm_param.xml";
    std::cout<<"right arm config file name is: "<<config_filename<<std::endl;
    //load controller parameters
    right_pm = new ParameterManager(config_filename);
    //initialize ptr to right kuka com okc
    com_okc_right = new ComOkc(kuka_right,OKC_HOST,OKC_PORT);

    //connect kuka right
    com_okc_right->connect();

    //initialize the kuka robot and let it stay in the init pose
    kuka_right_arm = new KukaLwr(kuka_right,*com_okc_right,tn);

    //initialize the robot state
    right_rs = new RobotState(kuka_right_arm);

    //get the initialize state of kuka right
    kuka_right_arm->get_joint_position_act();
    kuka_right_arm->update_robot_state();
    right_rs->updated(kuka_right_arm);
    right_ac_vec.push_back(new ProActController(*right_pm));
    right_task_vec.push_back(new KukaSelfCtrlTask(RP_NOCONTROL));
    right_task_vec.back()->mt = JOINTS;
    right_task_vec.back()->mft = GLOBAL;

    Eigen::Vector3d p,o;
    p.setZero();
    o.setZero();
    //get start point position in cartesian space
    p(0) = initP_x = right_rs->robot_position["eef"](0);
    p(1) = initP_y= right_rs->robot_position["eef"](1);
    p(2) = initP_z= right_rs->robot_position["eef"](2);

    o = tm2axisangle(right_rs->robot_orien["eef"]);
    initO_x = o(0);
    initO_y = o(1);
    initO_z = o(2);
    right_task_vec.back()->set_desired_p_eigen(p);
    right_task_vec.back()->set_desired_o_ax(o);

    kuka_right_arm->setAxisStiffnessDamping(right_ac_vec.back()->pm.stiff_ctrlpara.axis_stiffness, \
                                           right_ac_vec.back()->pm.stiff_ctrlpara.axis_damping);

    com_rsb = new ComRSB();
    rdtschunkjs = SchunkJS;
    com_rsb->add_msg(rdtschunkjs);
    gama_f_filter = new TemporalSmoothingFilter<Eigen::Vector3d>(10,Average,Eigen::Vector3d(0,0,0));
    gama_t_filter = new TemporalSmoothingFilter<Eigen::Vector3d>(10,Average,Eigen::Vector3d(0,0,0));

    //register cb function
    com_rsb->register_external("/foo/sdhmoveto",button_sdh_moveto);
    com_rsb->register_external("/foo/sdhaxisvecmoveto",button_sdhaxisvec_moveto);
    com_rsb->register_external("/foo/sdhmaintainF",button_sdhmaintainF);
    com_rsb->register_external("/foo/sdhslideX",button_sdhslideX);
    com_rsb->register_external("/foo/sdhslideY",button_sdhslideY);
    com_rsb->register_external("/foo/sdhfoldtool",button_sdhfoldtool);
    com_rsb->register_external("/foo/gamaftcalib",button_gamaftcalib);
    com_rsb->register_external("/foo/sdh_grav_comp_ctrl",button_sdh_grav_comp_ctrl);
    com_rsb->register_external("/foo/sdh_normal_ctrl",button_sdh_normal_ctrl);
    com_rsb->register_external("/foo/closeprog",button_closeprog);

#ifdef HAVE_ROS
    std::string left_kuka_arm_name="la";
    std::string right_kuka_arm_name="ra";
    std::string left_schunk_hand_name ="lh";
    js_la.name.push_back(left_kuka_arm_name+"_arm_0_joint");
    js_la.name.push_back(left_kuka_arm_name+"_arm_1_joint");
    js_la.name.push_back(left_kuka_arm_name+"_arm_2_joint");
    js_la.name.push_back(left_kuka_arm_name+"_arm_3_joint");
    js_la.name.push_back(left_kuka_arm_name+"_arm_4_joint");
    js_la.name.push_back(left_kuka_arm_name+"_arm_5_joint");
    js_la.name.push_back(left_kuka_arm_name+"_arm_6_joint");
    js_ra.name.push_back(right_kuka_arm_name+"_arm_0_joint");
    js_ra.name.push_back(right_kuka_arm_name+"_arm_1_joint");
    js_ra.name.push_back(right_kuka_arm_name+"_arm_2_joint");
    js_ra.name.push_back(right_kuka_arm_name+"_arm_3_joint");
    js_ra.name.push_back(right_kuka_arm_name+"_arm_4_joint");
    js_ra.name.push_back(right_kuka_arm_name+"_arm_5_joint");
    js_ra.name.push_back(right_kuka_arm_name+"_arm_6_joint");
    
    //for schunk
    js_schunk.name.push_back(left_schunk_hand_name+"_sdh_knuckle_joint");
    js_schunk.name.push_back(left_schunk_hand_name+"_sdh_finger_22_joint");
    js_schunk.name.push_back(left_schunk_hand_name+"_sdh_finger_23_joint");
    js_schunk.name.push_back(left_schunk_hand_name+"_sdh_thumb_2_joint");
    js_schunk.name.push_back(left_schunk_hand_name+"_sdh_thumb_3_joint");
    js_schunk.name.push_back(left_schunk_hand_name+"_sdh_finger_12_joint");
    js_schunk.name.push_back(left_schunk_hand_name+"_sdh_finger_13_joint");

    js_la.position.resize(7);
    js_la.velocity.resize(7);
    js_la.effort.resize(7);

    js_ra.position.resize(7);
    js_ra.velocity.resize(7);
    js_ra.effort.resize(7);
    
    js_schunk.position.resize(7);
    js_schunk.velocity.resize(7);
    js_schunk.effort.resize(7);

    js_la.header.frame_id="frame_la";
    js_ra.header.frame_id="frame_ra";
    js_ra.header.frame_id="frame_lh";

    gamma_force_marker_pub = nh->advertise<visualization_msgs::Marker>("gamma_force_marker", 2);
    hingedtool_axis_marker_pub = nh->advertise<visualization_msgs::Marker>("hingedtool_axis_marker", 2);

    jsPub_la = nh->advertise<sensor_msgs::JointState> ("/la/joint_states", 2);
    jsPub_ra = nh->advertise<sensor_msgs::JointState> ("/ra/joint_states", 2);
    jsPub_schunk = nh->advertise<sensor_msgs::JointState> ("/lh/joint_states", 2);
    ros::spinOnce();

    br = new tf::TransformBroadcaster();

    std::cout<<"ros init finished"<<std::endl;
#endif
}