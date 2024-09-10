	void DeleteNonClosestIn(){
		assert(data.size() > 1);
		if(data.size() == 2){ //Line
			Vector3f A = ConvertToEigen3Vector(data[1]);
			Vector3f B = ConvertToEigen3Vector(data[0]);
			if((-A).dot(B-A) <= 0){ //A is closest
				data[0] = data[1];
				data.pop_back();
				dataA[0] = dataA[1];
				dataB[0] = dataB[1];
				dataA.pop_back();
				dataB.pop_back();
			}else if((-B).dot(A-B) <= 0){ //B is closest
				data.pop_back();
				dataA.pop_back();
				dataB.pop_back();
			}else{ //AB is closest
				return;
			}

		}else if(data.size() == 3){ //Triangle
			Vector3f A = ConvertToEigen3Vector(data[2]);
			Vector3f B = ConvertToEigen3Vector(data[1]);
			Vector3f C = ConvertToEigen3Vector(data[0]);
			Vector3f AB = B -A;
			Vector3f AC = C- A;
			Vector3f BC = C-B;
			Vector3f Nab = AC.cross(AB).cross(AB);
			Vector3f Nac = AB.cross(AC).cross(AC);
			Vector3f Nbc = (-AB).cross(BC).cross(BC);

			if(AB.dot(-A) <= 0 && AC.dot(-A)<=0){ //A is closest;
				data[0] = data[2];
				dataA[0] = dataA[2];
				dataB[0] = dataB[2];
				data.pop_back();
				data.pop_back();
				dataA.pop_back();
				dataA.pop_back();
				dataB.pop_back();
				dataB.pop_back();
			}else if ((-AB).dot(-B) <=0 && BC.dot(-B)<=0){//B is closest
				data[0] = data[1];
				dataA[0] = dataA[1];
				dataB[0] = dataB[1];
				data.pop_back();
				data.pop_back(); 
				dataA.pop_back();
				dataA.pop_back();
				dataB.pop_back();
				dataB.pop_back();
			}else if((-AC).dot(-C)<= 0 && (-BC).dot(-C) <=0){//C is closest
				data.pop_back();
				data.pop_back();
				dataA.pop_back();
				dataA.pop_back();
				dataB.pop_back();
				dataB.pop_back();
			}else if(Nab.dot(-A)>=0 && AB.dot(-A) > 0){//AB is closest
				data[0] = data[1];//BBA
				data[1] = data[2];//BAA
				data.pop_back();//BA
				dataA[0] = dataA[1];
				dataA[1] = dataA[2];
				dataB[0] = dataB[1];
				dataB[1] = dataB[2];
				dataA.pop_back();
				dataB.pop_back();
			}else if(Nac.dot(-A) >=0 && AC.dot(-A) > 0){//AC is closest
				data[1] = data[2]; //CAA
				data.pop_back();
				dataA[1] = dataA[2];
				dataB[1] = dataB[2];
				dataA.pop_back();
				dataB.pop_back();
			}else if(Nbc.dot(-B) >=0 && BC.dot(-B) > 0){//BC is closest
				data.pop_back();
				dataA.pop_back();
				dataB.pop_back();
			}else{
				return;
			}
		}else{ //Tetrahedron
			unsigned int posPiece1, posPiece2, posPiece3;
			Vector3f A = ConvertToEigen3Vector(data[3]);
			Vector3f B = ConvertToEigen3Vector(data[2]);
			Vector3f C = ConvertToEigen3Vector(data[1]);
			Vector3f D = ConvertToEigen3Vector(data[0]);
			Vector3f AO = -A;
			Vector3f BO = -B;
			Vector3f CO = -C;
			Vector3f DO = -D;
			Vector3f AB = B-A;
			Vector3f AC = C-A;
			Vector3f AD = D-A;
			Vector3f Nabc = AB.cross(AC);
			Vector3f Nabd = AB.cross(AD);
			Vector3f Nacd = AC.cross(AD);
			Vector3f Nbcd = (C-B).cross(D-B);
			if((Nabc.dot(AO)*(Nabc.dot(AD))<0)){///ABC to check
				posPiece1 = 1;
				posPiece2 = 2;
				posPiece3 = 3;
			}else if(Nabd.dot(AO) * (Nabd.dot(AC) < 0)){ //ABD to check
				posPiece1 = 0;
				posPiece2 = 2;
				posPiece3 = 3;
			}else if(Nacd.dot(AO)*Nacd.dot(AB)<0){//ACD to check
				posPiece1 = 0;
				posPiece2 = 1;
				posPiece3 = 3;
			}else if(Nbcd.dot(BO) * Nbcd.dot(A-B) < 0){//BCD to check
				posPiece1 = 0;
				posPiece2 = 1;
				posPiece3 = 2;
			}else{ return;}

			Vector3f TriC = ConvertToEigen3Vector(data[posPiece1]);
			Vector3f TriB = ConvertToEigen3Vector(data[posPiece2]);
			Vector3f TriA = ConvertToEigen3Vector(data[posPiece3]);
			Vec3f Ac = dataA[posPiece1];
			Vec3f Ab = dataA[posPiece2];
			Vec3f Aa = dataA[posPiece3];
			Vec3f Bc = dataB[posPiece1];
			Vec3f Bb = dataB[posPiece2];
			Vec3f Ba = dataB[posPiece3];
			Vector3f TriAO = -TriA;
			Vector3f TriBO = -TriB;
			Vector3f TriCO = -TriC;
			Vector3f TriAB = TriB-TriA;
			Vector3f TriAC = TriC-TriA;
			Vector3f TriBC = TriC-TriB;
			Vector3f TriNab = TriAC.cross(TriAB).cross(TriAB);
			Vector3f TriNac = TriAB.cross(TriAC).cross(TriAC);
			Vector3f TriNbc = (TriA-TriB).cross(TriBC).cross(TriBC);

			if(TriAB.dot(TriAO) <= 0 && TriAC.dot(TriAO) <= 0){ //A is closest
				data.clear();
				dataA.clear();
				dataB.clear();
				data.push_back(ConvertToOM3Vector(TriA));
				dataA.push_back(Aa);
				dataB.push_back(Ba);
			}else if((TriA- TriB).dot(TriBO) <= 0 && TriBC.dot(TriBO)<=0){//B is closest
				data.clear();
				dataA.clear();
				dataB.clear();
				data.push_back(ConvertToOM3Vector(TriB));
				dataA.push_back(Ab);
				dataB.push_back(Bb);
			}else if((TriA-TriC).dot(TriCO) <= 0 && (TriB-TriC).dot(TriCO) <= 0){ //C is closest
				data.clear();
				dataA.clear();
				dataB.clear();
				data.push_back(ConvertToOM3Vector(TriC));
				dataA.push_back(Ac);
				dataB.push_back(Bc);
			}else if(TriNab.dot(TriAO)>=0 && TriAB.dot(TriAO) > 0){//AB is closest
				data.clear();
				dataA.clear();
				dataB.clear();
				data.push_back(ConvertToOM3Vector(TriB));
				data.push_back(ConvertToOM3Vector(TriA));
				dataA.push_back(Ab);
				dataA.push_back(Aa);
				dataB.push_back(Bb);
				dataB.push_back(Ba);
			}else if(TriNac.dot(TriAO) >= 0 && TriAC.dot(TriAO) > 0){ //AC is closest
				data.clear();
				dataA.clear();
				dataB.clear();
				data.push_back(ConvertToOM3Vector(TriC));
				data.push_back(ConvertToOM3Vector(TriA));
				dataA.push_back(Ac);
				dataA.push_back(Aa);
				dataB.push_back(Bc);
				dataB.push_back(Ba);
			}else if(TriNbc.dot(TriBO) >= 0 && TriBC.dot(TriBO) > 0){//BC closest
				data.clear();
				dataA.clear();
				dataB.clear();
				data.push_back(ConvertToOM3Vector(TriC));
				data.push_back(ConvertToOM3Vector(TriB));
				dataA.push_back(Ac);
				dataA.push_back(Ab);
				dataB.push_back(Bc);
				dataB.push_back(Bb);
			}else{//ABC closest
				data.clear();
				dataA.clear();
				dataB.clear();
				data.push_back(ConvertToOM3Vector(TriC));
				data.push_back(ConvertToOM3Vector(TriB));
				data.push_back(ConvertToOM3Vector(TriA));
				dataA.push_back(Ac);
				dataA.push_back(Ab);
				dataA.push_back(Aa);
				dataB.push_back(Bc);
				dataB.push_back(Bb);
				dataB.push_back(Ba);
			}
		}
	}