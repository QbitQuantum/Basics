void TransformerSkeleton::setupUnopenedRotations(bone *node,
	Quat origCumulParent, Vec3f origCumulPosition, Vec3f cumulPosition, Quat unfoldCumulParent){

	if (node == nullptr){
		return;
	}

	if (node->parent){
		TransformerBone *tBone = tBoneArray[node->m_index];
		ConnectingBone *cBone = tBone->m_connectingParent;

		// Connecting bone
		cBone->m_unfoldCoord = Vec3f(0, 0, tBone->m_parent->m_length);	// same as fold coord

		Vec3f bpPos = node->m_posCoord - cBone->m_unfoldCoord;
		cBone->m_unfoldedLength = sqrt(bpPos[0] * bpPos[0] + bpPos[1] * bpPos[1] + bpPos[2] * bpPos[2]);

		float xDist = bpPos[0];
		float yDist = bpPos[1];
		float zDist = bpPos[2];

		double ax = 0.0;
		double zero = 1.0e-3;

		// Remove zero errors
		if (xDist == 0){
			xDist = zero;
		}
		if (yDist == 0){
			yDist = zero;
		}
		if (zDist == 0){
			zDist = zero;
		}

		float cBoneTempLength = cBone->m_unfoldedLength;
		if (cBoneTempLength == 0){
			cBoneTempLength = zero;
		}

		ax = 57.2957795*acos(zDist / cBoneTempLength);
		if (zDist <= 0.0){
			ax = -ax;
		}
//		cprintf("ax: %f\n", ax);

		if (ax == 0){
			cBone->m_unfoldAngle = Vec4f(0, 0, 0, 1);
			cBone->m_unfoldQuat = Quat();
		}
		else {
			float rx = -yDist*zDist;
			float ry = xDist*zDist;

			// Rotate about rotation vector
			cBone->m_unfoldAngle = Vec4f(ax, rx, ry, 0);
			cBone->m_unfoldQuat.axisToQuat(Vec3d(rx, ry, 0), ax*3.142 / 180);
		}
		cBone->m_unfoldQuat = cBone->m_foldQuat.inverse() * cBone->m_unfoldQuat;
		cBone->m_unfoldQuat.normalize();
		Vec3d axis2;	double angle2;
		cBone->m_unfoldQuat.quatToAxis(axis2, angle2);
		cBone->m_unfoldAngle = Vec4f(angle2 * 180 / 3.142, axis2[0], axis2[1], axis2[2]);

		unfoldCumulParent = unfoldCumulParent * cBone->m_foldQuat * cBone->m_unfoldQuat * tBone->m_foldQuat;

		// Actual bone mesh			
		tBone->m_unfoldCoord = Vec3f(0, 0, cBone->m_unfoldedLength);

		origCumulParent = origCumulParent * Quat::createQuaterFromEuler(node->m_angle*3.142 / 180);


		tBone->m_unfoldQuat = unfoldCumulParent.inverse() * origCumulParent;
		tBone->m_unfoldQuat.normalize();
		Vec3d axis;	double angle;
		tBone->m_unfoldQuat.quatToAxis(axis, angle);
		tBone->m_unfoldAngle = Vec4f(angle * 180 / 3.142, axis[0], axis[1], axis[2]);

//		cprintf("tbone unfold angle: %f %f %f %f\n", tBone->m_unfoldAngle[0], tBone->m_unfoldAngle[1],
//			tBone->m_unfoldAngle[2], tBone->m_unfoldAngle[3]);
		
		unfoldCumulParent = unfoldCumulParent * tBone->m_unfoldQuat;
	}
	else {
		// Root bone 
		transformerRootBone->m_unfoldQuat = transformerRootBone->m_foldQuat.inverse();
		transformerRootBone->m_unfoldQuat.normalize();

		Vec3d axis;	double angle;
		transformerRootBone->m_unfoldQuat.quatToAxis(axis, angle);
		transformerRootBone->m_unfoldAngle = Vec4f(angle * 180 / 3.142, axis[0], axis[1], axis[2]);
		transformerRootBone->m_unfoldCoord = transformerRootBone->m_foldCoord;
		
		origCumulParent = Quat::createQuaterFromEuler(node->m_angle*3.142 / 180);
		origCumulPosition = transformerRootBone->m_unfoldCoord;
		cumulPosition = transformerRootBone->m_unfoldCoord;
		unfoldCumulParent = transformerRootBone->m_foldQuat * transformerRootBone->m_unfoldQuat;
	}

	for (size_t i = 0; i < node->child.size(); i++){
		setupUnopenedRotations(node->child[i], origCumulParent, origCumulPosition, cumulPosition, unfoldCumulParent);
	}
}