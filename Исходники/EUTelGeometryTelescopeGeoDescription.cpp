double EUTelGeometryTelescopeGeoDescription::FindRad(Eigen::Vector3d const & startPt, Eigen::Vector3d const & endPt) {

	Eigen::Vector3d track = endPt-startPt;
	double length = track.norm();
	track.normalize();

	double snext;
	Eigen::Vector3d point;
	Eigen::Vector3d direction;
	double epsil = 0.00001;
	double rad    = 0.;
	double propagatedDistance = 0;
	bool reachedEnd = false;

	TGeoMedium* med;
	gGeoManager->InitTrack(startPt(0), startPt(1), startPt(2), track(0), track(1), track(2));
	TGeoNode* nextnode = gGeoManager->GetCurrentNode();

	while(nextnode && !reachedEnd) {
		med = nullptr;
		if (nextnode) med = nextnode->GetVolume()->GetMedium();

		nextnode = gGeoManager->FindNextBoundaryAndStep(length);
		snext  = gGeoManager->GetStep();

		if( propagatedDistance+snext >= length ) {
			snext = length - propagatedDistance;
			reachedEnd = true;
		}
		//snext gets very small at a transition into a next node, in this case we need to manually propagate a small (epsil)
		//step into the direction of propagation. This introduces a small systematic error, depending on the size of epsil as
	    	if(snext < 1.e-8) {
			const double * currDir = gGeoManager->GetCurrentDirection();
			const double * currPt = gGeoManager->GetCurrentPoint();

			direction(0) = currDir[0]; direction(1) = currDir[1]; direction(2) = currDir[2];
			point(0) = currPt[0]; point(1) = currPt[1]; point(2) = currPt[2];

			point = point + epsil*direction;

			gGeoManager->CdTop();
			nextnode = gGeoManager->FindNode(point(0),point(1),point(2));
			snext = epsil;
		}	
		if(med) {
			//ROOT returns the rad length in cm while we use mm, therefore factor of 10
			double radlen = med->GetMaterial()->GetRadLen();
			if (radlen > 1.e-5 && radlen < 1.e10) {
				rad += snext/(radlen*10);
			} 
		}
		propagatedDistance += snext; 
	}
	return rad;   
}