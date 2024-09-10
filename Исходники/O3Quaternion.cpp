O3Quaternion O3Quaternion::GetNlerped(scale amount, const O3Quaternion& q1, const O3Quaternion& q2) const {
	double costheta = q1|q2;
	double flip = costheta >= 0; //sign = 1 if no signhack
	costheta = std::abs(costheta); //no abs if no signhack
	
	double c1, c2;
	c1 = 1. - amount;
	c2 = amount;
	
	c2 *= flip;
	O3Quaternion to_return = O3Quaternion(	c1*q1.GetX() + c2*q2.GetX(),
										c1*q1.GetY() + c2*q2.GetY(),
										c1*q1.GetZ() + c2*q2.GetZ(),
										c1*q1.GetW() + c2*q2.GetW()  );
	to_return.Normalize();
	return to_return;
}