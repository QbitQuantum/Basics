// ------------------------------------------------------------------------------------------------
void CCharacter3D::createInstance (TChar3DPart i, const SCharacter3DSetup::SCharacterPart &part)
{
	if (_Scene == NULL)
	{
		nlwarning ("CCharacter3D::createInstance : no scene setup.");
		return;
	}

	if (!_Instances[i].empty())
		_Scene->deleteInstance (_Instances[i]);

	if ((!part.Name.empty()) && (part.Name != "none.shape"))
		_Instances[i] = _Scene->createInstance (part.Name);

	// if cannot create output some errors
	if (_Instances[i].empty())
	{
		if ((i != Char3DPart_HandRightItem) && (i != Char3DPart_HandLeftItem))
			nlwarning ("CCharacter3D::createInstance : cannot create the instance : %s.", part.Name.c_str());
		return;
	}

	// FX Management

	// Advantage Fx
	if (!_InstancesFx[i].AdvantageFx.empty())
		_Scene->deleteInstance (_InstancesFx[i].AdvantageFx);

	if ((!part.AdvFx.empty()) && (part.AdvFx != "none.shape"))
	{
		_InstancesFx[i].AdvantageFx = _Scene->createInstance (part.AdvFx);
		if (_InstancesFx[i].AdvantageFx.empty())
		{
			nlwarning ("CCharacter3D::createInstance : cannot create the fx : %s.", part.AdvFx.c_str());
		}
		else
		{
			CMatrix mat = _Instances[i].getMatrix();
			mat.invert();
			mat *= _InstancesFx[i].AdvantageFx.getMatrix();
			_InstancesFx[i].AdvantageFx.setTransformMode(UTransformable::DirectMatrix);
			_InstancesFx[i].AdvantageFx.setMatrix(mat);
			_InstancesFx[i].AdvantageFx.parent(_Instances[i]);
		}
	}

	// Static Fx
	uint32 fx;
	for (fx = 0; fx < _InstancesFx[i].StaticFx.size(); ++fx)
		if (!_InstancesFx[i].StaticFx[fx].empty())
			_Scene->deleteInstance(_InstancesFx[i].StaticFx[fx]);
	_InstancesFx[i].StaticFx.clear();

	for (fx = 0; fx < part.StatFxNames.size(); ++fx)
		if ((!part.StatFxNames[fx].empty()) && (part.StatFxNames[fx] != "none.shape") &&
			(!part.StatFxBones[fx].empty()) && (part.StatFxBones[fx] != "none.shape"))
		{
			sint boneID = _Skeleton.getBoneIdByName(part.StatFxBones[fx]);
			if (boneID != -1)
			{
				UInstance instance = _Scene->createInstance(part.StatFxNames[fx]);
				if (!instance.empty())
				{
					instance.setTransformMode(UTransform::DirectMatrix);
					CMatrix mat;
					mat.setPos(part.StatFxOffss[fx]);
					instance.setMatrix(mat);
					_Skeleton.stickObject(instance, boneID);
					_InstancesFx[i].StaticFx.push_back(instance);
				}
				else
				{
					nlwarning("Can't create static fx %s sticked on bone %s", part.StatFxNames[fx].c_str(), part.StatFxBones[fx].c_str());
				}
			}
			else
			{
				nlwarning("Can't find bone %s for static fx %s", part.StatFxBones[fx].c_str(), part.StatFxNames[fx].c_str());
			}
		}
}