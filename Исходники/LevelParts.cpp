LevelParts::LevelParts() : mLevelPartsPosition(0.0f, 0.0f, 0.0f), mLevelPartsScale(1.0f, 1.0f, 1.0f), mLevelPartsRotation(0.0f, 0.0f, 0.0f, 1.0f), mLevelPartsRotationQuad(0.0f, 0.0f, 0.0f, 0.0f)
{



	///initialize player
	XMVECTOR S = XMLoadFloat3(&mLevelPartsScale);
	XMVECTOR P = XMLoadFloat3(&mLevelPartsPosition);
	XMVECTOR Q = XMLoadFloat4(&mLevelPartsRotationQuad);
	XMVECTOR rot = XMLoadFloat4(&mLevelPartsRotation);
	XMStoreFloat4x4(&mLevelPartsWorld, XMMatrixAffineTransformation(S, rot, Q, P));


	currCharDirection = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
	oldCharDirection = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
	charPosition = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
	LevelPartsForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	LevelPartsRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);


	direction = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);


}