  void MsgToPoint3D(const TPPLPoint &pt, const cob_3d_mapping_msgs::Shape::ConstPtr& new_message, Eigen::Vector3f &pos, Eigen::Vector3f &normal) {
    if(new_message->params.size()==4) {
      Eigen::Vector3f u,v,origin;
      Eigen::Affine3f transformation;
      normal(0)=new_message->params[0];
      normal(1)=new_message->params[1];
      normal(2)=new_message->params[2];
      origin(0)=new_message->centroid.x;
      origin(1)=new_message->centroid.y;
      origin(2)=new_message->centroid.z;
      //std::cout << "normal: " << normal << std::endl;
      //std::cout << "centroid: " << origin << std::endl;
      v = normal.unitOrthogonal ();
      u = normal.cross (v);
      pcl::getTransformationFromTwoUnitVectorsAndOrigin(v, normal,  origin, transformation);

      transformation=transformation.inverse();

      Eigen::Vector3f p3;
      p3(0)=pt.x;
      p3(1)=pt.y;
      p3(2)=0;
      pos = transformation*p3;
    }
    else if(new_message->params.size()==5) {
      Eigen::Vector2f v,v2,n2;
      v(0)=pt.x;
      v(1)=pt.y;
      v2=v;
      v2(0)*=v2(0);
      v2(1)*=v2(1);
      n2(0)=new_message->params[3];
      n2(1)=new_message->params[4];

      //dummy normal
      normal(0)=new_message->params[0];
      normal(1)=new_message->params[1];
      normal(2)=new_message->params[2];

      Eigen::Vector3f x,y, origin;
      x(0)=1.f;
      y(1)=1.f;
      x(1)=x(2)=y(0)=y(2)=0.f;

      Eigen::Matrix<float,3,2> proj2plane_;
      proj2plane_.col(0)=normal.cross(y);
      proj2plane_.col(1)=normal.cross(x);

      origin(0)=new_message->centroid.x;
      origin(1)=new_message->centroid.y;
      origin(2)=new_message->centroid.z;

      pos = origin+proj2plane_*v + normal*(v2.dot(n2));
      normal += normal*(v).dot(n2);
    }
  }