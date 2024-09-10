    RigidBodyInertia deVectorize(const Eigen::Matrix<double,10,1> & vec)
    {
        Vector COG;
        if( vec[0] != 0 ) {
            COG = Vector(vec[1],vec[2],vec[3]);

            COG = COG/vec[0];
        } else {
            COG = Vector(0.0,0.0,0.0);
        }

        Vector3d vCOG = Map<Vector3d>(COG.data);


        //In the constructor, the request rotational inertia is the one w.r.t. the COG
        RotationalInertia I_o = devech(vec.tail<6>());
        RotationalInertia I_c;
        Map<Matrix3d>(I_c.data) = Map<Matrix3d>(I_o.data)+
                                        vec[0]*(vCOG*vCOG.transpose()-vCOG.dot(vCOG)*Matrix3d::Identity());


        return RigidBodyInertia(vec[0],COG,I_c);
    }