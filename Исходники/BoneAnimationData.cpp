DirectX::XMFLOAT4 BoneAnimationData::GetRotationValue(float time)
{
	if(time <= rotationKeys[0].time)
		return rotationKeys[0].val;

	if(time >= rotationKeys[numberOfRotationKeys-1].time)
		return rotationKeys[numberOfRotationKeys-1].val;

	int rIndex;
	for(int i = 0;i < numberOfRotationKeys;i++)
	{
		if(rotationKeys[i].time >= time)
		{
			rIndex = i;
			break;
		}
	}

	float coef = (time - rotationKeys[rIndex-1].time) / (rotationKeys[rIndex].time - rotationKeys[rIndex-1].time);
	DirectX::XMVECTOR v1 = XMLoadFloat4(&rotationKeys[rIndex-1].val);
	DirectX::XMVECTOR v2 = XMLoadFloat4(&rotationKeys[rIndex].val);
	DirectX::XMVECTOR res = DirectX::XMQuaternionNormalize(DirectX::XMQuaternionSlerp(v1,v2,coef));
	DirectX::XMFLOAT4 r;
	DirectX::XMStoreFloat4(&r,res);

	return r;
}