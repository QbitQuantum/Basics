void SphereClumpGeom::recompute(int _div, bool failOk, bool fastOnly){
	if((centers.empty() && radii.empty()) || centers.size()!=radii.size()){
		if(failOk) { makeInvalid(); return;}
		throw std::runtime_error("SphereClumpGeom.recompute: centers and radii must have the same length (len(centers)="+to_string(centers.size())+", len(radii)="+to_string(radii.size())+"), and may not be empty.");
	}
	div=_div;
	// one single sphere: simple
	if(centers.size()==1){
		pos=centers[0];
		ori=Quaternionr::Identity();
		volume=(4/3.)*M_PI*pow(radii[0],3);
		inertia=Vector3r::Constant((2/5.)*volume*pow(radii[0],2));
		equivRad=radii[0];
		return;
	}
	volume=0;
	Vector3r Sg=Vector3r::Zero();
	Matrix3r Ig=Matrix3r::Zero();
	if(_div<=0){
		// non-intersecting: Steiner's theorem
		for(size_t i=0; i<centers.size(); i++){
			const Real& r(radii[i]); const Vector3r& x(centers[i]);
			Real v=(4/3.)*M_PI*pow(r,3);
			volume+=v;
			Sg+=v*x;
			Ig+=woo::Volumetric::inertiaTensorTranslate(Vector3r::Constant((2/5.)*v*pow(r,2)).asDiagonal(),v,-1.*x);
		}
	} else {
		// intersecting: grid sampling
		Real rMin=Inf; AlignedBox3r aabb;
		for(size_t i=0; i<centers.size(); i++){
			aabb.extend(centers[i]+Vector3r::Constant(radii[i]));
			aabb.extend(centers[i]-Vector3r::Constant(radii[i]));
			rMin=min(rMin,radii[i]);
		}
		if(rMin<=0){
			if(failOk){ makeInvalid(); return; }
			throw std::runtime_error("SphereClumpGeom.recompute: minimum radius must be positive (not "+to_string(rMin)+")");
		}
		Real dx=rMin/_div; Real dv=pow(dx,3);
		long nCellsApprox=(aabb.sizes()/dx).prod();
		 // don't compute anything, it would take too long
		if(fastOnly && nCellsApprox>1e5){ makeInvalid(); return; }
		if(nCellsApprox>1e8) LOG_WARN("SphereClumpGeom: space grid has "<<nCellsApprox<<" cells, computing inertia can take a long time.");
		Vector3r x;
		for(x.x()=aabb.min().x()+dx/2.; x.x()<aabb.max().x(); x.x()+=dx){
			for(x.y()=aabb.min().y()+dx/2.; x.y()<aabb.max().y(); x.y()+=dx){
				for(x.z()=aabb.min().z()+dx/2.; x.z()<aabb.max().z(); x.z()+=dx){
					for(size_t i=0; i<centers.size(); i++){
						if((x-centers[i]).squaredNorm()<pow(radii[i],2)){
							volume+=dv;
							Sg+=dv*x;
							Ig+=dv*(x.dot(x)*Matrix3r::Identity()-x*x.transpose())+/*along princial axes of dv; perhaps negligible?*/Matrix3r(Vector3r::Constant(dv*pow(dx,2)/6.).asDiagonal());
							break;
						}
					}
				}
			}
		}
	}
	woo::Volumetric::computePrincipalAxes(volume,Sg,Ig,pos,ori,inertia);
	equivRad=(inertia.array()/volume).sqrt().mean(); // mean of radii of gyration
}