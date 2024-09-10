///  Pick marker
//---------------------------------------------------------------------------------------------------------------
void SplineRoad::Pick(Camera* mCamera, Real mx, Real my,  bool bRay, bool bAddH, bool bHide)
{
	iSelPoint = -1;
	//if (vMarkNodes.size() != getNumPoints())
	//	return;  // assert
	
	Ray ray = mCamera->getCameraToViewportRay(mx,my);  // 0..1
	const Vector3& pos = mCamera->getDerivedPosition(), dir = ray.getDirection();
	const Plane& pl = mCamera->getFrustumPlane(FRUSTUM_PLANE_NEAR);
	Real plDist = FLT_MAX;
	const Real sphR = 2.4f;  //par

	for (int i=0; i < (int)getNumPoints(); ++i)
	{
		// ray to sphere dist
		const Vector3& posSph = getPos(i);
		const Vector3 ps = pos - posSph;
		Vector3 crs = ps.crossProduct(dir);
		Real dist = crs.length() / dir.length();
		// dist to camera
		Real plD = pl.getDistance(posSph);

		if (dist < sphR &&
			plD > 0 && plD < plDist)
		{
			plDist = plD;
			iSelPoint = i;
		}
	}
	
	SelectMarker(bHide);
	//  hide/show all markers
	int iHide = bHide ? 1 : 0;
	if (iHide != iOldHide)
	{	iOldHide = iHide;
		for (size_t i=0; i < vMarkNodes.size(); ++i)
			vMarkNodes[i]->setVisible(bAddH);
	}
	
	//  ray terrain hit pos
	if (bRay && ndHit && mTerrain)
	{
		std::pair<bool, Vector3> p = mTerrain->rayIntersects(ray);
		bHitTer = p.first;  //ndHit->setVisible(bHitTer);
		posHit = p.second;
		
		if (bHitTer)
		{
			Vector3 pos = posHit;
			//if (iChosen == -1)  // for new
			if (!newP.onTer && bAddH)
				pos.y = newP.pos.y;
			ndHit->setPosition(pos);
		}
	}
}