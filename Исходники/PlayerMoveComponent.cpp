//Mittels des Seperating Axis Theorem wird auf eine Kolission mit den Hindernissen geprüft
void PlayerMoveComponent::quadColission()
{

	CVector position = getPosition();
	double size = parent->getSize();

	//Die Eckpunkte des Spielers
	CVector v1 = CVector(position[0]-size,position[1]+size);
	CVector v2 = CVector(position[0]+size,position[1]+size);
	CVector v3 = CVector(position[0]+size,position[1]-size);
	CVector v4 = CVector(position[0]-size,position[1]-size);

	//Die zu prüfenden Achsen werden mit Hilfe der Vektoren der Spielerposition erstellt

	CVector a1 = v1 - v2;
	a1 = CVector(a1[1],-a1[0]);
	a1.normalize();

	CVector a2 = v2 - v3;
	a2 = CVector(a2[1],-a2[0]);
	a2.normalize();

	CVector a3 = v3 - v4;
	a3 = CVector(a3[1],-a3[0]);
	a3.normalize();

	CVector a4 = v4 - v1;
	a4 = CVector(a4[1],-a4[0]);
	a4.normalize();

	CVector a[4] = {a1,a2,a3,a4};
	CVector v[4] = {CVector(-size,size),CVector(size,size),CVector(size,-size),CVector(-size,-size)};

	vector<Character *> characters = parent->getCharacterManager()->getAllNearbyCharacters(getPosition(),OBSTACLE_TAG,200.0);

	vector<Character *>::iterator it = characters.begin();

	while(it != characters.end())
	{
		Character *c = (*it);
		it++;

		CVector cPos = c->getPosition()-position;
		double cSize = c->getSize();

		//Die Eckpunkte eines Obstacles
		CVector w1 = CVector(cPos[0]-cSize,cPos[1]+cSize);
		CVector w2 = CVector(cPos[0]+cSize,cPos[1]+cSize);
		CVector w3 = CVector(cPos[0]+cSize,cPos[1]-cSize);
		CVector w4 = CVector(cPos[0]-cSize,cPos[1]-cSize);

		CVector w[4] = {w1,w2,w3,w4};

		CVector moveVector = CVector(9999999,9999999); 

		//Die Punkte werden auf eine Achse projiziert. Anschließend werden die Maxima und Minima miteinander verglichen
		for(int i = 0; i<4; ++i){
			CVector maxV = CVector();
			CVector minV = CVector();
			CVector	maxW = CVector();
			CVector minW = CVector();

			for(int j = 0; j<4; ++j){

				CVector projV = (a[i] * v[j]) * a[i];
			
				if(projV[0]>maxV[0] || maxV.isNil())
					maxV[0] = projV[0];
				if(projV[1]>maxV[1] || maxV.isNil())
					maxV[1] = projV[1];
				if(projV[0]<minV[0] || minV.isNil())
					minV[0] = projV[0];
				if(projV[1]<minV[1] || minV.isNil())
					minV[1] = projV[1];

				
				CVector projW = (a[i] * w[j]) * a[i];
				if(projW[0]>maxW[0] || maxW.isNil())
					maxW[0] = projW[0];
				if(projW[1]>maxW[1] || maxW.isNil())
					maxW[1] = projW[1];
				if(projW[0]<minW[0] || minW.isNil())
					minW[0] = projW[0];
				if(projW[1]<minW[1] || minW.isNil())
					minW[1] = projW[1];
				
			}

			//Der Vektor in dessen Richtung der Spieler abgestoßen wird,wird berechnet...
			if((maxV[0]>=minW[0] && maxV[1]>=minW[1])&& (minV[0] <= maxW[0] && minV[1] <= maxW[1])){
				CVector vec = (maxV - minW).getLength() < (minV - maxW).getLength() ? maxV-minW : minV - maxW;
				if(moveVector.getLength() > vec.getLength()){
					moveVector = vec;
					
				}
			} else {
				moveVector = CVector();
				break;
			}

		}

		//...und auf die Position des Spielers übertragen
		if(!moveVector.isNil()){
			position-=moveVector;
			moveVector.normalize();
			moveVector *= MAX_VELOCITY/4;
			velocity = -moveVector;
		}

	}
	setPosition(position);
}