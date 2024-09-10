	vector KinectMeshAnimator::GetSkeletonOrientation(NUI_SKELETON_DATA& skeleton, int index1, int index2)
	{
		vector orientation;
		Joint* joint1 = bindings[index1];
		Joint* joint2 = bindings[index2];
		if (!joint1 || !joint2) return XMVectorSet(0.0, 1.0, 0.0, 0.0);

		// INVERT Z
		orientation = XMVectorSet(	skeleton.SkeletonPositions[index2].x - skeleton.SkeletonPositions[index1].x,
									skeleton.SkeletonPositions[index2].y - skeleton.SkeletonPositions[index1].y,
									skeleton.SkeletonPositions[index1].z - skeleton.SkeletonPositions[index2].z,
									0.0);

		vector bindOrientation = bindOrientations[index1];
		vector axis = XMVector3Normalize(XMVector3Cross(bindOrientation, orientation));

		if (XMVector3Equal(axis, XMVectorZero()))
			return XMVectorSet(0.0, 1.0, 0.0, 0.0);

		float angle;
		XMStoreFloat(&angle, XMVector3Dot(bindOrientation, orientation));
		angle = acos(angle);
		return XMQuaternionRotationAxis(axis, angle);
	}