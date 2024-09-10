void SoSpring::applyForce()
{
    // Calculate the forces according to Hooke's Law
    // k * (DISTij-LENij) * Vij
	SbVec3f resultingForces;
 	SbVec3f deltaVector = endpos.getValue()-startpos.getValue();
    float elongation; 
	
	SbVec3f acc1 = acc.getValue();
	SbVec3f vel1 = vel.getValue();

	elongation = deltaVector.length();
	deltaVector.normalize();
	resultingForces=stiffness.getValue()*elongation*deltaVector;

	// debug 
	// printf("a1%f,a2%f,a3%f, v1%f,v2%f,v3%f,p1%f,p2%f,p3%f \n", acc1[0],acc1[1],acc1[2],vel1[0],vel1[1],vel1[2],startpos.getValue()[0],startpos.getValue()[1],startpos.getValue()[2] );
	acc1 = resultingForces*(1.0f/mass.getValue());
 	vel1 = vel1 + (acc1*timeStep.getValue());
	vel1  *= damp.getValue();

	vel.setValue(vel1);
	acc.setValue(acc1);

	if ( (vel1.length()<treshold.getValue())& (acc1.length()<treshold.getValue() ) )
		{
		// debug
		//printf("INFO: treasold reached!! \n");
		
		timer->unschedule();
		}
	else // update
		{
	startpos.setValue(startpos.getValue()+ vel1*timeStep.getValue()) ;
		}
}