    void Edge_V_V_GICPLandmark::linearizeOplus()
    {
      //  std::cout << "START Edge_V_V_GICPLandmark::linearizeOplus() " << std::endl;
      VertexPointXYZ* vp0 = static_cast<VertexPointXYZ*>(_vertices[0]);
      VertexSE3* vp1 = static_cast<VertexSE3*>(_vertices[1]);
      Vector3d p1 = measurement().pos1;

      if (!vp0->fixed())
        {
          _jacobianOplusXi.block<3,3>(0,0) = -Matrix3d::Identity();
        }

      if (!vp1->fixed())
        {
          Matrix3d R1 = vp1->estimate().matrix().topLeftCorner<3,3>();
          _jacobianOplusXj.block<3,3>(0,0) = R1;
          _jacobianOplusXj.block<3,1>(0,3) = R1*dRidx.transpose()*p1;
          _jacobianOplusXj.block<3,1>(0,4) = R1*dRidy.transpose()*p1;
          _jacobianOplusXj.block<3,1>(0,5) = R1*dRidz.transpose()*p1;
        }
    }