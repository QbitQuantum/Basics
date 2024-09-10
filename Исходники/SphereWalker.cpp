void SphereWalker::move(float dt)
{
	XMVECTOR	perp	  = XMVectorSet(-cosf(angle), sinf(angle), 0,0);
	XMVECTOR incrementalRotation;
	incrementalRotation = XMQuaternionRotationAxis(perp, dt );
	XMStoreFloat4(&qPos, XMQuaternionMultiply(incrementalRotation , XMLoadFloat4(&qPos)));
	
	orientationToPos(qPos, pos);
	
	//Rotate in space
	XMMATRIX globalRotation = XMMatrixRotationQuaternion( XMLoadFloat4(&qPos));
	
	XMMATRIX localRotation;
		XMVECTOR up = XMVectorSet( 0,0,1,0);
		localRotation = XMMatrixRotationAxis(up, -angle);
	XMStoreFloat4x4(&orientation, localRotation * globalRotation);

}