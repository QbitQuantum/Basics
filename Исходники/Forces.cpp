void GravitationalForce::apply_fun(float d_t){
	for (unsigned int i = 0; i < mInfluencedPhysics.size()-1; i++){
		Physics* lhs = mInfluencedPhysics[i];
		for (unsigned int j = i+1 ; j < mInfluencedPhysics.size(); j++){
			Physics* rhs = mInfluencedPhysics[j];
			Vector3 distanceVector = rhs->getPosition()-lhs->getPosition();
			float distance = distanceVector.length();
			//Distanz in Ordnung
			if (distance < getMaxDistance() && distance >= 1.0){
				if(distance < 1){
					distance = 1;
				}
				distanceVector.normalize();
				//Anziehungskraft berechnen
				float force = mScale * (rhs->getMass()*lhs->getMass() / (distance*distance));
				//Anziehungskraft in Ordnung
				if (force > getMinForce()){
					Vector3 Rhs_forceVector = distanceVector;
					Rhs_forceVector *= force;
					//Anziehungskraft um d_t skaliert anwenden
					lhs->applyForce(Rhs_forceVector*d_t);
					Vector3 Lhs_forceVector = (-1.0) * distanceVector;
					Lhs_forceVector *= force;
					//Anziehungskraft um d_t skaliert anwenden
					rhs->applyForce(Lhs_forceVector*d_t);
				}
			}
		}
	}
}