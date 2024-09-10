//----------------------------------------------------------------------------
void AmbientRegionActor::_UpdateDirLightCamera()
{
	AVector dir = AVector::AnglesToDirection(Mathf::DEG_TO_RAD*mHorAngle,
		Mathf::DEG_TO_RAD*mVerAngle);
	dir.Normalize();

	Scene *scene = DynamicCast<Scene>(GetTopestParent());
	if (scene)
	{
		EnvirParam *envirParam = scene->GetEnvirParam();

		Light *lightDir = envirParam->GetLight_Dir();
		Projector *projector = envirParam->GetLight_Dir_Projector();

		lightDir->Ambient = Float4(mAmbientColor[0], mAmbientColor[1],
			mAmbientColor[2], mIntensity);
		lightDir->Intensity = mIntensity;
		lightDir->Diffuse = Float4(mDiffuseColor[0], mDiffuseColor[1],
			mDiffuseColor[2], 1.0f);
		lightDir->Specular = Float4(mSpecularColor[0], mSpecularColor[1],
			mSpecularColor[2], mSpecularPow);

		float upDot = dir.Dot(-AVector::UNIT_Z);
		if (upDot >= 0.99f)
		{
		}
		else
		{
			AVector upTemp = AVector::UNIT_Z;
			AVector right = dir.UnitCross(upTemp);
			AVector up = right.UnitCross(dir);

			lightDir->DVector = dir;
			lightDir->UVector = up;
			lightDir->RVector = right;

			APoint camPos = mLightCameraLookPosition - dir*mLightCameraLookDistance;
			projector->SetFrame(camPos, lightDir->DVector,
				lightDir->UVector, lightDir->RVector);
		}

		if (!projector->IsPerspective())
		{
			projector->SetFrustum(0.1f, 100.0f,
				-mLightCameraExtent, mLightCameraExtent, -mLightCameraExtent,
				mLightCameraExtent);
		}
		else
		{
			projector->SetFrustum(mLightCameraExtent, 1.0f, 1.0f, 100.0f);
		}
	}
}