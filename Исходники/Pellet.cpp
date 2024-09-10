void PelletAgglomerator::run(){
	//DemField& dem(field->cast<DemField>());
	// loop over all source particles, and loop over all contacts of each of them
	if(isnan(massIncPerRad)) throw std::runtime_error("PalletAgglomerator.massIncPerRad==NaN (must be specified)");
	if(dampHalfLife<0) dampHalfLife*=-scene->dt;
	Real sumDMass=0.;
	Real lambda=(dampHalfLife==0 || isnan(dampHalfLife))?0:(log(2)/dampHalfLife);
	for(const shared_ptr<Particle>& src: agglomSrcs){
		for(const auto& idCon: src->contacts){
			const shared_ptr<Contact>& c(idCon.second);
			if(!c->isReal()) continue;
			Particle* other(c->leakOther(src.get()));
			Real* radius=nullptr;
			// if(!other->shape->isA<Sphere>()) continue; // other particles is not a sphere
			if(other->shape->isA<Sphere>()) radius=&(other->shape->cast<Sphere>().radius);
			else if(other->shape->isA<Capsule>()) radius=&(other->shape->cast<Capsule>().radius);
			else continue;
			assert(dynamic_pointer_cast<L6Geom>(c->geom));
			// radius change
			// angVel is local already
			Real dMass=c->geom->cast<L6Geom>().angVel.tail<2>().norm()*scene->dt*massIncPerRad;
			sumDMass+=dMass;
			Real newVol=(4/3.)*M_PI*pow(*radius,3)+dMass/other->material->density;
			*radius=cbrt(3*newVol/(4*M_PI));
			other->shape->updateMassInertia(other->material->density);
			if(!other->matState) other->matState=make_shared<PelletMatState>();
			assert(dynamic_pointer_cast<PelletMatState>(other->matState));
			auto& pms=other->matState->cast<PelletMatState>();
			if(pms.stepAgglomUpdated!=scene->step){ pms.agglomRate=0.; pms.stepAgglomUpdated=scene->step; } // reset value
			pms.agglomRate+=dMass/scene->dt;
			// rotation damping
			if(lambda>0){
				other->shape->nodes[0]->getData<DemData>().angVel*=(1-lambda*scene->dt);
			}
			boost::mutex::scoped_lock l(pms.lock);
			pms.cumAgglomMass+=dMass;
			pms.cumAgglomAngle+=c->geom->cast<L6Geom>().angVel.tail<2>().norm()*scene->dt;
		}
	}
	currRate=(1-currRateSmooth)*currRate+currRateSmooth*(sumDMass/scene->dt);
	mass+=sumDMass;
};