void DebugNode::Draw()
{
	Entity::Draw();
	if (!isDraw)
		return;
	if (verts.size() == 0)
		return;
	
	Matrix4 prevMatrix = RenderManager::Instance()->GetMatrix(RenderManager::MATRIX_MODELVIEW); 
	Matrix4 meshFinalMatrix = GetWorldTransform() * prevMatrix;
    
    RenderManager::Instance()->SetMatrix(RenderManager::MATRIX_MODELVIEW, meshFinalMatrix);	
    RenderManager::Instance()->SetRenderEffect(RenderManager::FLAT_COLOR);

    RenderManager::Instance()->SetRenderData(renderData);
	RenderManager::Instance()->DrawArrays(PRIMITIVETYPE_LINELIST, 0, verts.size()/3);
    
    RenderManager::Instance()->SetMatrix(RenderManager::MATRIX_MODELVIEW, prevMatrix);    
}