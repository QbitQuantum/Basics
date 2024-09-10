/**
* \brief Collision Partikel mit einer Box.
* \param box zu testende Box
*/
void ParticleSystem::collide(ParticlePtr part, BoxPtr box)
{ 
    //sphere in das lokale koordinatensystem der box bringen
	Vector3<float> particlePos = part->getPosition() - box->getRigidBody()->getPosition();
	Quaternion boxOri = box->getRigidBody()->getOrientation();
	const Quaternion& boxInvOri = boxOri.inverse();    
    particlePos = qRotate(particlePos, boxInvOri);
    
    //test auf collision mit den 6 seiten der box
    unsigned int cnt = 0;
	float rad = 3.0f;

	float right = dot(particlePos, Vector3<float>(1,0,0)) + rad;
	float left = dot(particlePos, Vector3<float>(-1,0,0)) - rad;
	float front = dot(particlePos, Vector3<float>(0,0,1)) + rad;
	float back = dot(particlePos, Vector3<float>(0,0,-1)) - rad;
	float top = dot(particlePos, Vector3<float>(0,1,0)) + rad;
	float bottom = dot(particlePos, Vector3<float>(0,-1,0)) - rad;
	
	
    float dR  = box->getWidth()/2 - right + rad;
    float dL  = box->getWidth()/2 - left + rad;
    float dF  = box->getDepth()/2 - front + rad;
    float dBa = box->getDepth()/2 - back + rad;
    float dT  = box->getHeight()/2 - top + rad; 
    float dBo = box->getHeight()/2 - bottom + rad; 
    
    if (right  >= 0 && dR >= 0)  
	{	
		cnt ++;
	    if (right >  box->getWidth()/2)
		  particlePos[X] = box->getWidth()/2;	
		else  		
		  particlePos[X] = right ;	
	}
	if (left   >  0 && dL >= 0)  
	{
		cnt ++;	
		if(left > box->getWidth()/2)
		  particlePos[X] = -box->getWidth()/2;
		else
		  particlePos[X] = -left ;
	}
	if (front  >= 0 && dF >= 0)  
	{
		cnt ++;
		if (front > box->getDepth()/2)  
		  particlePos[Z] = box->getDepth()/2;
		else
		  particlePos[Z] = front;	  
 	}
	if (back   >  0 && dBa >= 0)  
	{
		cnt ++;
		if (back > box->getDepth()/2)  
		  particlePos[Z] = -box->getDepth()/2;
		else
		  particlePos[Z] = -back;  	
 	}
	if (top    >= 0 && dT >= 0) 
	{
		cnt ++;
		if (top > box->getHeight()/2)  
		  particlePos[Y] = box->getHeight()/2;
		else
		  particlePos[Y] = top;	  
 	}
	if (bottom >  0 && dBo >= 0) 
	{
		cnt ++;
		if (bottom > box->getHeight()/2)  
		  particlePos[Y] = -box->getHeight()/2;
		else
		  particlePos[Y] = -bottom  ;
	}
    
	//test auf collision
    if (cnt >= 3)
	{
		
		//berechnung normalB und contactPoint
		const Vector3<float>& contactPoint 
			= qRotate(particlePos, boxOri) + box->getRigidBody()->getPosition();
		//cout << "C: " << contactPoint << endl;
		//cout << "P: " << part->getPosition() << endl;
		Vector3<float> normalB = part->getPosition() - contactPoint;
		//cout << normalB.length() <<"\n";

		//if (normalB.length() != 0)
		normalB.normalize();
		
		// folgender Abschnitt aus: 
		// CollisionSystem::collisionResponse(part, sphere, contactPoint, normalB);

		//berechnung der relativen geschwindigkeit in richtung normalB
		const Vector3<float>& velocityA = part->getVelocity();
		const Vector3<float>& velocityB = box->getRigidBody()->getVelocity();
		Vector3<float> velA = part->getVelocity();
		Vector3<float> forceA = part->getForce();


//		const Vector3<float>& rA = contactPoint - part->getPosition(); // vorher: particlePos!
//		const Vector3<float>& rB = contactPoint - box->getPosition();
		
		const Vector3<float>& vA = velocityA;
		const Vector3<float>& vB = velocityB;
		const Vector3<float>& vR = vA - vB;
		
		float vN = dot(vR, normalB);
		
//------------------Behandlung für colliding contact---------------------------------------
		if (vN <= 0.5)
		{	

//--------------------neue Behandlung aus Sphere kopiert-------------------------
			float vDoN = dot(velA, normalB);
			Vector3<float> vS = normalB * vDoN; 
		
			float fDoN = dot(forceA, normalB);
			Vector3<float> fS = normalB * fDoN;
			Vector3<float> force = part->getForce();
			force.normalize();
			if (dot (force, normalB) > 0 ){
				part->setVelocity(part->getVelocity() - vS);
				part->setVelocity(part->getVelocity() * 0.75);	// Wert: 0.75
				part->addForce((-1.0) * fS);
				part->setForce(part->getForce() * 0.75);	// Wert: 0.75
				part->setIsColliding(true);
			}
//------------------------------------------------------------------------------
			////berechnung der impuls-kraft in richtung normalB
			////float damping = (0.01f + box->getBounciness()) / 2.0f;
			//float damping = 0.12f;
			//float invMassA, invMassB = 0.0f;
			////Matrix<float> invTensorA(3,3);

			////Matrix<float> invTensorB = box->getInvWorldInertiaTensor();
		
			////test ob dynamisch
			//if(part->getIsDynamicFlag())
			//{	
			//	invMassA = part->getInvMass();
			//}
			//else 
			//	invMassA = 0.0;
			//
			//if(box->getRigidBody()->getIsDynamicFlag())
			//{	
			//	invMassB = box->getInvMass();
			//	//invTensorB = box->getRigidBody()->getInvWorldInertiaTensor();
			//}
			//else 
			//	invMassB = 0.0;
		
			//float fNum = -(/*1+*/damping)*(dot(normalB,(velocityA - velocityB)));
			//float fDenom = invMassA + invMassB;// + dot(crossA,uA)+dot(crossB,uB);

			//float impulseMagnitude = fNum / fDenom;

			//if (impulseMagnitude < 0){
			//Vector3<float> impulseForce = impulseMagnitude * normalB;

			///*impulseForce.normalize();
			//float vDoI = dot(velA, impulseForce);
			//float fDoI = dot(forceA, impulseForce);
			//Vec3 vS = impulseForce * vDoI;
			//Vec3 fS = impulseForce * fDoI;*/

			////part->setVelocity(part->getVelocity()[X], 0.0f, part->getVelocity()[Z]);
			////part->setVelocity(part->getVelocity() - vS);
			////part->addForce(fS);
			////setzen der linaren momente
			//if (part->getInvMass()!=0)
			//{
			//part->setVelocity(part->getVelocity() - impulseForce/invMassA);
			//part->setIsColliding(true);
			//}
			////part->setVelocity(part->getVelocity() + (impulseForce / invMassB));        
			//
			//}
		}
	}
	
}