//bilateral constraint between two dynamic objects
void resolveSingleBilateral(btRigidBody& body1, const btVector3& pos1,
                      btRigidBody& body2, const btVector3& pos2,
                      btScalar distance, const btVector3& normal,btScalar& impulse ,btScalar timeStep)
{
	(void)timeStep;
	(void)distance;


	btScalar normalLenSqr = normal.length2();
	btAssert(btFabs(normalLenSqr) < btScalar(1.1));
	if (normalLenSqr > btScalar(1.1))
	{
		impulse = btScalar(0.);
		return;
	}
	btVector3 rel_pos1 = pos1 - body1.getCenterOfMassPosition(); 
	btVector3 rel_pos2 = pos2 - body2.getCenterOfMassPosition();
	//this jacobian entry could be re-used for all iterations
	
	btVector3 vel1 = body1.getVelocityInLocalPoint(rel_pos1);
	btVector3 vel2 = body2.getVelocityInLocalPoint(rel_pos2);
	btVector3 vel = vel1 - vel2;
	

	   btJacobianEntry jac(body1.getCenterOfMassTransform().getBasis().transpose(),
		body2.getCenterOfMassTransform().getBasis().transpose(),
		rel_pos1,rel_pos2,normal,body1.getInvInertiaDiagLocal(),body1.getInvMass(),
		body2.getInvInertiaDiagLocal(),body2.getInvMass());

	btScalar jacDiagAB = jac.getDiagonal();
	btScalar jacDiagABInv = btScalar(1.) / jacDiagAB;
	
	  btScalar rel_vel = jac.getRelativeVelocity(
		body1.getLinearVelocity(),
		body1.getCenterOfMassTransform().getBasis().transpose() * body1.getAngularVelocity(),
		body2.getLinearVelocity(),
		body2.getCenterOfMassTransform().getBasis().transpose() * body2.getAngularVelocity()); 
	btScalar a;
	a=jacDiagABInv;


	rel_vel = normal.dot(vel);
	
	//todo: move this into proper structure
	btScalar contactDamping = btScalar(0.2);

#ifdef ONLY_USE_LINEAR_MASS
	btScalar massTerm = btScalar(1.) / (body1.getInvMass() + body2.getInvMass());
	impulse = - contactDamping * rel_vel * massTerm;
#else	
	btScalar velocityImpulse = -contactDamping * rel_vel * jacDiagABInv;
	impulse = velocityImpulse;
#endif
}