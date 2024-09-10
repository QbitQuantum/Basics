//helper: computes a facet horizontal and vertical extensions
void ComputeFacetExtensions(CCVector3& N, ccPolyline* facetContour, double& horizExt, double& vertExt)
{
	//horizontal and vertical extensions
	horizExt = vertExt = 0;
	
	CCLib::GenericIndexedCloudPersist* vertCloud = facetContour->getAssociatedCloud();
	if (vertCloud)
	{
		//oriRotMat.applyRotation(N); //DGM: oriRotMat is only for display!
		//we assume that at this point the "up" direction is always (0,0,1)
		CCVector3 Xf(1,0,0), Yf(0,1,0);
		//we get the horizontal vector on the plane
		CCVector3 D = CCVector3(0,0,1).cross(N);
		if (D.norm2() > ZERO_TOLERANCE) //otherwise the facet is horizontal!
		{
			Yf = D;
			Yf.normalize();
			Xf = N.cross(Yf);
		}

		const CCVector3* G = CCLib::Neighbourhood(vertCloud).getGravityCenter();

		ccBBox box;
		for (unsigned i=0; i<vertCloud->size(); ++i)
		{
			const CCVector3 P = *(vertCloud->getPoint(i)) - *G;
			CCVector3 p( P.dot(Xf), P.dot(Yf), 0 );
			box.add(p);
		}

		vertExt = box.getDiagVec().x;
		horizExt = box.getDiagVec().y;
	}
}