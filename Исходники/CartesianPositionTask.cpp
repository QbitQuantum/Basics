            bodyId_, controlPoint_, true);
        tare = 0;
    }
  
    // Get the latest joint state information
    Vector Q(model.getNumDOFs());
    Vector Qd(model.getNumDOFs());
  
    model.getLatestFullState(Q, Qd);
  
    Vector3d bodyTranslation = RigidBodyDynamics::CalcBodyToBaseCoordinates(model.rbdlModel(), Q, bodyId_, Vector::Zero(3), false);
    Matrix3d bodyRotation =  RigidBodyDynamics::CalcBodyWorldOrientation(model.rbdlModel(), Q, bodyId_, false);
  
    getJacobian(JtLoc);
  
    xCurWorld = bodyRotation.transpose() * controlPoint_ + bodyTranslation;
    Matrix3d frameRotation;
    Vector3d frameTranslation;

    if(frameId_ == -1) //Using fixed world frame as reference, latching immaterial.
    {

        // if (projection_.cols() != xCurWorld.rows())
        // {
        //     CONTROLIT_ERROR << "Matrix size problem:\n"
        //                     << "  - frameId_ = " << frameId_ << "\n"
        //                     << "  - projection_ = " << projection_ << "\n"
        //                     << "  - xCurWorld_ = " << xCurWorld;
        // }

        xCurFrameProjected = projection_ * xCurWorld;