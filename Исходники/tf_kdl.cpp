 void transformKDLToTF(const KDL::Frame &k, tf::Transform &t)
 {
   t.setOrigin(tf::Vector3(k.p[0], k.p[1], k.p[2]));
   t.setBasis(tf::Matrix3x3(k.M.data[0], k.M.data[1], k.M.data[2],
                          k.M.data[3], k.M.data[4], k.M.data[5],
                          k.M.data[6], k.M.data[7], k.M.data[8]));
 }