LightComponent::LightComponent(XMFLOAT4 pos, Light::LIGHTTYPE type, XMFLOAT4 dir, bool isCastingShadow, XMFLOAT4 color, float range, float spotAngle, float attenuation) :
m_range(range),
m_isCastingShadow(isCastingShadow)
{
	m_light.Position = XMLoadFloat4(&pos);
	m_light.Color = XMLoadFloat4(&color);
	m_light.Direction = XMLoadFloat4(&dir);
	XMFLOAT4 misc = XMFLOAT4(spotAngle, attenuation, (float)type, 0.0f);
	m_light.X_SpotAngleAndY_AttenuationAndZ_LightType = XMLoadFloat4(&misc);

}