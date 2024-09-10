void Head::Joint::orientTowards(bool entering, const Math::Vector3d &point, float rate, const Math::Matrix4 &matrix,
	float maxPitch, float maxYaw, float maxRoll, float constrain) {
	float step = g_grim->getPerSecond(rate);
	float yawStep = step;
	float pitchStep = step / 3.0f;
	float rollStep = step / 3.0f;

	if (!_node)
		return;

	// Make sure we have up-to-date world transform matrices computed for the joint nodes of this character.
	_node->_needsUpdate = true;
	ModelNode *p = _node;
	while (p->_parent) {
		p = p->_parent;
		p->_needsUpdate = true;
	}
	p->setMatrix(matrix);
	p->update();

	Math::Vector3d modelFront; // the modeling convention for the forward direction.
	Math::Vector3d modelUp; // the modeling convention for the upward direction.
	Math::Vector3d frontDir; // Character front facing direction vector in world space (global scene coordinate space)

	// the character head coordinate frame is: +Y forward, +Z up, +X right.
	frontDir = Math::Vector3d(_node->_matrix(0,1), _node->_matrix(1,1), _node->_matrix(2,1)); // Look straight ahead. (+Y)
	modelFront = Math::Vector3d(0,1,0);
	modelUp = Math::Vector3d(0,0,1);

	// v is the world space direction vector this character should be looking towards.
	Math::Vector3d targetDir = point - _node->_pivotMatrix.getPosition();
	if (!entering)
		targetDir = frontDir;
	if (targetDir.isZero())
		return;

	targetDir.normalize();

	// The vector v is in world space, so generate the world space lookat matrix for the desired head facing
	// orientation.
	Math::Matrix4 lookAtTM;
	lookAtTM.setToIdentity();
	const Math::Vector3d worldUp(0,0,1); // The Residual scene convention: +Z is world space up.
	if (Math::Vector3d::dotProduct(targetDir, worldUp) >= 0.98f) // Avoid singularity if trying to look straight up.
		lookAtTM.buildFromTargetDir(modelFront, targetDir, modelUp, -frontDir); // Instead of orienting head towards scene up, orient head towards character "back",
	                                                                // i.e. when you look straight up, your head up vector tilts/arches to point straight backwards.
	else if (Math::Vector3d::dotProduct(targetDir, worldUp) <= -0.98f) // Avoid singularity if trying to look straight down.
		lookAtTM.buildFromTargetDir(modelFront, targetDir, modelUp, frontDir); // Instead of orienting head towards scene down, orient head towards character "front",
																   // i.e. when you look straight down, your head up vector tilts/arches to point straight forwards.
	else
		lookAtTM.buildFromTargetDir(modelFront, targetDir, modelUp, worldUp);
	// The above specifies the world space orientation of this bone, but we need to output
	// the orientation in parent space (as yaw/pitch/roll).

	// Get the coordinate frame in which we need to produce the character head yaw/pitch/roll values.
	Math::Matrix4 parentWorldTM;
	if (_node->_parent)
		parentWorldTM = _node->_parent->_matrix;

	// While we could compute the desired lookat direction directly in the above coordinate frame,
	// it is preferrable to compute the lookat direction with respect to the head orientation in
	// the keyframe animation. This is because the LUA scripts specify the maximum head yaw, pitch and
	// roll values with respect to those keyframe animations. If the lookat was simply computed
	// directly in the space of the parent, we couldn't apply the head maxYaw/Pitch/Roll constraints
	// properly. So, compute the coordinate frame of this bone in the keyframe animation.
	Math::Matrix4 animFrame = _node->_localMatrix;
	parentWorldTM = parentWorldTM * animFrame;
	parentWorldTM.invertAffineOrthonormal();

	// Convert lookAtTM orientation from world space to parent-with-keyframe-animation space.
	lookAtTM = parentWorldTM * lookAtTM;

	// Decompose to yaw-pitch-roll (+Z, +X, +Y).
	// In this space, Yaw is +Z. Pitch is +X. Roll is +Y.
	Math::Angle y, pt, r;
	lookAtTM.getPitchYawRoll(&pt, &y, &r);

	y = y * constrain;
	pt = pt * constrain;
	r = r * constrain;

	// Constrain the maximum head movement, as desired by the game LUA scripts.
	y.clampDegrees(maxYaw);
	pt.clampDegrees(maxPitch);
	r.clampDegrees(maxRoll);

	// Also limit yaw, pitch and roll to make at most a movement as large as the given max step size during this frame.
	// This will produce a slow head-turning animation instead of immediately snapping to the
	// target lookat orientation.
	if (y - _yaw > yawStep)
		y = _yaw + yawStep;
	if (_yaw - y > yawStep)
		y = _yaw - yawStep;

	if (pt - _pitch > pitchStep)
		pt = _pitch + pitchStep;
	if (_pitch - pt > pitchStep)
		pt = _pitch - pitchStep;

	if (r - _roll > rollStep)
		r = _roll + rollStep;
	if (_roll - r > rollStep)
		r = _roll - rollStep;

	// Remember how far we animated the head this frame, and we'll continue from here the next frame.
	_pitch = pt;
	_yaw = y;
	_roll = r;

	// Assemble ypr back to a matrix.
	// This matrix is the head orientation with respect to parent-with-keyframe-animation space.
	lookAtTM.buildFromPitchYawRoll(pt, y, r);

	// What follows is a hack: Since translateObject(ModelNode *node, bool reset) in this file,
	// and GfxOpenGL/GfxTinyGL::drawHierachyNode concatenate transforms incorrectly, by summing up
	// euler angles, do a hack here where we do the proper transform here already, and *subtract off*
	// the YPR scalars from the animYPR scalars to cancel out the values that those pieces of code
	// will later accumulate. After those pieces of code have been fixed, the following lines can
	// be deleted, and this function can simply output the contents of pt, y and r variables above.
	lookAtTM = animFrame * lookAtTM;

	lookAtTM.getPitchYawRoll(&pt, &y, &r);
	_node->_animYaw = y - _node->_yaw;
	_node->_animPitch = pt - _node->_pitch;
	_node->_animRoll = r - _node->_roll;
}