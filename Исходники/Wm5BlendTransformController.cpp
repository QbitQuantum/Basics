//----------------------------------------------------------------------------
bool BlendTransformController::Update (double applicationTime)
{
	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	mController0->Update(applicationTime);
	mController1->Update(applicationTime);

	const Transform& xfrm0 = mController0->GetTransform();
	const Transform& xfrm1 = mController1->GetTransform();
	float oneMinusWeight = 1.0f - mWeight;

	// Arithmetic blend of translations.
	const APoint& trn0 = xfrm0.GetTranslate();
	const APoint& trn1 = xfrm1.GetTranslate();
	APoint blendTrn = oneMinusWeight*trn0 + mWeight*trn1;
	mLocalTransform.SetTranslate(blendTrn);

	if (mRSMatrices)
	{
		const HMatrix& rot0 = xfrm0.GetRotate();
		const HMatrix& rot1 = xfrm1.GetRotate();

		HQuaternion quat0(rot0), quat1(rot1);
		if (quat0.Dot(quat1) < 0.0f)
		{
			quat1 = -quat1;
		}

		APoint sca0 = xfrm0.GetScale();
		APoint sca1 = xfrm1.GetScale();
		HMatrix blendRot;
		HQuaternion blendQuat;
		APoint blendSca;

		if (mGeometricRotation)
		{
			blendQuat.Slerp(mWeight, quat0, quat1);
		}
		else
		{
			blendQuat = oneMinusWeight*quat0 + mWeight*quat1;
			blendQuat.Normalize();
		}
		blendQuat.ToRotationMatrix(blendRot);
		mLocalTransform.SetRotate(blendRot);

		if (mGeometricScale)
		{
			for (int i = 0; i < 3; ++i)
			{
				float s0 = sca0[i];
				float s1 = sca1[i];
				if (s0 != 0.0f && s1 != 0.0f)
				{
					float sign0 = Mathf::Sign(s0);
					float sign1 = Mathf::Sign(s1);
					s0 = Mathf::FAbs(s0);
					s1 = Mathf::FAbs(s1);
					float pow0 = Mathf::Pow(s0, oneMinusWeight);
					float pow1 = Mathf::Pow(s1, mWeight);
					blendSca[i] = sign0*sign1*pow0*pow1;
				}
				else
				{
					blendSca[i] = 0.0f;
				}
			}
		}
		else
		{
			blendSca = oneMinusWeight*sca0 + mWeight*sca1;
		}
		mLocalTransform.SetScale(blendSca);
	}
	else
	{
		// Arithemtic blend of matrices.
		const HMatrix& mat0 = xfrm0.GetMatrix();
		const HMatrix& mat1 = xfrm1.GetMatrix();
		HMatrix blendMat = oneMinusWeight*mat0 + mWeight*mat1;
		mLocalTransform.SetMatrix(blendMat);
	}

	Spatial* spatial = StaticCast<Spatial>(mObject);
	spatial->LocalTransform = mLocalTransform;
	return true;
}