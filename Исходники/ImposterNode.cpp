void ImposterNode::UpdateImposter()
{
	Camera * camera = scene->GetCurrentCamera();

	Camera * imposterCamera = new Camera();
	Vector3 cameraPos = camera->GetPosition();

	Entity * child = GetChild(0);
	AABBox3 bbox = child->GetWTMaximumBoundingBoxSlow();
	Vector3 bboxCenter = bbox.GetCenter();

	imposterCamera->Setup(camera->GetFOV(), camera->GetAspect(), camera->GetZNear(), camera->GetZFar());
	imposterCamera->SetTarget(bbox.GetCenter());
	imposterCamera->SetPosition(cameraPos);
	imposterCamera->SetUp(camera->GetUp());
	imposterCamera->SetLeft(camera->GetLeft());

	Rect viewport = RenderManager::Instance()->GetViewport();
	
	const Matrix4 & mvp = imposterCamera->GetUniformProjModelMatrix();

	AABBox3 screenBounds;
	GetOOBBoxScreenCoords(child, mvp, screenBounds);

	Vector4 pv(bboxCenter);
	pv = pv*mvp;
	pv.z = (pv.z/pv.w + 1.f) * 0.5f;
	float32 bboxCenterZ = pv.z;

	Vector2 screenSize = Vector2(screenBounds.max.x-screenBounds.min.x, screenBounds.max.y-screenBounds.min.y);

	Vector3 screenBillboardVertices[4];
	screenBillboardVertices[0] = Vector3(screenBounds.min.x, screenBounds.min.y, screenBounds.min.z);
	screenBillboardVertices[1] = Vector3(screenBounds.max.x, screenBounds.min.y, screenBounds.min.z);
	screenBillboardVertices[2] = Vector3(screenBounds.min.x, screenBounds.max.y, screenBounds.min.z);
	screenBillboardVertices[3] = Vector3(screenBounds.max.x, screenBounds.max.y, screenBounds.min.z);

	center = Vector3();
	Matrix4 invMvp = mvp;
	invMvp.Inverse();
	for(int32 i = 0; i < 4; ++i)
	{
		//unproject
		Vector4 out;
		out.x = 2.f*(screenBillboardVertices[i].x-viewport.x)/viewport.dx-1.f;
		out.y = 2.f*(screenBillboardVertices[i].y-viewport.y)/viewport.dy-1.f;
		out.z = 2.f*screenBillboardVertices[i].z-1.f;
		out.w = 1.f;

		out = out*invMvp;
		DVASSERT(out.w != 0.f);

		out.x /= out.w;
		out.y /= out.w;
		out.z /= out.w;

		imposterVertices[i] = Vector3(out.x, out.y, out.z);
		center += imposterVertices[i];
	}
	center /= 4.f;


	//draw
	RecreateFbo(screenSize);
	//Logger::Info("%f, %f", screenSize.x, screenSize.y);
	if(!block)
	{
		return;
	}

	direction = camera->GetPosition()-center;
	direction.Normalize();

	distanceSquaredToCamera = (center-cameraPos).SquareLength();

	float32 nearPlane = sqrtf(distanceSquaredToCamera);
	//float32 farPlane = nearPlane + (bbox.max.z-bbox.min.z);
	float32 w = (imposterVertices[1]-imposterVertices[0]).Length();
	float32 h = (imposterVertices[2]-imposterVertices[0]).Length();
	
	//TODO: calculate instead of +50
	imposterCamera->Setup(-w/2.f, w/2.f, -h/2.f, h/2.f, nearPlane, nearPlane+50.f);

	Rect oldViewport = RenderManager::Instance()->GetViewport();
	
	//Texture * target = fbo->GetTexture();

	RenderManager::Instance()->AppendState(RenderState::STATE_SCISSOR_TEST);
	RenderManager::Instance()->State()->SetScissorRect(Rect(block->offset.x, block->offset.y, block->size.dx, block->size.dy));
	RenderManager::Instance()->FlushState();
	//TODO: use one "clear" function instead of two
	//if(block->size.x == 512.f)
	//{
	//	RenderManager::Instance()->ClearWithColor(0.f, .8f, 0.f, 1.f);
	//}
	//else if(block->size.x == 256.f)
	//{
	//	RenderManager::Instance()->ClearWithColor(0.f, .3f, 0.f, 1.f);
	//}
	//else if(block->size.x == 128.f)
	//{
	//	RenderManager::Instance()->ClearWithColor(.3f, .3f, 0.f, 1.f);
	//}
	//else
	//{
	//	RenderManager::Instance()->ClearWithColor(.3f, 0.f, 0.f, 1.f);
	//}
    
	RenderManager::Instance()->ClearWithColor(.0f, .0f, 0.f, .0f);
	RenderManager::Instance()->ClearDepthBuffer();
	RenderManager::Instance()->RemoveState(RenderState::STATE_SCISSOR_TEST);

	RenderManager::Instance()->SetViewport(Rect(block->offset.x, block->offset.y, block->size.dx, block->size.dy), true);


	imposterCamera->SetTarget(center);
	imposterCamera->Set();

	//TODO: remove this call
	HierarchicalRemoveCull(child);
	RenderManager::Instance()->FlushState();
	child->Draw();

	RenderManager::Instance()->SetViewport(oldViewport, true);

	isReady = true;
	state = STATE_IMPOSTER;

	//unproject
	screenBillboardVertices[0] = Vector3(screenBounds.min.x, screenBounds.min.y, bboxCenterZ);
	screenBillboardVertices[1] = Vector3(screenBounds.max.x, screenBounds.min.y, bboxCenterZ);
	screenBillboardVertices[2] = Vector3(screenBounds.min.x, screenBounds.max.y, bboxCenterZ);
	screenBillboardVertices[3] = Vector3(screenBounds.max.x, screenBounds.max.y, bboxCenterZ);
	for(int32 i = 0; i < 4; ++i)
	{
		//unproject
		Vector4 out;
		out.x = 2.f*(screenBillboardVertices[i].x-viewport.x)/viewport.dx-1.f;
		out.y = 2.f*(screenBillboardVertices[i].y-viewport.y)/viewport.dy-1.f;
		out.z = 2.f*screenBillboardVertices[i].z-1.f;
		out.w = 1.f;

		out = out*invMvp;
		DVASSERT(out.w != 0.f);

		out.x /= out.w;
		out.y /= out.w;
		out.z /= out.w;

		imposterVertices[i] = Vector3(out.x, out.y, out.z);
	}

	SafeRelease(imposterCamera);

	ClearGeometry();
	CreateGeometry();
}