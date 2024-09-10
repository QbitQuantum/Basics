bool Seaweed::collisionParticleParticle(Particle *p1, Particle *p2)
{
	// particle-particle distance
	
	// normal vector between the two
	Vec u = p1->getPosition() - p2->getPosition();
	
	// norm of the vector
	double penetration = u.normalize();
	
	// take into account the radius of both particles, account for potentially different radius
	penetration -= (p1->getRadius() + p2->getRadius()) ;
	if (penetration >= 0)
		return false;
	
	// penetration velocity
	double vPen = ( ( p1->getVelocity() * u) - ( p2->getVelocity() * u) ); // Reciprocity of the movement, move toward each other 
	p1->incrPosition(-penetration * u);
	p2->incrPosition(penetration * u);
	p1->incrVelocity(-(1 + rebound) * vPen * u * p1->getMass()/(p1->getMass() + p2->getMass())); // reaction is pondered
	p2->incrVelocity((1 + rebound) * vPen * u * p2->getMass()/(p1->getMass() + p2->getMass()));
	
	return true;
}