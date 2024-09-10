 void transformEigenToTF(const Eigen::Affine3d &e, tf::Transform &t)
 {
   t.setOrigin(tf::Vector3( e.matrix()(0,3), e.matrix()(1,3), e.matrix()(2,3)));
   t.setBasis(tf::Matrix3x3(e.matrix()(0,0), e.matrix()(0,1),e.matrix()(0,2),
                            e.matrix()(1,0), e.matrix()(1,1),e.matrix()(1,2),
                            e.matrix()(2,0), e.matrix()(2,1),e.matrix()(2,2)));
 }