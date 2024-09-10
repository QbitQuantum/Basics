 /**
  * @brief Rotate the map relative to its local frame
  * 
  * @param rotation <a href="http://eigen.tuxfamily.org/dox/group__Geometry__Module.html#ga0d2bd45f1215359f8e7c0d7ab53c4acb" target="_blank">
  * Eigen::Quaterniond</a>
  */
 void rotate(const Eigen::Quaterniond &rotation)
 {
     data_ptr->offset.rotate(rotation.inverse());
 }            