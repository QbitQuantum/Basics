inline void KinematicUtil::get_head_angles_for_distance_intern(KRobot& robot, const Vector2d& pos, bool left_leg, double y_angle, double x_angle) {
    Affine3d base, inv_base;
    //handle support leg
    if(left_leg) {
        inv_base = robot.get_joint_by_id(JointIds::LFootEndpoint).get_chain_matrix_inverse();
        base = robot.get_joint_by_id(JointIds::LFootEndpoint).get_chain_matrix();
    } else {
        inv_base = robot.get_joint_by_id(JointIds::RFootEndpoint).get_chain_matrix_inverse();
        base = robot.get_joint_by_id(JointIds::RFootEndpoint).get_chain_matrix();
    }
    Vector3d head_pos = (inv_base.matrix() * robot.get_joint_by_id(JointIds::Camera).get_endpoint()).head<3>();
    head_pos.y() = 0;
    //difference vector between head and the point to focus
    Vector3d diff = (Vector3d()<<pos, 0).finished() - head_pos;
    Vector3d target = base.linear() * diff.normalized();
    //handle "special" tasks. Those tasks where another point than the middle point should have the given distance.
    if(additional_parameter > 0) {
        Vector3d y_orthogonal, x_orthogonal;
        //Calculate an orthogonal vector to have a rotation axis when rotating the target vector, so that y-angle has the given distance
        y_orthogonal = diff.cross(Vector3d::UnitZ()).normalized();
        L_DEBUG(cout<<"Orthogonale:\n"<<y_orthogonal.transpose()<<endl);
        //Creating the rotation type
        AngleAxisd y_turn( - y_angle, y_orthogonal);
        L_DEBUG(cout<<"Turn Matrix:\n"<<(Matrix3d()<<(Matrix3d::Identity() * y_turn)).finished()<<endl);
        //rotating
        target = y_turn * target;
        if(additional_parameter > 1) {
            //same as for y-axis now for x-axis, y-axis first because of "dependencies"
            x_orthogonal = diff.cross(y_orthogonal).normalized();
            L_DEBUG(cout<<"Orthogonale:\n"<<x_orthogonal.transpose()<<endl);
            AngleAxisd x_turn(x_angle, x_orthogonal);
            L_DEBUG(cout<<"Turn Matrix:\n"<<(Matrix3d()<<(Matrix3d::Identity() * x_turn)).finished()<<endl);
            target = x_turn * target;
        }
    }
    robot.inverse_chain(ChainIds::HeadChain, target, 1e-3, 100, Kin::KJoint::AxisType::XAxis);
    L_DEBUG(cout<<"angles: y_angle:" << y_angle << " x_angle: "<< x_angle<<endl);
    L_DEBUG(cout<< "Target"<<endl<<target.transpose()<<endl);
    L_DEBUG(cout<<"Head"<<endl<<(robot.get_joint_by_id(JointIds::LFootEndpoint).get_chain_matrix_inverse() * robot.get_joint_by_id(JointIds::Camera).get_chain_matrix()).matrix()<<endl);
}