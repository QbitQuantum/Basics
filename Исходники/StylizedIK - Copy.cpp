void RelativeEulerAngleDecoder::Decode(array_view<DirectX::Quaternion> rots, const VectorType & x)
{
	int n = rots.size();

	Eigen::Vector4f qs;
	XMVECTOR q, qb;
	qs.setZero();
	for (int i = 0; i < n; i++)
	{
		qs.segment<3>(0) = x.segment<3>(i * 3).cast<float>();
		q = XMLoadFloat4A(qs.data());
		q = XMQuaternionRotationRollPitchYawFromVector(q); // revert the log map
		qb = XMLoadA(bases[i]);
		q = XMQuaternionMultiply(qb, q);
		XMStoreA(rots[i], q);
	}
}