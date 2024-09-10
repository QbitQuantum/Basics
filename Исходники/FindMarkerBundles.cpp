//Create a ROS frame out of the known corners of a tag in the weird marker coord frame used by Alvar markers (x right y forward z up)
//p0-->p1 should point in Alvar's pos X direction
//p1-->p2 should point in Alvar's pos Y direction
int makeMasterTransform (const CvPoint3D64f& p0, const CvPoint3D64f& p1,
                         const CvPoint3D64f& p2, const CvPoint3D64f& p3,
                         tf::Transform &retT)
  {
    const tf::Vector3 q0(p0.x, p0.y, p0.z);
    const tf::Vector3 q1(p1.x, p1.y, p1.z);
    const tf::Vector3 q2(p2.x, p2.y, p2.z);
    const tf::Vector3 q3(p3.x, p3.y, p3.z);
  
    // (inverse) matrix with the given properties
    const tf::Vector3 v = (q1-q0).normalized();
    const tf::Vector3 w = (q2-q1).normalized();
    const tf::Vector3 n = v.cross(w);
    tf::Matrix3x3 m(v[0], v[1], v[2], w[0], w[1], w[2], n[0], n[1], n[2]);
    m = m.inverse();
    
    //Translate to quaternion
    if(m.determinant() <= 0)
        return -1;
  
    //Use Eigen for this part instead, because the ROS version of bullet appears to have a bug
    Eigen::Matrix3f eig_m;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            eig_m(i,j) = m[i][j];
        }
    }
    Eigen::Quaternion<float> eig_quat(eig_m);
    
    // Translate back to bullet
    tfScalar ex = eig_quat.x();
    tfScalar ey = eig_quat.y();
    tfScalar ez = eig_quat.z();
    tfScalar ew = eig_quat.w();
    tf::Quaternion quat(ex,ey,ez,ew);
    quat = quat.normalized();
    
    double qx = (q0.x() + q1.x() + q2.x() + q3.x()) / 4.0;
    double qy = (q0.y() + q1.y() + q2.y() + q3.y()) / 4.0;
    double qz = (q0.z() + q1.z() + q2.z() + q3.z()) / 4.0;
    tf::Vector3 origin (qx,qy,qz);
    
    tf::Transform tform (quat, origin);  //transform from master to marker
    retT = tform;
    
    return 0;
  }