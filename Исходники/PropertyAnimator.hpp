 virtual Matrix4 interp (const Matrix4 &src,const Matrix4 &dst, DTfloat t) {
     return Matrix4( Matrix3(Quaternion::slerp(Quaternion(src.orientation()), Quaternion(dst.orientation()), t)),
                     src.translation() + (dst.translation()-src.translation()) * t);
 }