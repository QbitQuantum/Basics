/*
Generic function to compute L3Geom (with colinear points), used for {sphere,facet,wall}+sphere contacts now
*/
void Ig2_Sphere_Sphere_L3Geom::handleSpheresLikeContact(const shared_ptr<Interaction>& I, const State& state1, const State& state2, const Vector3r& shift2, bool is6Dof, const Vector3r& normal, const Vector3r& contPt, Real uN, Real r1, Real r2){
	// create geometry
	if(!I->geom){
		if(is6Dof) I->geom=shared_ptr<L6Geom>(new L6Geom);
		else       I->geom=shared_ptr<L3Geom>(new L3Geom);
		L3Geom& g(I->geom->cast<L3Geom>());
		g.contactPoint=contPt;
		g.refR1=r1; g.refR2=r2;
		g.normal=normal;
		// g.trsf.setFromTwoVectors(Vector3r::UnitX(),g.normal); // quaternion just from the X-axis; does not seem to work for some reason?!
		const Vector3r& locX(g.normal);
		// initial local y-axis orientation, in the xz or xy plane, depending on which component is larger to avoid singularities
		Vector3r locY=normal.cross(abs(normal[1])<abs(normal[2])?Vector3r::UnitY():Vector3r::UnitZ()); locY-=locX*locY.dot(locX); locY.normalize();
		Vector3r locZ=normal.cross(locY);
		#ifdef L3_TRSF_QUATERNION
			Matrix3r trsf; trsf.row(0)=locX; trsf.row(1)=locY; trsf.row(2)=locZ;
			g.trsf=Quaternionr(trsf); // from transformation matrix
		#else
			g.trsf.row(0)=locX; g.trsf.row(1)=locY; g.trsf.row(2)=locZ;
		#endif
		g.u=Vector3r(uN,0,0); // zero shear displacement
		if(distFactor<0) g.u0[0]=uN;
		// L6Geom::phi is initialized to Vector3r::Zero() automatically
		//cerr<<"Init trsf=\n"<<g.trsf<<endl<<"locX="<<locX<<", locY="<<locY<<", locZ="<<locZ<<endl;
		return;
	}
	
	// update geometry

	/* motion of the conctact consists in rigid motion (normRotVec, normTwistVec) and mutual motion (relShearDu);
	   they are used to update trsf and u
	*/

	L3Geom& g(I->geom->cast<L3Geom>());
	const Vector3r& currNormal(normal); const Vector3r& prevNormal(g.normal);
	// normal rotation vector, between last steps
	Vector3r normRotVec=prevNormal.cross(currNormal);
	// contrary to what ScGeom::precompute does now (r2486), we take average normal, i.e. .5*(prevNormal+currNormal),
	// so that all terms in the equation are in the previous mid-step
	// the re-normalization might not be necessary for very small increments, but better do it
	Vector3r avgNormal=(approxMask&APPROX_NO_MID_NORMAL) ? prevNormal : .5*(prevNormal+currNormal);
	if(!(approxMask&APPROX_NO_RENORM_MID_NORMAL) && !(approxMask&APPROX_NO_MID_NORMAL)) avgNormal.normalize(); // normalize only if used and if requested via approxMask
	// twist vector of the normal from the last step
	Vector3r normTwistVec=avgNormal*scene->dt*.5*avgNormal.dot(state1.angVel+state2.angVel);
	// compute relative velocity
	// noRatch: take radius or current distance as the branch vector; see discussion in ScGeom::precompute (avoidGranularRatcheting)
	Vector3r c1x=((noRatch && !r1>0) ? ( r1*normal).eval() : (contPt-state1.pos).eval()); // used only for sphere-sphere
	Vector3r c2x=(noRatch ? (-r2*normal).eval() : (contPt-state2.pos+shift2).eval());
	//Vector3r state2velCorrected=state2.vel+(scene->isPeriodic?scene->cell->intrShiftVel(I->cellDist):Vector3r::Zero()); // velocity of the second particle, corrected with meanfield velocity if necessary
	//cerr<<"correction "<<(scene->isPeriodic?scene->cell->intrShiftVel(I->cellDist):Vector3r::Zero())<<endl;
	Vector3r relShearVel=(state2.vel+state2.angVel.cross(c2x))-(state1.vel+state1.angVel.cross(c1x));
	// account for relative velocity of particles in different cell periods
	if(scene->isPeriodic) relShearVel+=scene->cell->intrShiftVel(I->cellDist);
	relShearVel-=avgNormal.dot(relShearVel)*avgNormal;
	Vector3r relShearDu=relShearVel*scene->dt;

	/* Update of quantities in global coords consists in adding 3 increments we have computed; in global coords (a is any vector)

		1. +relShearVel*scene->dt;      // mutual motion of the contact
		2. -a.cross(normRotVec);   // rigid rotation perpendicular to the normal
		3. -a.cross(normTwistVec); // rigid rotation parallel to the normal

	*/

	// compute current transformation, by updating previous axes
	// the X axis can be prescribed directly (copy of normal)
	// the mutual motion on the contact does not change transformation
	#ifdef L3_TRSF_QUATERNION
		const Matrix3r prevTrsf(g.trsf.toRotationMatrix());
		Quaternionr prevTrsfQ(g.trsf);
	#else
		const Matrix3r prevTrsf(g.trsf); // could be reference perhaps, but we need it to compute midTrsf (if applicable)
	#endif
	Matrix3r currTrsf; currTrsf.row(0)=currNormal;
	for(int i=1; i<3; i++){
		currTrsf.row(i)=prevTrsf.row(i)-prevTrsf.row(i).cross(normRotVec)-prevTrsf.row(i).cross(normTwistVec);
	}
	#ifdef L3_TRSF_QUATERNION
		Quaternionr currTrsfQ(currTrsf);
		if((scene->iter % trsfRenorm)==0 && trsfRenorm>0) currTrsfQ.normalize();
	#else
		if((scene->iter % trsfRenorm)==0 && trsfRenorm>0){
			#if 1
				currTrsf.row(0).normalize();
				currTrsf.row(1)-=currTrsf.row(0)*currTrsf.row(1).dot(currTrsf.row(0)); // take away y projected on x, to stabilize numerically
				currTrsf.row(1).normalize();
				currTrsf.row(2)=currTrsf.row(0).cross(currTrsf.row(1));
				currTrsf.row(2).normalize();
			#else
				currTrsf=Matrix3r(Quaternionr(currTrsf).normalized());
			#endif
			#ifdef YADE_DEBUG
				if(abs(currTrsf.determinant()-1)>.05){
					LOG_ERROR("##"<<I->getId1()<<"+"<<I->getId2()<<", |trsf|="<<currTrsf.determinant());
					g.trsf=currTrsf;
					throw runtime_error("Transformation matrix far from orthonormal.");
				}
			#endif
		}
	#endif

	/* Previous local trsf u'⁻ must be updated to current u'⁰. We have transformation T⁻ and T⁰,
		δ(a) denotes increment of a as defined above.  Two possibilities:

		1. convert to global, update, convert back: T⁰(T⁻*(u'⁻)+δ(T⁻*(u'⁻))). Quite heavy.
		2. update u'⁻ straight, using relShearVel in local coords; since relShearVel is computed 
			at (t-Δt/2), we would have to find intermediary transformation (same axis, half angle;
			the same as slerp at t=.5 between the two).

			This could be perhaps simplified by using T⁰ or T⁻ since they will not differ much,
			but it would have to be verified somehow.
	*/
	// if requested via approxMask, just use prevTrsf
	#ifdef L3_TRSF_QUATERNION
		Quaternionr midTrsf=(approxMask&APPROX_NO_MID_TRSF) ? prevTrsfQ : prevTrsfQ.slerp(.5,currTrsfQ);
	#else
		Quaternionr midTrsf=(approxMask&APPROX_NO_MID_TRSF) ? Quaternionr(prevTrsf) : Quaternionr(prevTrsf).slerp(.5,Quaternionr(currTrsf));
	#endif
	//cerr<<"prevTrsf=\n"<<prevTrsf<<", currTrsf=\n"<<currTrsf<<", midTrsf=\n"<<Matrix3r(midTrsf)<<endl;
	
	// updates of geom here

	// midTrsf*relShearVel should have the 0-th component (approximately) zero -- to be checked
	g.u+=midTrsf*relShearDu;
	//cerr<<"midTrsf=\n"<<midTrsf<<",relShearDu="<<relShearDu<<", transformed "<<midTrsf*relShearDu<<endl;
	g.u[0]=uN; // this does not have to be computed incrementally
	#ifdef L3_TRSF_QUATERNION
		g.trsf=currTrsfQ;
	#else
		g.trsf=currTrsf;
	#endif

	// GenericSpheresContact
	g.refR1=r1; g.refR2=r2;
	g.normal=currNormal;
	g.contactPoint=contPt;

	if(is6Dof){
		// update phi, from the difference of angular velocities
		// the difference is transformed to local coord using the midTrsf transformation
		// perhaps not consistent when spheres have different radii (depends how bending moment is computed)
		I->geom->cast<L6Geom>().phi+=midTrsf*(scene->dt*(state2.angVel-state1.angVel));
	}
};