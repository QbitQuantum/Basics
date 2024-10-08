bool Ig2_Facet_Sphere_ScGeom::go(const shared_ptr<Shape>& cm1,
							const shared_ptr<Shape>& cm2,
							const State& state1,
							const State& state2,
							const Vector3r& shift2,
							const bool& force,
							const shared_ptr<Interaction>& c)
{
	TIMING_DELTAS_START();
	const Se3r& se31=state1.se3; const Se3r& se32=state2.se3;
	Facet*   facet = static_cast<Facet*>(cm1.get());
	/* could be written as (needs to be tested):
	 * Vector3r cl=se31.orientation.Conjugate()*(se32.position-se31.position);
	 */
	Matrix3r facetAxisT=se31.orientation.toRotationMatrix(); 
	Matrix3r facetAxis = facetAxisT.transpose();
	// local orientation
	Vector3r cl = facetAxis*(se32.position + shift2 - se31.position);  // "contact line" in facet-local coords

	//
	// BEGIN everything in facet-local coordinates
	//

	Vector3r normal = facet->normal;
	Real L = normal.dot(cl);
	if (L<0) {normal=-normal; L=-L; }

	Real sphereRadius = static_cast<Sphere*>(cm2.get())->radius;
	if (L>sphereRadius && !c->isReal() && !force) { // no contact, but only if there was no previous contact; ortherwise, the constitutive law is responsible for setting Interaction::isReal=false
		TIMING_DELTAS_CHECKPOINT("Ig2_Facet_Sphere_ScGeom");
		return false;
	}

	Vector3r cp = cl - L*normal;
	const Vector3r* ne = facet->ne;
	
	Real penetrationDepth=0;
	
	Real bm = ne[0].dot(cp);
	int m=0;
	for (int i=1; i<3; ++i)
	{
		Real b=ne[i].dot(cp);
		if (bm<b) {bm=b; m=i;}
	}

	Real sh = sphereRadius*shrinkFactor;
	Real icr = facet->icr-sh;

	if (icr<0)
	{
		LOG_WARN("a radius of a facet's inscribed circle less than zero! So, shrinkFactor is too large and would be reduced to zero.");
		shrinkFactor=0;
		icr = facet->icr;
		sh = 0;
	}


	if (bm<icr) // contact with facet's surface
	{
		penetrationDepth = sphereRadius - L;
		normal.normalize();
	}
	else
	{
		cp = cp + ne[m]*(icr-bm);
		if (cp.dot(ne[(m-1<0)?2:m-1])>icr) // contact with vertex m
//			cp = facet->vertices[m];
			cp = facet->vu[m]*(facet->vl[m]-sh);
		else if (cp.dot(ne[m=(m+1>2)?0:m+1])>icr) // contact with vertex m+1
//			cp = facet->vertices[(m+1>2)?0:m+1];
			cp = facet->vu[m]*(facet->vl[m]-sh);
		normal = cl-cp;
		Real norm=normal.norm(); normal/=norm;
		penetrationDepth = sphereRadius - norm;
	}

	//
	// END everything in facet-local coordinates
	//

	if (penetrationDepth>0 || c->isReal())
	{
		shared_ptr<ScGeom> scm;
		bool isNew = !c->geom;
		if (c->geom)
			scm = YADE_PTR_CAST<ScGeom>(c->geom);
		else
			scm = shared_ptr<ScGeom>(new ScGeom());
	  
		normal = facetAxisT*normal; // in global orientation
		scm->contactPoint = se32.position + shift2 - (sphereRadius-0.5*penetrationDepth)*normal;
		scm->penetrationDepth = penetrationDepth;
		scm->radius1 = 2*sphereRadius;
		scm->radius2 = sphereRadius;
		if (isNew) c->geom = scm;
		scm->precompute(state1,state2,scene,c,normal,isNew,shift2,false/*avoidGranularRatcheting only for sphere-sphere*/);
		TIMING_DELTAS_CHECKPOINT("Ig2_Facet_Sphere_ScGeom");
		return true;
	}
	TIMING_DELTAS_CHECKPOINT("Ig2_Facet_Sphere_ScGeom");
	return false;
}