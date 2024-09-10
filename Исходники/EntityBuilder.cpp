const Entity EntityBuilder::CreateHealingLight(const XMFLOAT3 & pos, const XMFLOAT3 & rot, const DirectX::XMFLOAT3 & color, float intensity, float outerAngle, float innerAngle, float range)
{
	Entity ent = _entity.Create();
	_transform->CreateTransform(ent);
	_light->BindSpotLight(ent, color, intensity, outerAngle, innerAngle, range);
	_light->SetAsVolumetric(ent, true);
	_transform->SetPosition(ent, pos);
	_transform->SetRotation(ent, rot);

	float s = range*atanf(outerAngle);
	_transform->SetScale(ent, XMFLOAT3(s, s, range));

	return ent;
}