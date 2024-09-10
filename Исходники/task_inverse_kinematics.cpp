	bool TaskInverseKinematics::init(hardware_interface::EffortJointInterface *robot, ros::NodeHandle &n)
	{
        nh_ = n;

        // get URDF and name of root and tip from the parameter server
        std::string robot_description, root_name, tip_name;

        if (!ros::param::search(n.getNamespace(),"robot_description", robot_description))
        {
            ROS_ERROR_STREAM("TaskInverseKinematics: No robot description (URDF) found on parameter server ("<<n.getNamespace()<<"/robot_description)");
            return false;
        }
        if (!nh_.getParam("root_name", root_name))
        {
            ROS_ERROR_STREAM("TaskInverseKinematics: No root name found on parameter server ("<<n.getNamespace()<<"/root_name)");
            return false;
        }
        if (!nh_.getParam("tip_name", tip_name))
        {
            ROS_ERROR_STREAM("TaskInverseKinematics: No tip name found on parameter server ("<<n.getNamespace()<<"/tip_name)");
            return false;
        }

        ROS_INFO("robot_description: %s",robot_description.c_str());
        ROS_INFO("root_name:         %s",root_name.c_str());
        ROS_INFO("tip_name:          %s",tip_name.c_str());


        // Get the gravity vector (direction and magnitude)
        KDL::Vector gravity_ = KDL::Vector::Zero();
        gravity_(2) = -9.81;

        // Construct an URDF model from the xml string
        std::string xml_string;

        if (n.hasParam(robot_description))
            n.getParam(robot_description.c_str(), xml_string);
        else
        {
            ROS_ERROR("Parameter %s not set, shutting down node...", robot_description.c_str());
            n.shutdown();
            return false;
        }

        if (xml_string.size() == 0)
        {
            ROS_ERROR("Unable to load robot model from parameter %s",robot_description.c_str());
            n.shutdown();
            return false;
        }

        ROS_DEBUG("%s content\n%s", robot_description.c_str(), xml_string.c_str());

        // Get urdf model out of robot_description
        urdf::Model model;
        if (!model.initString(xml_string))
        {
            ROS_ERROR("Failed to parse urdf file");
            n.shutdown();
            return false;
        }
        ROS_DEBUG("Successfully parsed urdf file");

        KDL::Tree kdl_tree_;
        if (!kdl_parser::treeFromUrdfModel(model, kdl_tree_))
        {
            ROS_ERROR("Failed to construct kdl tree");
            n.shutdown();
            return false;
        }



        // Populate the KDL chain
        if(!kdl_tree_.getChain(root_name, tip_name, kdl_chain_))
        {
            ROS_ERROR_STREAM("Failed to get KDL chain from tree: ");
            ROS_ERROR_STREAM("  "<<root_name<<" --> "<<tip_name);
            ROS_ERROR_STREAM("  Tree has "<<kdl_tree_.getNrOfJoints()<<" joints");
            ROS_ERROR_STREAM("  Tree has "<<kdl_tree_.getNrOfSegments()<<" segments");
            ROS_ERROR_STREAM("  The segments are:");

            KDL::SegmentMap segment_map = kdl_tree_.getSegments();
            KDL::SegmentMap::iterator it;

            for( it=segment_map.begin(); it != segment_map.end(); it++ )
              ROS_ERROR_STREAM( "    "<<(*it).first);

            return false;
        }
        ROS_DEBUG("Number of segments: %d", kdl_chain_.getNrOfSegments());
        ROS_DEBUG("Number of joints in chain: %d", kdl_chain_.getNrOfJoints());


        // Parsing joint limits from urdf model
        boost::shared_ptr<const urdf::Link> link_ = model.getLink(tip_name);
        boost::shared_ptr<const urdf::Joint> joint_;
        joint_limits_.min.resize(kdl_chain_.getNrOfJoints());
        joint_limits_.max.resize(kdl_chain_.getNrOfJoints());
        joint_limits_.center.resize(kdl_chain_.getNrOfJoints());
        int index;

        std::cout<< "kdl_chain_.getNrOfJoints(): " << kdl_chain_.getNrOfJoints() << std::endl;

        for (int i = 0; i < kdl_chain_.getNrOfJoints() && link_; i++)
        {
            joint_ = model.getJoint(link_->parent_joint->name);
            index = kdl_chain_.getNrOfJoints() - i - 1;

            joint_limits_.min(index) = joint_->limits->lower;
            joint_limits_.max(index) = joint_->limits->upper;
            joint_limits_.center(index) = (joint_limits_.min(index) + joint_limits_.max(index))/2;

            link_ = model.getLink(link_->getParent()->name);
        }
        ROS_INFO("Successfully parsed joint limits");






        // Get joint handles for all of the joints in the chain
        for(std::vector<KDL::Segment>::const_iterator it = kdl_chain_.segments.begin()+1; it != kdl_chain_.segments.end(); ++it)
        {
            joint_handles_.push_back(robot->getHandle(it->getJoint().getName()));
            ROS_DEBUG("%s", it->getJoint().getName().c_str() );
        }

        ROS_DEBUG(" Number of joints in handle = %lu", joint_handles_.size() );

        PIDs_.resize(kdl_chain_.getNrOfJoints());

        // Parsing PID gains from YAML
        std::string pid_ = ("pid_");
        for (int i = 0; i < joint_handles_.size(); ++i)
        {
            if (!PIDs_[i].init(ros::NodeHandle(n, pid_ + joint_handles_[i].getName())))
            {
                ROS_ERROR("Error initializing the PID for joint %d",i);
                return false;
            }
        }

        jnt_to_jac_solver_.reset(new KDL::ChainJntToJacSolver(kdl_chain_));
        id_solver_.reset(new KDL::ChainDynParam(kdl_chain_,gravity_));
        fk_pos_solver_.reset(new KDL::ChainFkSolverPos_recursive(kdl_chain_));
        ik_vel_solver_.reset(new KDL::ChainIkSolverVel_pinv(kdl_chain_));
        ik_pos_solver_.reset(new KDL::ChainIkSolverPos_NR_JL(kdl_chain_,joint_limits_.min,joint_limits_.max,*fk_pos_solver_,*ik_vel_solver_));

        joint_msr_states_.resize(kdl_chain_.getNrOfJoints());
        joint_des_states_.resize(kdl_chain_.getNrOfJoints());
        tau_cmd_.resize(kdl_chain_.getNrOfJoints());
        J_.resize(kdl_chain_.getNrOfJoints());

        sub_command_ = nh_.subscribe("command_configuration", 1, &TaskInverseKinematics::command_configuration, this);

        return true;
	}