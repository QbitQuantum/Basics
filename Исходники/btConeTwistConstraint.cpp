// given a twist rotation in constraint space, (pre: cone must already be removed)
// this method computes its corresponding angle and axis.
void btConeTwistConstraint::computeTwistLimitInfo(const btQuaternion& qTwist,
												  btScalar& twistAngle, // out
												  btVector3& vTwistAxis) // out
{
	btQuaternion qMinTwist = qTwist;
	twistAngle = qTwist.getAngle();

	if (twistAngle > SIMD_PI) // long way around. flip quat and recalculate.
	{
		qMinTwist = operator-(qTwist);
		twistAngle = qMinTwist.getAngle();
	}
	if (twistAngle < 0)
	{
		// this should never happen
		int wtf = 0; wtf = wtf;			
	}

	vTwistAxis = btVector3(qMinTwist.x(), qMinTwist.y(), qMinTwist.z());
	if (twistAngle > SIMD_EPSILON)
		vTwistAxis.normalize();
}