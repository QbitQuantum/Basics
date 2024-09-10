void RendererD3D::UpdateModelPointLight(Vector firstLightPos, Vector secondLightPos)
{
	Vector firstLightOS;
	Vector secondLightOS;
	Matrix modelToWorldTrans;
	Vector camPos = Camera::GetInstance().GetCamEye();
	Vector camPosOS;
		
	//// Get the actor transform
	modelToWorldTrans = Actor::GetInstance().GetActorTransform();
	modelToWorldTrans = modelToWorldTrans.transpose();
	modelToWorldTrans = modelToWorldTrans.inverse();

	// Transform the light positions into the actor Object space
	// then pass on to the shader
	firstLightOS = modelToWorldTrans.transform(firstLightPos);
	secondLightOS = modelToWorldTrans.transform(secondLightPos);
	camPosOS = modelToWorldTrans.transform(camPos);

	D3DXVECTOR4 lightOne;
	lightOne.x = firstLightOS.x;
	lightOne.y = firstLightOS.y;
	lightOne.z = firstLightOS.z;
	lightOne.w = 0.0f;
	
	D3DXVECTOR4 lightTwo;
	lightTwo.x = secondLightOS.x;
	lightTwo.y = secondLightOS.y;
	lightTwo.z = secondLightOS.z;
	lightTwo.w = 0.0f;

	D3DXVECTOR4 camEye;
	camEye.x = camPosOS.x;
	camEye.y = camPosOS.y;
	camEye.z = camPosOS.z;
	camEye.w = 0.0f;

	m_pEffect->SetVector("lightPosOne",&lightOne);
	m_pEffect->SetVector("lightPosTwo",&lightTwo);
	m_pEffect->SetVector("eyePos",&camEye);
}