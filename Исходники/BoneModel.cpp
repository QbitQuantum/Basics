XMVECTOR LimitAngle(const XMVECTOR& quat, const XMVECTOR& rotmin, const XMVECTOR& rotmax)
{
	XMVECTOR rot_xyz = GetAngle(quat);
	/*	XMMATRIX mtx = XMMatrixRotationQuaternion(quat);

	//ZYX　Y=-90〜90°Y軸＝ねじり方向
	float rx = -atan2f(XMVectorGetY(mtx.r[2]),XMVectorGetZ(mtx.r[2]));
	float ry = asinf(XMVectorGetX(mtx.r[2]));
	float rz = -atan2f(XMVectorGetX(mtx.r[1]),XMVectorGetX(mtx.r[0]));
	XMVECTOR rot_xyz = {rx,ry,rz,0};
	*rotang_before = rot_xyz;
	*/
	rot_xyz = XMVectorMax(rot_xyz, rotmin);
	rot_xyz = XMVectorMin(rot_xyz, rotmax);
	XMMATRIX mtx = XMMatrixRotationZ(XMVectorGetZ(rot_xyz));
	mtx = XMMatrixMultiply(mtx, XMMatrixRotationY(XMVectorGetY(rot_xyz)));
	mtx = XMMatrixMultiply(mtx, XMMatrixRotationX(XMVectorGetX(rot_xyz)));

	return XMQuaternionRotationMatrix(mtx);
}