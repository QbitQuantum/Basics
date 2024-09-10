bool FireBallParticles::Update(FXMVECTOR newPos, float fireballRadius, float dt, ID3D11DeviceContext* context)
{
	if (!mProperties.isFire || mIsAllParticlesDead)
	{
		return true;
	}

	XMVECTOR nPos = newPos;
	if (mTweenPoints.size() > 0)
	{
		nPos = XMLoadFloat3(&mCurrTweenPoint);
		UpdateCurrentTweenPoint(dt);
	}

	XMFLOAT3 fVel3;
	float pSize;
	bool isParticleStillAlive = false;
	for (int i = 0; i < mFireBallParticles.size(); ++i)
	{
		XMVECTOR pos = XMLoadFloat3(&mFireBallParticles[i].pos);
		XMVECTOR vel = XMLoadFloat3(&mFireBallParticles[i].vel);

		mFireBallParticles[i].age += dt;
		if (mProperties.isOneShot && (mFireBallParticles[i].age >= mFireBallParticles[i].lifetime))
		{
			continue;
		}
		else if (mFireBallParticles[i].age <= mFireBallParticles[i].lifetime)
		{
			isParticleStillAlive = true;
		}
		else if (!mProperties.isOneShot && (mFireBallParticles[i].age >= mFireBallParticles[i].lifetime))
		{
			isParticleStillAlive = true;
			vel = XMVector3Normalize(XMVectorSet(MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), 0.0f)) * fireballRadius;
			XMStoreFloat3(&mFireBallParticles[i].pos, nPos + vel);
			fVel3 = GetVelocity();
			vel = XMVector3Normalize(XMVectorSet(fVel3.x, fVel3.y, fVel3.z, 0.0f));
			float speedMult = GetSpeedMultiplier();
			if (MathHelper::RandF() > 0.50f)
			{
				if (MathHelper::RandF() > 0.50f)
				{
					vel.m128_f32[0] += MathHelper::RandF(-0.4f, 0.4f);
					//vel.m128_f32[0] *= MathHelper::RandF(-0.06f, 0.06f);
					//vel.m128_f32[2] *= MathHelper::RandF(-0.06f, 0.06f);
				}
				else
				{
					vel.m128_f32[2] += MathHelper::RandF(-0.4f, 0.4f);
					//vel.m128_f32[0] *= MathHelper::RandF(-0.06f, 0.06f);
					//vel.m128_f32[2] *= MathHelper::RandF(-0.06f, 0.06f);
				}
			}
			XMStoreFloat3(&mFireBallParticles[i].vel, vel * speedMult);
			pSize = GetSize();
			mFireBallParticles[i].size.x = pSize;
			mFireBallParticles[i].size.y = pSize;
			mFireBallParticles[i].age = 0.0f;
			mFireBallParticles[i].lifetime = GetLifetime();
			pos = XMLoadFloat3(&mFireBallParticles[i].pos);
			vel = XMLoadFloat3(&mFireBallParticles[i].vel);
		}
		if (pos.m128_f32[1] < (nPos.m128_f32[1] + (fireballRadius * 0.60f)))
		{
			XMVECTOR s1Center = nPos;
			float s1Radius = fireballRadius;
			float currOverLap = 0.0f;
			XMVECTOR correction = XMVectorZero();

			XMVECTOR d = s1Center - pos;

			float distance = sqrt((d.m128_f32[0] * d.m128_f32[0]) /*+ (d.m128_f32[1] * d.m128_f32[1])*/ + (d.m128_f32[2] * d.m128_f32[2])); //Magnitude of the difference

			float overLap = s1Radius - distance;

			if (overLap > currOverLap) // Have Collision
			{
				currOverLap = overLap;

				correction = XMVector3Normalize(d) * currOverLap; //correct collision by moving sphere out of box
			}
			pos += correction;
		}
		pos = pos + vel;
		XMStoreFloat3(&mFireBallParticles[i].pos, pos);
	}

	if (isParticleStillAlive)
	{
		UpdateFireBallParticleVB(context);
	}
	else
	{
		mIsAllParticlesDead = true;
		if (mProperties.isOneShot)
		{
			ResetParticles();
		}
	}
	return false;
}