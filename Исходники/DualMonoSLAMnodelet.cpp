    SE3<> IMU2camWorldfromQuat(Eigen::Quaternion<double> atti){// use ini attitude info from EKF node to ini ptam pose
        Vector<4> attivec = makeVector(atti.w(), atti.x(), atti.y(), atti.z());//Rw1i
        Matrix<3> iniOrientationEKF;
        iniOrientationEKF = tag::quaternionToMatrix(attivec);

        Matrix<3> roll = TooN::Data(1.0, 0, 0,//Rww1, because the roll and pitch angles are in
                              0, -1, 0, // a world frame which pointing downward.
                              0, 0, -1);

        SE3<> camWorld = SE3<>();
        Matrix<3> rotation;
        if (tracker_->attitude_get)
            rotation = iniOrientationEKF; //
        else
            rotation = roll * iniOrientationEKF;//Rwi = Rww1*Rw1i
        camWorld.get_rotation() = rotation*se3IMUfromcam.get_rotation().get_matrix();//Rwc = (Rwi * Ric)

        Vector<3> twr = makeVector(0.0, 0.0, 0.198);// twc = twr + Rwr * trc
        Vector<3> twc = twr + rotation * se3IMUfromcam.get_translation();
        camWorld.get_translation()[0] = 0.0;//twc[0]; //twc
        camWorld.get_translation()[1] = 0.0;//twc[1];
        camWorld.get_translation()[2] = twc[2];

        camWorld = camWorld.inverse();//Tcw

        cout<< "TCW INITIALIZED. TWC: " << twc[0]<< ", " << twc[1]<< ", " << twc[2]<<endl;
//        cout<< camWorld.get_rotation().get_matrix()(2,2)<<endl;
        return camWorld;
    }