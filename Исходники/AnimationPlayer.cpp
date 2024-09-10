void AnimationPlayer::Play(float delta)
{
	//find the appropriate frame
	this->AnimTime += delta * this->AnimRate;
	
	if(this->AnimTime >= this->Animation.second->mDuration)
    {
        this->AnimTime = 0.0f;
		this->CurrentFrame = 0;
    }
	else if(this->AnimTime < 0.0f)
    {
        this->AnimTime = this->Animation.second->mDuration;
		this->CurrentFrame = this->Animation.second->mKeys.size() - 1;
    }

	if(this->AnimTime < 0)
	{
		return; // No time change so don't do anything
	}

	std::size_t prevFrame = this->CurrentFrame;
	if(this->AnimTime < this->Animation.second->mKeys[this->CurrentFrame].mTime)
	{
		do
		{
			this->CurrentFrame -= 1;
		}while(this->AnimTime < this->Animation.second->mKeys[this->CurrentFrame].mTime);
	}
	else if(this->AnimTime > this->Animation.second->mKeys[this->CurrentFrame].mTime)
	{
		do
		{
			this->CurrentFrame += 1;
		}while(this->AnimTime > this->Animation.second->mKeys[this->CurrentFrame].mTime);
	}

	if(prevFrame != this->CurrentFrame)
	{
		this->PreviousFrame = prevFrame;
	}

	if(this->PreviousFrame != this->CurrentFrame)
	{
		float ratio = (this->AnimTime - this->Animation.second->mKeys[this->PreviousFrame].mTime) / 
						(this->Animation.second->mKeys[this->CurrentFrame].mTime - this->Animation.second->mKeys[this->PreviousFrame].mTime);
		
		for(std::size_t i = 0; i < this->CurrentBones.size(); ++i)
		{
			if(this->ChannelMap[i] != -1)
			{
				const cFBXBuffer::JointPose& jntA = this->Animation.second->mKeys[this->PreviousFrame].mBones[this->ChannelMap[i]];
				const cFBXBuffer::JointPose& jntB = this->Animation.second->mKeys[this->CurrentFrame].mBones[this->ChannelMap[i]];

				XMVECTOR lerpedTranslation = XMVectorLerp(XMLoadFloat3(&jntA.translation), XMLoadFloat3(&jntB.translation), ratio);
				XMStoreFloat3(&(this->CurrentBones[i].translation), lerpedTranslation);
				XMVECTOR slerpedRotation = XMQuaternionSlerp(XMLoadFloat4(&jntA.rotation), XMLoadFloat4(&jntB.rotation), ratio);
				XMStoreFloat4(&(this->CurrentBones[i].rotation), slerpedRotation);
				XMVECTOR lerpedScale = XMVectorLerp(XMLoadFloat3(&jntA.scale), XMLoadFloat3(&jntB.scale), ratio);
				XMStoreFloat3(&(this->CurrentBones[i].scale), lerpedScale);
			}
		}
	}

	
	XMMATRIX root = this->CurrentBones[1].GetTransform();
	XMMATRIX modroot = root;
	if(this->PreviousFrame > this->Animation.second->mKeys.size())
    {
        //if we've looped, add on the total root-motion of the animation
        XMVECTOR fdet;
		XMMATRIX invFirstRoot = XMMatrixInverse(&fdet, this->Animation.second->mKeys.back().mBones[1].GetTransform());    
		modroot *= invFirstRoot * this->Animation.second->mKeys.front().mBones[1].GetTransform();
    }

	XMVECTOR det;
	XMMATRIX invPrevRoot = XMMatrixInverse(&det, XMLoadFloat4x4(&mPrevRoot));
	XMMATRIX rootMotion = invPrevRoot * modroot;


	XMVECTOR scale;
	XMVECTOR rotQuat;
	XMVECTOR trans;
	if(XMMatrixDecompose(&scale, &rotQuat, &trans, rootMotion))
	{
		XMStoreFloat3(&mRootTranslation, trans);
		XMStoreFloat4(&mRootRotation, rotQuat);
		if(mRootTranslation.z < -0.1f)
		{
			mRootTranslation.z = mRootTranslation.z;
		}
	}
	
	XMStoreFloat4x4(&mPrevRoot, root);

	CurrentBones[1].translation.x = Animation.second->mKeys[0].mBones[1].translation.x;
	CurrentBones[1].translation.z = Animation.second->mKeys[0].mBones[1].translation.z;
}