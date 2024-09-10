/**
 *
 * @param jnt the KDL::Joint to convert (axis and origin expressed in the
 *          predecessor frame of reference, as by KDL convention)
 * @param frameToTip the predecessor/successor frame transformation
 * @param H_new_old_predecessor in the case the predecessor frame is being
 *          modified to comply to URDF constraints (frame origin on the joint axis)
 *          this matrix the transformation from the old frame to the new frame (H_new_old)
 * @param H_new_old_successor  in the case the successor frame is being
 *          modified to comply to URDF constraints (frame origin on the joint axis)
 *          this matrix the transformation from the old frame to the new frame (H_new_old)
 */
urdf::Joint toUrdf(const KDL::Joint & jnt,
                   const KDL::Frame & frameToTip,
                   const KDL::Frame & H_new_old_predecessor,
                   KDL::Frame & H_new_old_successor)
{
    //URDF constaints the successor link frame origin to lay on the axis
    //of the joint ( see : http://www.ros.org/wiki/urdf/XML/joint )
    //Then if the JointOrigin of the KDL joint is not zero, it is necessary
    //to move the link frame (then it is necessary to change also the spatial inertia)
    //and the definition of the childrens of the successor frame
    urdf::Joint ret;
    ret.name = jnt.getName();

    H_new_old_successor = getH_new_old(jnt,frameToTip);

    ret.parent_to_joint_origin_transform = toUrdf(H_new_old_predecessor*frameToTip*(H_new_old_successor.Inverse()));

    switch(jnt.getType())
    {
        case KDL::Joint::RotAxis:
        case KDL::Joint::RotX:
        case KDL::Joint::RotY:
        case KDL::Joint::RotZ:
            //using continuos if no joint limits are specified
            ret.type = urdf::Joint::CONTINUOUS;
            //in urdf, the joint axis is expressed in the joint/successor frame
            //in kdl, the joint axis is expressed in the predecessor rame
            ret.axis = toUrdf(((frameToTip).M.Inverse((jnt.JointAxis()))));
        break;
        case KDL::Joint::TransAxis:
        case KDL::Joint::TransX:
        case KDL::Joint::TransY:
        case KDL::Joint::TransZ:
            ret.type = urdf::Joint::PRISMATIC;
            //in urdf, the joint axis is expressed in the joint/successor frame
            //in kdl, the joint axis is expressed in the predecessor rame
            ret.axis = toUrdf((frameToTip.M.Inverse(jnt.JointAxis())));
        break;
        default:
            std::cerr << "[WARN] Converting unknown joint type of joint " << jnt.getTypeName() << " into a fixed joint" << std::endl;
        case KDL::Joint::None:
            ret.type = urdf::Joint::FIXED;
    }
    return ret;
}