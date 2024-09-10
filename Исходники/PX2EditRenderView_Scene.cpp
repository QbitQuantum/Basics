//----------------------------------------------------------------------------
void EditRenderView_Scene::_RoundCamera(float horz, float vert)
{
	Scene *scene = PX2_PROJ.GetScene();
	CameraActor *camActor = scene->GetUseCameraActor();

	if (mViewType == VT_PERSPECTIVE)
	{
		PX2::Object *obj = PX2_SELECTION.GetFirstObject();

		bool hasTarget = false;
		APoint pos;
		Movable *mov = DynamicCast<Movable>(obj);
		if (mov)
		{
			pos = mov->WorldTransform.GetTranslate();
			hasTarget = true;
		}

		if (hasTarget)
		{
			const APoint &camPos = camActor->LocalTransform.GetTranslate();
			AVector rVector;
			AVector dVector;
			AVector uVector;
			camActor->GetRDUVector(rVector, dVector, uVector);

			AVector targetDir = pos - camPos;
			float targetLength = targetDir.Normalize();

			// horz
			HMatrix incrH(AVector::UNIT_Z, -horz*0.1f);
			targetDir = incrH * targetDir;
			dVector = incrH * dVector;
			uVector = incrH * uVector;
			rVector = incrH * rVector;

			HMatrix incrV(rVector, -vert*0.1f);
			targetDir = incrV * targetDir;
			dVector = incrV * dVector;
			uVector = incrV * uVector;

			APoint newPos = pos - targetDir*targetLength;
			camActor->LocalTransform.SetTranslate(newPos);

			AVector::Orthonormalize(dVector, uVector, rVector);
			camActor->LocalTransform.SetRotate(
				HMatrix(rVector, dVector, uVector, AVector::ZERO, true));
		}
	}
}