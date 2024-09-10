void GJointRevolute::update_short()
{
	if ( bReversed ) {
		T = SE3(Exp(-axis*coordinate.q), Vec3(0,0,0));
		inv_T = SE3(~T.GetRotation());
		S[0] = -axis[0]; S[1] = -axis[1]; S[2] = -axis[2];
	} else {
		T = SE3(Exp(axis*coordinate.q), Vec3(0,0,0));
		inv_T = SE3(~T.GetRotation());
		S[0] = axis[0]; S[1] = axis[1]; S[2] = axis[2];
	}
}