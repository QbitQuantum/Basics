ShadowCameraTransform DirectionalLight::CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot) const
{
	Vector3f resultPos = mainCameraPos + mainCameraRot.GetForward() * GetHalfShadowArea();
	Quaternion resultRot = GetTransform().GetTransformedRot();
	
	float worldTexelSize = (GetHalfShadowArea()*2)/((float)(1 << GetShadowInfo().GetShadowMapSizeAsPowerOf2()));
	
	Vector3f lightSpaceCameraPos = resultPos.Rotate(resultRot.Conjugate());
	
	lightSpaceCameraPos.SetX(worldTexelSize * floor(lightSpaceCameraPos.GetX() / worldTexelSize));
	lightSpaceCameraPos.SetY(worldTexelSize * floor(lightSpaceCameraPos.GetY() / worldTexelSize));
	
	resultPos = lightSpaceCameraPos.Rotate(resultRot);
	
	return ShadowCameraTransform(resultPos, resultRot);
}