Rotation Rotation::Rot(const Vector& rotaxis,double angle) {
    // The formula is
    // V.(V.tr) + st*[V x] + ct*(I-V.(V.tr))
    // can be found by multiplying it with an arbitrary vector p
    // and noting that this vector is rotated.
    Vector rotvec = rotaxis;
	rotvec.Normalize();
	return Rotation::Rot2(rotvec,angle);
}