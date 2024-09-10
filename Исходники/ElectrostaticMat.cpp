bool Law2_ScGeom_ElectrostaticPhys::go(shared_ptr<IGeom>& iGeom, shared_ptr<IPhys>& iPhys, Interaction* interaction)
{
	// Physic
    ElectrostaticPhys* phys=static_cast<ElectrostaticPhys*>(iPhys.get());

    // Geometry
    ScGeom* geom=static_cast<ScGeom*>(iGeom.get());

    // Get bodies properties
    Body::id_t id1 = interaction->getId1();
    Body::id_t id2 = interaction->getId2();
    const shared_ptr<Body> b1 = Body::byId(id1,scene);
    const shared_ptr<Body> b2 = Body::byId(id2,scene);
    State* s1 = b1->state.get();
    State* s2 = b2->state.get();

    // geometric parameters
    Real a((geom->radius1+geom->radius2)/2.);
    bool isNew=false;
	
	// Speeds
    Vector3r shiftVel=scene->isPeriodic ? Vector3r(scene->cell->velGrad*scene->cell->hSize*interaction->cellDist.cast<Real>()) : Vector3r::Zero();
    Vector3r shift2 = scene->isPeriodic ? Vector3r(scene->cell->hSize*interaction->cellDist.cast<Real>()): Vector3r::Zero();

    Vector3r relV = geom->getIncidentVel(s1, s2, scene->dt, shift2, shiftVel, false );
	Real undot = relV.dot(geom->normal); // Normal velocity norm
	
    if(-geom->penetrationDepth > a && -geom->penetrationDepth > 10.*phys->DebyeLength) { return false; }
    
    // inititalization
	if(phys->u == -1. ) {phys->u = -geom->penetrationDepth; isNew=true;}
	
	// Solve normal
	normalForce_DL_Adim(phys,geom, undot,isNew);
	
	// Solve shear and torques
	Vector3r C1 = Vector3r::Zero();
	Vector3r C2 = Vector3r::Zero();
	
	computeShearForceAndTorques_log(phys, geom, s1, s2, C1, C2);
	
    // Apply!
    scene->forces.addForce(id1,phys->normalForce+phys->shearForce);
    scene->forces.addTorque(id1,C1);

    scene->forces.addForce(id2,-(phys->normalForce+phys->shearForce));
    scene->forces.addTorque(id2,C2);

    return true;
}