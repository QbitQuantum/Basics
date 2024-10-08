bool Law2_ScGeom_MindlinPhys_Mindlin::go(shared_ptr<IGeom>& ig, shared_ptr<IPhys>& ip, Interaction* contact){
	const Real& dt = scene->dt; // get time step
	
	Body::id_t id1 = contact->getId1(); // get id body 1
 	Body::id_t id2 = contact->getId2(); // get id body 2

	State* de1 = Body::byId(id1,scene)->state.get();
	State* de2 = Body::byId(id2,scene)->state.get();	

	ScGeom* scg = static_cast<ScGeom*>(ig.get());
	MindlinPhys* phys = static_cast<MindlinPhys*>(ip.get());	

	const shared_ptr<Body>& b1=Body::byId(id1,scene); 
	const shared_ptr<Body>& b2=Body::byId(id2,scene); 

	bool useDamping=(phys->betan!=0. || phys->betas!=0. || phys->alpha!=0.);
	bool LinDamp=true;
	if (phys->alpha!=0.) {LinDamp=false;} // use non linear damping

	// tangential and normal stiffness coefficients, recomputed from betan,betas at every step
	Real cn=0, cs=0;

	/****************/
	/* NORMAL FORCE */
	/****************/
	
	Real uN = scg->penetrationDepth; // get overlapping 
	if (uN<0) {
		if (neverErase) {phys->shearForce = phys->normalForce = Vector3r::Zero(); phys->kn=phys->ks=0; return true;}
		else return false;
	}
	/* Hertz-Mindlin's formulation (PFC) 
	Note that the normal stiffness here is a secant value (so as it is cannot be used in the GSTS)
	In the first place we get the normal force and then we store kn to be passed to the GSTS */
	Real Fn = phys->kno*std::pow(uN,1.5); // normal Force (scalar)
	if (includeAdhesion) {
			Fn -= phys->adhesionForce; // include adhesion force to account for the effect of Van der Waals interactions
			phys->isAdhesive = (Fn<0); // set true the bool to count the number of adhesive contacts
			}
	phys->normalForce = Fn*scg->normal; // normal Force (vector)

	if (calcEnergy){
		Real R=scg->radius1*scg->radius2/(scg->radius1+scg->radius2);
		phys->radius=pow((Fn+(includeAdhesion?phys->adhesionForce:0.))*pow(R,3/2.)/phys->kno,1/3.); // attribute not used anywhere, we do not need it
	}

	/*******************************/
	/* TANGENTIAL NORMAL STIFFNESS */
	/*******************************/
	
	phys->kn = 3./2.*phys->kno*std::pow(uN,0.5); // here we store the value of kn to compute the time step
	
	/******************************/
	/* TANGENTIAL SHEAR STIFFNESS */
	/******************************/
	
	phys->ks = phys->kso*std::pow(uN,0.5); // get tangential stiffness (this is a tangent value, so we can pass it to the GSTS)

	/************************/
	/* DAMPING COEFFICIENTS */
	/************************/
	
	// Inclusion of local damping if requested
	// viscous damping is defined for both linear and non-linear elastic case 
	if (useDamping && LinDamp){
		Real mbar = (!b1->isDynamic() && b2->isDynamic()) ? de2->mass : ((!b2->isDynamic() && b1->isDynamic()) ? de1->mass : (de1->mass*de2->mass / (de1->mass + de2->mass))); // get equivalent mass if both bodies are dynamic, if not set it equal to the one of the dynamic body
		//Real mbar = de1->mass*de2->mass / (de1->mass + de2->mass); // equivalent mass
		Real Cn_crit = 2.*sqrt(mbar*phys->kn); // Critical damping coefficient (normal direction)
		Real Cs_crit = 2.*sqrt(mbar*phys->ks); // Critical damping coefficient (shear direction)
		// Note: to compare with the analytical solution you provide cn and cs directly (since here we used a different method to define c_crit)
		cn = Cn_crit*phys->betan; // Damping normal coefficient
		cs = Cs_crit*phys->betas; // Damping tangential coefficient
		if(phys->kn<0 || phys->ks<0){ cerr<<"Negative stiffness kn="<<phys->kn<<" ks="<<phys->ks<<" for ##"<<b1->getId()<<"+"<<b2->getId()<<", step "<<scene->iter<<endl; }
	}
	else if (useDamping){ // (see Tsuji, 1992)
		Real mbar = (!b1->isDynamic() && b2->isDynamic()) ? de2->mass : ((!b2->isDynamic() && b1->isDynamic()) ? de1->mass : (de1->mass*de2->mass / (de1->mass + de2->mass))); // get equivalent mass if both bodies are dynamic, if not set it equal to the one of the dynamic body
		cn = phys->alpha*sqrt(mbar)*pow(uN,0.25); // normal viscous coefficient, see also [Antypov2011] eq. 10
		cs = cn; // same value for shear viscous coefficient
	}

	/***************/
	/* SHEAR FORCE */
	/***************/
	
	Vector3r& shearElastic = phys->shearElastic; // reference for shearElastic force
	// Define shifts to handle periodicity
	const Vector3r shift2 = scene->isPeriodic ? scene->cell->intrShiftPos(contact->cellDist): Vector3r::Zero(); 
	const Vector3r shiftVel = scene->isPeriodic ? scene->cell->intrShiftVel(contact->cellDist): Vector3r::Zero(); 
	// 1. Rotate shear force
	shearElastic = scg->rotate(shearElastic);
	Vector3r prev_FsElastic = shearElastic; // save shear force at previous time step
	// 2. Get incident velocity, get shear and normal components
	Vector3r incidentV = scg->getIncidentVel(de1, de2, dt, shift2, shiftVel, preventGranularRatcheting);	
	Vector3r incidentVn = scg->normal.dot(incidentV)*scg->normal; // contact normal velocity
	Vector3r incidentVs = incidentV - incidentVn; // contact shear velocity
	// 3. Get shear force (incrementally)
	shearElastic = shearElastic - phys->ks*(incidentVs*dt);

	/**************************************/
	/* VISCOUS DAMPING (Normal direction) */
	/**************************************/
	
	// normal force must be updated here before we apply the Mohr-Coulomb criterion
	if (useDamping){ // get normal viscous component
		phys->normalViscous = cn*incidentVn;
		Vector3r normTemp = phys->normalForce - phys->normalViscous; // temporary normal force
		// viscous force should not exceed the value of current normal force, i.e. no attraction force should be permitted if particles are non-adhesive
		// if particles are adhesive, then fixed the viscous force at maximum equal to the adhesion force
		// *** enforce normal force to zero if no adhesion is permitted ***
		if (phys->adhesionForce==0.0 || !includeAdhesion){
						if (normTemp.dot(scg->normal)<0.0){
										phys->normalForce = Vector3r::Zero();
										phys->normalViscous = phys->normalViscous + normTemp; // normal viscous force is such that the total applied force is null - it is necessary to compute energy correctly!
						}
						else{phys->normalForce -= phys->normalViscous;}
		}
		else if (includeAdhesion && phys->adhesionForce!=0.0){
						// *** limit viscous component to the max adhesive force ***
						if (normTemp.dot(scg->normal)<0.0 && (phys->normalViscous.norm() > phys->adhesionForce) ){
										Real normVisc = phys->normalViscous.norm(); Vector3r normViscVector = phys->normalViscous/normVisc;
										phys->normalViscous = phys->adhesionForce*normViscVector;
										phys->normalForce -= phys->normalViscous;
						}
						// *** apply viscous component - in the presence of adhesion ***
						else {phys->normalForce -= phys->normalViscous;}
		}
		if (calcEnergy) {normDampDissip += phys->normalViscous.dot(incidentVn*dt);} // calc dissipation of energy due to normal damping
	}
	

	/*************************************/
	/* SHEAR DISPLACEMENT (elastic only) */
	/*************************************/
	
	Vector3r& us_elastic = phys->usElastic;
	us_elastic = scg->rotate(us_elastic); // rotate vector
	Vector3r prevUs_el = us_elastic; // store previous elastic shear displacement (already rotated)
	us_elastic -= incidentVs*dt; // add shear increment

	/****************************************/
	/* SHEAR DISPLACEMENT (elastic+plastic) */
	/****************************************/
	
	Vector3r& us_total = phys->usTotal;
	us_total = scg->rotate(us_total); // rotate vector
	Vector3r prevUs_tot = us_total; // store previous total shear displacement (already rotated)
	us_total -= incidentVs*dt; // add shear increment NOTE: this vector is not passed into the failure criterion, hence it holds also the plastic part of the shear displacement

	bool noShearDamp = false; // bool to decide whether we need to account for shear damping dissipation or not
	
	/********************/
	/* MOHR-COULOMB law */
	/********************/
	phys->isSliding=false;
	phys->shearViscous=Vector3r::Zero(); // reset so that during sliding, the previous values is not there
	Fn = phys->normalForce.norm();
	if (!includeAdhesion) {
		Real maxFs = Fn*phys->tangensOfFrictionAngle;
		if (shearElastic.squaredNorm() > maxFs*maxFs){
			phys->isSliding=true;
			noShearDamp = true; // no damping is added in the shear direction, hence no need to account for shear damping dissipation
			Real ratio = maxFs/shearElastic.norm();
			shearElastic *= ratio; phys->shearForce = shearElastic; /*store only elastic shear displacement*/ us_elastic*= ratio;
			if (calcEnergy) {frictionDissipation += (us_total-prevUs_tot).dot(shearElastic);} // calculate energy dissipation due to sliding behavior
			}
		else if (useDamping){ // add current contact damping if we do not slide and if damping is requested
			phys->shearViscous = cs*incidentVs; // get shear viscous component
			phys->shearForce = shearElastic - phys->shearViscous;}
		else if (!useDamping) {phys->shearForce = shearElastic;} // update the shear force at the elastic value if no damping is present and if we passed MC
	}
	else { // Mohr-Coulomb formulation adpated due to the presence of adhesion (see Thornton, 1991).
		Real maxFs = phys->tangensOfFrictionAngle*(phys->adhesionForce+Fn); // adhesionForce already included in normalForce (above)
		if (shearElastic.squaredNorm() > maxFs*maxFs){
			phys->isSliding=true;
			noShearDamp = true; // no damping is added in the shear direction, hence no need to account for shear damping dissipation
			Real ratio = maxFs/shearElastic.norm(); shearElastic *= ratio; phys->shearForce = shearElastic; /*store only elastic shear displacement*/ us_elastic *= ratio;
			if (calcEnergy) {frictionDissipation += (us_total-prevUs_tot).dot(shearElastic);} // calculate energy dissipation due to sliding behavior
			}
		else if (useDamping){ // add current contact damping if we do not slide and if damping is requested
			phys->shearViscous = cs*incidentVs; // get shear viscous component
			phys->shearForce = shearElastic - phys->shearViscous;}
		else if (!useDamping) {phys->shearForce = shearElastic;} // update the shear force at the elastic value if no damping is present and if we passed MC
	}

	/************************/
	/* SHEAR ELASTIC ENERGY */
	/************************/
	
	// NOTE: shear elastic energy calculation must come after the MC criterion, otherwise displacements and forces are not updated
	if (calcEnergy) {
		shearEnergy += (us_elastic-prevUs_el).dot((shearElastic+prev_FsElastic)/2.); // NOTE: no additional energy if we perform sliding since us_elastic and prevUs_el will hold the same value (in fact us_elastic is only keeping the elastic part). We work out the area of the trapezium.
	}

	/**************************************************/
	/* VISCOUS DAMPING (energy term, shear direction) */
	/**************************************************/
	
	if (useDamping){ // get normal viscous component (the shear one is calculated inside Mohr-Coulomb criterion, see above)
		if (calcEnergy) {if (!noShearDamp) {shearDampDissip += phys->shearViscous.dot(incidentVs*dt);}} // calc energy dissipation due to viscous linear damping
	}

	/****************/
	/* APPLY FORCES */
	/****************/
	
	if (!scene->isPeriodic)
		applyForceAtContactPoint(-phys->normalForce - phys->shearForce, scg->contactPoint , id1, de1->se3.position, id2, de2->se3.position);
	else { // in scg we do not wrap particles positions, hence "applyForceAtContactPoint" cannot be used
		Vector3r force = -phys->normalForce - phys->shearForce;
		scene->forces.addForce(id1,force);
		scene->forces.addForce(id2,-force);
		scene->forces.addTorque(id1,(scg->radius1-0.5*scg->penetrationDepth)* scg->normal.cross(force));
		scene->forces.addTorque(id2,(scg->radius2-0.5*scg->penetrationDepth)* scg->normal.cross(force));
	}
	
	/********************************************/
	/* MOMENT CONTACT LAW */
	/********************************************/
	if (includeMoment){
		// *** Bending ***//
		// new code to compute relative particle rotation (similar to the way the shear is computed)
		// use scg function to compute relAngVel
		Vector3r relAngVel = scg->getRelAngVel(de1,de2,dt);
		//Vector3r relAngVel = (b2->state->angVel-b1->state->angVel);
		Vector3r relAngVelBend = relAngVel - scg->normal.dot(relAngVel)*scg->normal; // keep only the bending part 
		Vector3r relRot = relAngVelBend*dt; // relative rotation due to rolling behaviour	
		// incremental formulation for the bending moment (as for the shear part)
		Vector3r& momentBend = phys->momentBend;
		momentBend = scg->rotate(momentBend); // rotate moment vector (updated)
		momentBend = momentBend-phys->kr*relRot; // add incremental rolling to the rolling vector
		// ----------------------------------------------------------------------------------------
		// *** Torsion ***//
		Vector3r relAngVelTwist = scg->normal.dot(relAngVel)*scg->normal;
		Vector3r relRotTwist = relAngVelTwist*dt; // component of relative rotation along n
		// incremental formulation for the torsional moment
		Vector3r& momentTwist = phys->momentTwist;
		momentTwist = scg->rotate(momentTwist); // rotate moment vector (updated)
		momentTwist = momentTwist-phys->ktw*relRotTwist;

#if 0
	// code to compute the relative particle rotation
	if (includeMoment){
		Real rMean = (scg->radius1+scg->radius2)/2.;
		// sliding motion
		Vector3r duS1 = scg->radius1*(phys->prevNormal-scg->normal);
		Vector3r duS2 = scg->radius2*(scg->normal-phys->prevNormal);
		// rolling motion
		Vector3r duR1 = scg->radius1*dt*b1->state->angVel.cross(scg->normal);
		Vector3r duR2 = -scg->radius2*dt*b2->state->angVel.cross(scg->normal);
		// relative position of the old contact point with respect to the new one
		Vector3r relPosC1 = duS1+duR1;
		Vector3r relPosC2 = duS2+duR2;
		
		Vector3r duR = (relPosC1+relPosC2)/2.; // incremental displacement vector (same radius is temporarily assumed)

		// check wheter rolling will be present, if not do nothing
		Vector3r x=scg->normal.cross(duR);
		Vector3r normdThetaR(Vector3r::Zero()); // initialize 
		if(x.squaredNorm()==0) { /* no rolling */ }
		else {
				Vector3r normdThetaR = x/x.norm(); // moment unit vector
				phys->dThetaR = duR.norm()/rMean*normdThetaR;} // incremental rolling
		
		// incremental formulation for the bending moment (as for the shear part)
		Vector3r& momentBend = phys->momentBend;
		momentBend = scg->rotate(momentBend); // rotate moment vector
		momentBend = momentBend+phys->kr*phys->dThetaR; // add incremental rolling to the rolling vector FIXME: is the sign correct?
#endif

		// check plasticity condition (only bending part for the moment)
		Real MomentMax = phys->maxBendPl*phys->normalForce.norm();
		Real scalarMoment = phys->momentBend.norm();
		if (MomentMax>0){
			if(scalarMoment > MomentMax) 
			{
			    Real ratio = MomentMax/scalarMoment; // to fix the moment to its yielding value
			    phys->momentBend *= ratio;
			 }
		}
		// apply moments
		Vector3r moment = phys->momentTwist+phys->momentBend;
		scene->forces.addTorque(id1,-moment); 
		scene->forces.addTorque(id2,moment);
	}
	return true;
	// update variables
	//phys->prevNormal = scg->normal;
}

// The following code was moved from Ip2_FrictMat_FrictMat_MindlinCapillaryPhys.cpp

void Ip2_FrictMat_FrictMat_MindlinCapillaryPhys::go( const shared_ptr<Material>& b1 //FrictMat
					, const shared_ptr<Material>& b2 // FrictMat
					, const shared_ptr<Interaction>& interaction)
{
	if(interaction->phys) return; // no updates of an already existing contact necessary

	shared_ptr<MindlinCapillaryPhys> contactPhysics(new MindlinCapillaryPhys());
	interaction->phys = contactPhysics;

	FrictMat* mat1 = YADE_CAST<FrictMat*>(b1.get());
	FrictMat* mat2 = YADE_CAST<FrictMat*>(b2.get());
	
	/* from interaction physics */
	Real Ea = mat1->young;
	Real Eb = mat2->young;
	Real Va = mat1->poisson;
	Real Vb = mat2->poisson;
	Real fa = mat1->frictionAngle;
	Real fb = mat2->frictionAngle;

	/* from interaction geometry */
	GenericSpheresContact* scg = YADE_CAST<GenericSpheresContact*>(interaction->geom.get());		
	Real Da = scg->refR1>0 ? scg->refR1 : scg->refR2; 
	Real Db = scg->refR2; 
	//Vector3r normal=scg->normal;  //The variable set but not used

	/* calculate stiffness coefficients */
	Real Ga = Ea/(2*(1+Va));
	Real Gb = Eb/(2*(1+Vb));
	Real G = (Ga+Gb)/2; // average of shear modulus
	Real V = (Va+Vb)/2; // average of poisson's ratio
	Real E = Ea*Eb/((1.-std::pow(Va,2))*Eb+(1.-std::pow(Vb,2))*Ea); // Young modulus
	Real R = Da*Db/(Da+Db); // equivalent radius
	Real Rmean = (Da+Db)/2.; // mean radius
	Real Kno = 4./3.*E*sqrt(R); // coefficient for normal stiffness
	Real Kso = 2*sqrt(4*R)*G/(2-V); // coefficient for shear stiffness
	Real frictionAngle = std::min(fa,fb);

	Real Adhesion = 4.*Mathr::PI*R*gamma; // calculate adhesion force as predicted by DMT theory

	/* pass values calculated from above to MindlinCapillaryPhys */
	contactPhysics->tangensOfFrictionAngle = std::tan(frictionAngle); 
	//mindlinPhys->prevNormal = scg->normal; // used to compute relative rotation
	contactPhysics->kno = Kno; // this is just a coeff
	contactPhysics->kso = Kso; // this is just a coeff
	contactPhysics->adhesionForce = Adhesion;
	
	contactPhysics->kr = krot;
	contactPhysics->ktw = ktwist;
	contactPhysics->maxBendPl = eta*Rmean; // does this make sense? why do we take Rmean?

	/* compute viscous coefficients */
	if(en && betan) throw std::invalid_argument("Ip2_FrictMat_FrictMat_MindlinCapillaryPhys: only one of en, betan can be specified.");
	if(es && betas) throw std::invalid_argument("Ip2_FrictMat_FrictMat_MindlinCapillaryPhys: only one of es, betas can be specified.");

	// en or es specified, just compute alpha, otherwise alpha remains 0
	if(en || es){
		Real logE = log((*en)(mat1->id,mat2->id));
		contactPhysics->alpha = -sqrt(5/6.)*2*logE/sqrt(pow(logE,2)+pow(Mathr::PI,2))*sqrt(2*E*sqrt(R)); // (see Tsuji, 1992)
	}
	
	// betan specified, use that value directly; otherwise give zero
	else{	
		contactPhysics->betan=betan ? (*betan)(mat1->id,mat2->id) : 0; 
		contactPhysics->betas=betas ? (*betas)(mat1->id,mat2->id) : contactPhysics->betan;
	}
};