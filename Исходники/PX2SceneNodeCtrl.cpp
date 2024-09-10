//----------------------------------------------------------------------------
void SceneNodeCtrl::OnMotion(bool leftDown, RenderStep *renderStep,
	PX2::APoint posNow, PX2::APoint posBefore)
{
	PX2_UNUSED(leftDown);
	PX2_UNUSED(renderStep);

	Renderer *renderer = renderStep->GetRenderer();
	Camera *camera = renderStep->GetCamera();

	// 光标移动更新
	if (DT_NONE == mDragType)
	{
		GeoObjFactory factory;

		DragType dt = GetDragType(renderStep, posNow);
		Movable *ctrlMov = 0;
		Float4 colorYellowAlpha = Float4(1.0f, 1.0f, 0.0f, 0.3f);

		if (DT_X == dt)
		{
			ctrlMov = GetCurrentCtrlX();
			factory.UpdateCtrlColor(renderer, ctrlMov, Float4::YELLOW);
		}
		else if (DT_Y == dt)
		{
			ctrlMov = GetCurrentCtrlY();
			factory.UpdateCtrlColor(renderer, ctrlMov, Float4::YELLOW);
		}
		else if (DT_Z == dt)
		{
			ctrlMov = GetCurrentCtrlZ();
			factory.UpdateCtrlColor(renderer, ctrlMov, Float4::YELLOW);
		}
		else if (DT_XY == dt)
		{
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXY(), colorYellowAlpha);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlYZ(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXZ(), Float4::ZERO);
		}
		else if (DT_YZ == dt)
		{
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlYZ(), colorYellowAlpha);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXY(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXZ(), Float4::ZERO);
		}
		else if (DT_XZ == dt)
		{
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXZ(), colorYellowAlpha);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXY(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlYZ(), Float4::ZERO);
		}
		else if (DT_XYZ == dt)
		{
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXYZ(), Float4::YELLOW);
		}
		else if (DT_NONE == dt)
		{
			factory.UpdateCtrlColor(renderer, GetCurrentCtrlX(), Float4::RED);
			factory.UpdateCtrlColor(renderer, GetCurrentCtrlY(), Float4::GREEN);
			factory.UpdateCtrlColor(renderer, GetCurrentCtrlZ(), Float4::BLUE);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXY(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlYZ(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXZ(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXYZ(), Float4::WHITE);
		}

		if (DT_NONE == dt)
		{
			Event *ent = EditEventSpace::CreateEventX(EditEventSpace::SceneNodeDrag);
			ent->SetData<int>(0);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
		else
		{
			Event *ent = EditEventSpace::CreateEventX(EditEventSpace::SceneNodeDrag);
			ent->SetData<int>(1);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
	}

	if (DT_NONE == mDragType) return;
	else
	{
		Event *ent = EditEventSpace::CreateEventX(EditEventSpace::SceneNodeDrag);
		ent->SetData<int>(1);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}

	int numObjs = PX2_SELECTION.GetNumObjects();
	if (0 == numObjs) 
		return;

	// get pickPoint with the plane
	TriMesh *meshHelp = PX2_GR.GetXYPlane();
	if (DT_X == mDragType)
	{
		if (LT_PERSPECTIVE == mLookType || LT_TOP == mLookType)
			meshHelp = PX2_GR.GetXYPlane();
		else if (LT_FRONT == mLookType)
			meshHelp = PX2_GR.GetXZPlane();
	}
	else if (DT_Y == mDragType)
	{
		meshHelp = PX2_GR.GetXYPlane();
	}
	else if (DT_Z == mDragType)
	{
		AVector cameraDir = camera->GetDVector();
		cameraDir.Normalize();
		float dotVal = Mathf::FAbs(cameraDir.Dot(AVector::UNIT_X));
		if (dotVal > 0.7f)
		{
			meshHelp = PX2_GR.GetYZPlane();
		}
		else
		{
			meshHelp = PX2_GR.GetXZPlane();
		}
	}
	else if (DT_XY == mDragType)
	{
		meshHelp = PX2_GR.GetXYPlane();
	}
	else if (DT_YZ == mDragType)
	{
		meshHelp = PX2_GR.GetYZPlane();
	}
	else if (DT_XZ == mDragType)
	{
		meshHelp = PX2_GR.GetXZPlane();
	}
	else if (DT_XYZ == mDragType)
	{
		meshHelp = PX2_GR.GetXYPlane();
	}
	meshHelp->WorldTransform.SetTranslate(GetPosition());

	// get pick ray
	APoint rayOrigin_Now;
	AVector rayDir_Now;
	renderStep->GetPickRay(posNow.X(), posNow.Z(), rayOrigin_Now, rayDir_Now);

	APoint rayOrigin_Before;
	AVector rayDir_Before;
	renderStep->GetPickRay(posBefore.X(), posBefore.Z(), rayOrigin_Before, rayDir_Before);

	// pick
	Picker pickerNow;
	pickerNow.Execute(meshHelp, rayOrigin_Now, rayDir_Now, 0.0f, Mathf::MAX_REAL);
	float lengthNow = pickerNow.GetClosestToZero().T;
	APoint positionNow(rayOrigin_Now + rayDir_Now*lengthNow);

	Picker pickerOrigin;
	pickerOrigin.Execute(meshHelp, rayOrigin_Before, rayDir_Before, 0.0f, Mathf::MAX_REAL);
	float lengthBefore = pickerOrigin.GetClosestToZero().T;
	APoint positionBefore(rayOrigin_Before + rayDir_Before*lengthBefore);

	if (pickerNow.Records.empty() || pickerOrigin.Records.empty()) return;

	AVector transMoved = positionNow - positionBefore;
	AVector transDir = transMoved;
	transDir.Normalize();

	float transValue = 0.0f;
	float transValue1 = 0.0f;
	AVector transVec;
	AVector rolateVec;

	AVector dirX = mDirX;
	AVector dirY = mDirY;
	AVector dirZ = mDirZ;

	if (DT_X == mDragType)
	{
		transValue = transMoved.Dot(dirX);
		transVec = dirX * transValue;

		rolateVec.X() = transMoved.Length() *(1.0f - Mathf::FAbs(transDir.Dot(dirX)));

		AVector vec = transDir.Cross(dirX);
		rolateVec.X() *= Mathf::Sign(vec.Z());
	}
	else if (DT_Y == mDragType)
	{
		transValue = transMoved.Dot(dirY);
		transVec = dirY * transValue;

		rolateVec.Y() = transMoved.Length() *(1.0f - Mathf::FAbs(transDir.Dot(dirY)));

		AVector vec = transDir.Cross(dirY);
		rolateVec.Y() *= Mathf::Sign(vec.Z());
	}
	else if (DT_Z == mDragType)
	{
		transValue = transMoved.Dot(dirZ);
		transVec = dirZ * transValue;

		rolateVec.Z() = transMoved.Length() *(1.0f - Mathf::FAbs(transDir.Dot(dirZ)));

		rolateVec.Z() *= Mathf::Sign(posNow.X() - posBefore.X());
	}
	else if (DT_XY == mDragType)
	{
		transValue = transMoved.Dot(dirX);
		transValue1 = transMoved.Dot(dirY);
		transVec = dirX * transValue + dirY * transValue1;
	}
	else if (DT_YZ == mDragType)
	{
		transValue = transMoved.Dot(dirY);
		transValue1 = transMoved.Dot(dirZ);
		transVec = dirY * transValue + dirZ * transValue1;
	}
	else if (DT_XZ == mDragType)
	{
		transValue = transMoved.Dot(dirX);
		transValue1 = transMoved.Dot(dirZ);
		transVec = dirX * transValue + dirZ * transValue1;
	}
	else if (DT_XYZ == mDragType)
	{
		float transValue0 = Mathf::FAbs(transMoved.Dot(dirX));
		float transValue1 = Mathf::FAbs(transMoved.Dot(dirY));
		float transValue2 = Mathf::FAbs(transMoved.Dot(dirZ));

		float trans = (transValue0 + transValue1 + transValue2) / 3.0f;
		trans *= Mathf::Sign(transMoved.Y());

		transVec = AVector(trans, trans, trans);
	}

	if (CT_SCALE == mCtrlType)
		transVec *= 0.5f;

	HMatrix parentMat = mParentRotateMat.Inverse();
	transVec = parentMat * transVec;

	if (CT_TRANSLATE == mCtrlType)
	{
		PX2_SELECTION.Translate(transVec);

		UpdateCtrlTrans();
	}
	else if (CT_ROLATE == mCtrlType)
	{
		PX2_SELECTION.AddRolate(rolateVec);
	}
	else if (CT_SCALE == mCtrlType)
	{
		if (DT_XYZ == mDragType)
			PX2_SELECTION.AddScale(transVec);
	}

	Object *obj = PX2_SELECTION.GetFirstObject();
	if (obj)
	{
		Event *ent = EditEventSpace::CreateEventX(
			EditEventSpace::ObjectTransformChanged);
		ent->SetData<Object*>(obj);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}

	mCtrlsGroup->Update(Time::GetTimeInSeconds(), false);
}