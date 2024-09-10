XMVECTOR HydraManager::getRotation(int controllerIndex) const
{
	if (sixenseIsControllerEnabled(controllerIndex))
	{
		XMVECTOR axis;
		float angle;

		XMQuaternionToAxisAngle(&axis, &angle, XMLoadFloat4(&XMFLOAT4(&mAcd.controllers[controllerIndex].rot_quat[0])));

		axis = XMVectorSet(-XMVectorGetX(axis), XMVectorGetY(axis), -XMVectorGetZ(axis), 0.0f);

		XMVECTOR rotationQuat = XMQuaternionRotationAxis(axis, angle);

		return rotationQuat;
	}
	
	return XMQuaternionIdentity();
}