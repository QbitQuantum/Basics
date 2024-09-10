 // Inverse
 Pose3 inverse() const
 {
   return Pose3(_rotation.transpose(),  -(_rotation * _center));
 }