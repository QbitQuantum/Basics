//----------------------------------------------------------------------------
void EditRenderView_PreView::SetObject(PX2::Object *obj)
{
	Texture2D *d2Tex = DynamicCast<Texture2D>(obj);
	Movable *mov = DynamicCast<Movable>(obj);
	if (d2Tex)
	{
		mPreViewType = PVT_TEXTURE;

		const SelectResData &data = PX2_EDIT.GetSelectedResource();
		SelectResData::SelectResType selectResType = data.GetSelectResType();

		std::string texStr = "";

		if (selectResType == SelectResData::RT_NORMAL)
		{
			mUIPicBox->SetTexture(data.ResPathname);

			Texture2D *tex2D = DynamicCast<Texture2D>(PX2_RM.BlockLoad(data.ResPathname));
			if (tex2D)
			{
				texStr = "width:" + StringHelp::IntToString((int)tex2D->GetWidth()) + " "
					+ "height:" + StringHelp::IntToString((int)tex2D->GetHeight()) + " ";
			}
		}
		else if (selectResType == SelectResData::RT_TEXPACKELEMENT)
		{
			PX2_RM.AddTexPack(data.ResPathname);
			const TexPackElement &texPackEle = PX2_RM.GetTexPackElement(
				data.ResPathname, data.EleName);
			if (texPackEle.IsValid())
			{
				mUIPicBox->SetTexture(data.ResPathname, data.EleName);
				mUIPicBox->SetSize((float)texPackEle.W, (float)texPackEle.H);

				texStr = "width: " + StringHelp::IntToString(texPackEle.W) + "  " + "height: " + StringHelp::IntToString(texPackEle.H) + "  ";
			}
		}
		mUIText->SetText(texStr);

		_ReSizeTexture();
	}
	else if (mov)
	{
		mPreViewType = PVT_MODEL;

		mUIText->SetText("");

		EnvirParamPtr beforeParam = PX2_GR.GetCurEnvirParam();
		PX2_GR.SetCurEnvirParam(mModelScene->GetEnvirParam());

		mModeActor->DetachAllChildren();
		mModelMovable = (Movable*)(mov->Copy(""));
		Node::TravelExecute(mModelMovable, _ModePreViewTravelExecuteFun);
		mModeActor->AttachChild(mModelMovable);
		mModelMovable->ResetPlay();
		mModeActor->Update(GetTimeInSeconds(), 0.0f, false);
		mModelCameraActor->ResetPlay();

		const APoint &boundCenter = mModelMovable->WorldBound.GetCenter();
		float boundRadius = mModelMovable->WorldBound.GetRadius();

		APoint camPos = boundCenter + AVector(-boundRadius*2.5f, -boundRadius*2.5f, boundRadius*1.5f);
		AVector dir = boundCenter - camPos;

		if (boundRadius > 0.0f)
		{
			dir.Normalize();
			AVector up = AVector(Float3(0.0f, 0.0f, 1.0f));
			AVector right = dir.Cross(up);
			right.Normalize();
			up = right.Cross(dir);
			up.Normalize();
			AVector::Orthonormalize(dir, up, right);

			mModelCameraActor->GetCameraNode()->LocalTransform.SetRotate(HMatrix(right, dir, up, AVector::ZERO, true));
			mModelCameraActor->GetCameraNode()->LocalTransform.SetTranslate(camPos);
		}

		PX2_GR.SetCurEnvirParam(beforeParam);
	}
	else
	{
		mPreViewType = PVT_NONE;
	}
}