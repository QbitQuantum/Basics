bool ShapeCollisionImage::checkShape(ShapeCollisionImage * image,
	CollisionSurfaceList * list)
{
	// Sphere against polys in other shape
	m_mul(image->shapeInst->fRootDeltaTransform,
		image->transform,&list->tWorld);
	TMat3F wti = list->tWorld;
	wti.inverse();
	TMat3F mat;
	m_mul(transform,wti,&mat);

	if (!image->shapeInst->collideSphere(image->collisionDetail,
			sphere.center,sphere.radius,&mat,list,
			image->collisionLevel == CollideFaces))
		return false;

	list->tLocal = mat;
	list->tLocal.inverse();
	return true;
}