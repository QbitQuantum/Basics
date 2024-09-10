/**
 * Recursion method to be used with traverseTreeTopDown() and recursion parameters
 * of type *Vector3RecursionParams*.
 *
 * Re-arranges the joint-transform of the recursion link's *parent joint*, along with
 * the link's visual/collision/intertial rotations, such that all joints rotate around the axis
 * given in the recursion parameters vector.
 */
int allRotationsToAxisCB(urdf_traverser::RecursionParamsPtr& p)
{
    urdf_traverser::LinkPtr link = p->getLink();
    if (!link)
    {
        ROS_ERROR("allRotationsToAxis: NULL link passed");
        return -1;
    }

    Vector3RecursionParams::Ptr param = baselib_binding_ns::dynamic_pointer_cast<Vector3RecursionParams>(p);
    if (!param)
    {
        ROS_ERROR("Wrong recursion parameter type");
        return -1;
    }

    urdf_traverser::JointPtr joint = link->parent_joint;
    if (!joint)
    {
        ROS_INFO_STREAM("allRotationsToAxis: Joint for link " << link->name << " is NULL, so this must be the root joint");
        return 1;
    }

    Eigen::Vector3d axis = param->vec;

    Eigen::Quaterniond alignAxis;
    if (urdf_traverser::jointTransformForAxis(joint, axis, alignAxis))
    {
        Eigen::Vector3d rotAxis(joint->axis.x, joint->axis.y, joint->axis.z);
        // ROS_INFO_STREAM("Transforming axis "<<rotAxis<<" for joint "<<joint->name<<" with transform "<<urdf_traverser::EigenTransform(alignAxis));

        urdf_traverser::applyTransform(joint, urdf_traverser::EigenTransform(alignAxis), false);

        // the link has to receive the inverse transform, so it stays at the original position
        Eigen::Quaterniond alignAxisInv = alignAxis.inverse();
        urdf_traverser::applyTransform(link, urdf_traverser::EigenTransform(alignAxisInv), true);

        // we also have to fix the child joint's (1st order child joints) transform
        // to correct for this transformation.
        for (std::vector<urdf_traverser::JointPtr>::iterator pj = link->child_joints.begin();
                pj != link->child_joints.end(); pj++)
        {
            urdf_traverser::applyTransform(*pj, urdf_traverser::EigenTransform(alignAxisInv), true);
        }

        // finally, set the rotation axis to the target
        joint->axis.x = axis.x();
        joint->axis.y = axis.y();
        joint->axis.z = axis.z();
    }

    // all good, indicate that recursion can continue
    return 1;
}