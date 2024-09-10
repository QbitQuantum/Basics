    void callback(const PointPlusConstPtr& robot_point, const PointPlusConstPtr& mass_point)
	{
	    ROS_DEBUG("Synchronized Callback triggered");
	    puppeteer_msgs::PointPlus r_pt, m_pt;

	    // if not in run or calibrate, just exit
	    if (run_system_logic())
		return;

	    // let's first correct for the radii of the objects:
	    r_pt = *robot_point;
	    r_pt = correct_vals(r_pt, DEFAULT_ROBOT_RADIUS);
	    m_pt = *mass_point;
	    m_pt = correct_vals(m_pt, DEFAULT_MASS_RADIUS);

	    if (calibrated_flag == false)
	    {
		if (calibrate_count == 0)
		{
		    calibrate_count++;
		    robot_cal_pos << 0, 0, 0;
		    mass_cal_pos << 0, 0, 0;
		    robot_start_pos << 0, 0, 0;
		    mass_start_pos << 0, 0, 0;
		    return;
		}
		else if (calibrate_count <= NUM_CALIBRATES)
		{
		    ROS_INFO_THROTTLE(1, "Calibrating...");
		    if (!m_pt.error && !r_pt.error)
		    {
			// then we got both objects successfully:
			robot_cal_pos(0) += r_pt.x;
			robot_cal_pos(1) += r_pt.y;
			robot_cal_pos(2) += r_pt.z;
			mass_cal_pos(0) += m_pt.x;
			mass_cal_pos(1) += m_pt.y;
			mass_cal_pos(2) += m_pt.z;
			calibrate_count++;
		    }
		    return;
		}
		else
		{
		    ROS_INFO("Calibration completed successfully!");
		    // if here, calibration is done!
		    // first find averages:
		    robot_cal_pos = (robot_cal_pos/((double) NUM_CALIBRATES));
		    mass_cal_pos = (mass_cal_pos/((double) NUM_CALIBRATES));
		    // now set start positions:
		    mass_start_pos << q0.xm, q0.ym, 0;
		    robot_start_pos << q0.xr, H0, 0;
		    // now get the transform:
		    mass_cal_pos -= mass_start_pos;
		    robot_cal_pos -= robot_start_pos;
		    // let's check if there is an error here:
		    ////////////////////////
                    // ERROR CHECK	  //
                    ////////////////////////
		    // if no error:
		    // cal_pos = (mass_cal_pos + robot_cal_pos)/2.0;
		    cal_pos = mass_cal_pos;

		    // reset vars:
		    calibrate_count = 0;
		    calibrated_flag = true;
		}
	    }
	    
	    // send global frame transforms:
	    send_global_transforms(m_pt.header.stamp);

	    // transform both of the points into the
	    // optimization_frame, build the output message, and
	    // publish
	    tf::Transform transform;
	    PlanarSystemConfig qmeas;
	    Eigen::Affine3d gwo;
	    Eigen::Vector3d robot_trans, mass_trans;
	    transform.setOrigin(tf::Vector3(cal_pos(0),
					    cal_pos(1), cal_pos(2)));
	    transform.setRotation(tf::Quaternion(0,0,0,1));
	    tf::TransformTFToEigen(transform, gwo);
	    gwo = gwo.inverse();
	    // transform robot:
	    robot_trans << r_pt.x, r_pt.y, r_pt.z;
	    robot_trans = gwo*robot_trans;
	    // transform mass:
	    mass_trans << m_pt.x, m_pt.y, m_pt.z;
	    mass_trans = gwo*mass_trans;
	    // calculate string length:
	    mass_trans(2) = 0; robot_trans(2) = 0;
	    double rad = (mass_trans - robot_trans).norm();
	    qmeas.xm = mass_trans(0);
	    qmeas.ym = mass_trans(1);
	    qmeas.xr = robot_trans(0);
	    qmeas.r = rad;
	    qmeas.mass_err = m_pt.error;
	    qmeas.robot_err = r_pt.error;
	    qmeas.header.stamp = m_pt.header.stamp;
	    qmeas.header.frame_id = "optimization_frame";
	    config_pub.publish(qmeas);
		    
	    return;
	}