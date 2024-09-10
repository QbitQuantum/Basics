 float Transform3D::norm(Transform3D T) {
     float pos_norm = arma::norm(T.translation());
     // return Rotation3D::norm(T.rotation());
     // TODO: how to weight these two?
     return pos_norm + Rotation3D::norm(T.rotation());
 }