void DAVA::ShadowVolumeNode::DrawShadow()
{
	Matrix4 prevMatrix = RenderManager::Instance()->GetMatrix(RenderManager::MATRIX_MODELVIEW); 
	Matrix4 meshFinalMatrix = GetWorldTransform() * prevMatrix;
	RenderManager::Instance()->SetMatrix(RenderManager::MATRIX_MODELVIEW, meshFinalMatrix);

	Matrix4 projMatrix = RenderManager::Instance()->GetMatrix(RenderManager::MATRIX_PROJECTION);

	RenderManager::Instance()->SetShader(shader);
	RenderManager::Instance()->SetRenderData(shadowPolygonGroup->renderDataObject);
	RenderManager::Instance()->FlushState();
	RenderManager::Instance()->AttachRenderData();

	Vector3 position = Vector3() * GetWorldTransform();
	Light * light = scene->GetNearestDynamicLight(Light::TYPE_COUNT, position);
	if (light && uniformLightPosition0 != -1)
	{
		Vector3 lightPosition0 = light->GetPosition();
		const Matrix4 & matrix = scene->GetCurrentCamera()->GetMatrix();
		lightPosition0 = lightPosition0 * matrix;

		shader->SetUniformValueByIndex(uniformLightPosition0, lightPosition0);
	}

	if (shadowPolygonGroup->renderDataObject->GetIndexBufferID() != 0)
	{
		RenderManager::Instance()->HWDrawElements(PRIMITIVETYPE_TRIANGLELIST, shadowPolygonGroup->indexCount, EIF_16, 0);
	}
	else
	{
		RenderManager::Instance()->HWDrawElements(PRIMITIVETYPE_TRIANGLELIST, shadowPolygonGroup->indexCount, EIF_16, shadowPolygonGroup->indexArray);
	}

	RenderManager::Instance()->SetMatrix(RenderManager::MATRIX_MODELVIEW, prevMatrix);
}