void PlayerCollisionImage::buildImageTransform(SimCollisionImage* image,
	CollisionSurfaceList* list,TMat3F* mat)
{
	// Transform that goes from image space into the local space.
	//
	TMat3F &rootDelta = shapeInst->fRootDeltaTransform;
	if (rootDelta.flags & (TMat3F::Matrix_HasRotation |
		TMat3F::Matrix_HasTranslation | TMat3F::Matrix_HasScale))
	{
		// Since this shape has an animation transform, we need
		// to adjust the collision surface transforms.
		TMat3F tmp = list->tLocal;
		m_mul(rootDelta,tmp,&list->tLocal);
		m_mul(rootDelta,transform,&list->tWorld);
	}
	TMat3F wta = list->tWorld;
	wta.inverse();
	m_mul(image->transform,wta,mat);
}	