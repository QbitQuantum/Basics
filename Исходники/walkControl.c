/* Computes abs(targetHipAngle) for the hip, such that the swing ankle is virtually constrained
 * to move only in the vertical direction, with the distance locked at the target step length */
float getTargetHipAngle(float thStance, float thSwing, float stepLen) {
	float d = stepLen;   // target step length
	float l = PARAM_l;   // robot leg length
	float h = getAnkleJointRelHeight(thStance, thSwing);
	return Acos( 1 - ( d * d + h * h ) / ( 2 * l * l ) );
}