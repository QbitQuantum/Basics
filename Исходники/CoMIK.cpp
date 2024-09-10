    Eigen::MatrixXf CoMIK::getJacobianOfCoM(RobotNodePtr node)
    {
        // Get number of degrees of freedom
        size_t nDoF = rns->getAllRobotNodes().size();

        // Create matrices for the position and the orientation part of the jacobian.
        Eigen::MatrixXf position = Eigen::MatrixXf::Zero(3, nDoF);

        const std::vector<RobotNodePtr> parentsN = bodyNodeParents[node];

        // Iterate over all degrees of freedom
        for (size_t i = 0; i < nDoF; i++)
        {
            RobotNodePtr dof = rns->getNode(i);// bodyNodes[i];

            // Check if the tcp is affected by this DOF
            if (find(parentsN.begin(), parentsN.end(), dof) != parentsN.end())
            {
                // Calculus for rotational joints is different as for prismatic joints.
                if (dof->isRotationalJoint())
                {
                    // get axis
                    boost::shared_ptr<RobotNodeRevolute> revolute
                        = boost::dynamic_pointer_cast<RobotNodeRevolute>(dof);
                    THROW_VR_EXCEPTION_IF(!revolute, "Internal error: expecting revolute joint");
                    // todo: find a better way of handling different joint types
                    Eigen::Vector3f axis = revolute->getJointRotationAxis(coordSystem);

                    // For CoM-Jacobians only the positional part is necessary
                    Eigen::Vector3f toTCP = node->getCoMLocal() + node->getGlobalPose().block(0, 3, 3, 1)
                                            - dof->getGlobalPose().block(0, 3, 3, 1);
                    position.block(0, i, 3, 1) = axis.cross(toTCP);
                }
                else if (dof->isTranslationalJoint())
                {
                    // -> prismatic joint
                    boost::shared_ptr<RobotNodePrismatic> prismatic
                        = boost::dynamic_pointer_cast<RobotNodePrismatic>(dof);
                    THROW_VR_EXCEPTION_IF(!prismatic, "Internal error: expecting prismatic joint");
                    // todo: find a better way of handling different joint types
                    Eigen::Vector3f axis = prismatic->getJointTranslationDirection(coordSystem);

                    position.block(0, i, 3, 1) = axis;
                }
            }
        }

        if (target.rows() == 2)
        {
            Eigen::MatrixXf result(2, nDoF);
            result.row(0) = position.row(0);
            result.row(1) = position.row(1);
            return result;
        }
        else if (target.rows() == 1)
        {
            VR_INFO << "One dimensional CoMs not supported." << endl;
        }

        return position;
    }