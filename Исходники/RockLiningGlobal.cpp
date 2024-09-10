void RockLiningGlobal::action(){
	const double PI = 3.14159;
	if (openingCreated == true && installed == false){
		
		double angleInterval = 2.0*PI/static_cast<double>(totalNodes);
		for (int n=0; n<totalNodes;n++){
			double currentAngle = 0.0 + n*angleInterval; /* from 0 degrees east */
			double unitX = cos(currentAngle);
			double unitY = sin(currentAngle);
			Vector3r searchDir(unitX,0,unitY);

			vector<double> distanceFrOpening; vector<int> IDs;
			double outerRadius = openingRad + 1.0;
			FOREACH(const shared_ptr<Body>& b, *scene->bodies){
				if (!b) continue;
				if (b->isClump() == true) continue;
				PotentialBlock* pb=static_cast<PotentialBlock*>(b->shape.get()); 
				if(!pb) continue;
				if(pb->isBoundary == true || pb->erase== true || pb->isLining==true){continue;}	
				State* state1 = b->state.get();				
				Vector3r intersectionPt(0,0,0);
				if ( installLining(pb,  state1, startingPoint, searchDir, outerRadius, intersectionPt )){
					IDs.push_back(b->id);
					distanceFrOpening.push_back((intersectionPt-startingPoint).norm());
					//std::cout<<"currentAngle: "<<currentAngle<<", b->id: "<<b->id<<", dist: "<<(intersectionPt-startingPoint).norm()<<endl;
				}
			}

			/* find closest block */
			int totalBlocks = IDs.size(); 
			double closestDistance = 100000.0; 
			int closestID=0;
			for (int i=0; i<totalBlocks; i++){
				if ( distanceFrOpening[i] < closestDistance){
					closestID = IDs[i];
					closestDistance = distanceFrOpening[i];
				}			
			}
			stickIDs.push_back(closestID);
			IDs.clear();distanceFrOpening.clear();
//std::cout<<"closestID: "<<closestID<<endl;
	
			/* find intersection with edges of polygon */
			Vector3r jointIntersection (0,0,0); 
			State* state1 = Body::byId(closestID,scene)->state.get();
			Shape* shape1 = Body::byId(closestID,scene)->shape.get();
			PotentialBlock *pb=static_cast<PotentialBlock*>(shape1);
			int totalPlanes = pb->a.size();
			int intersectNo = 0;
			Vector3r nodeLocalPos(0,0,0); Vector3r nodeGlobalPos(0,0,0);
//std::cout<<"totalPlanes: "<<totalPlanes<<endl;
			double closestPlaneDist = 1000000;
			for (int i=0; i<totalPlanes; i++){						
					Vector3r plane = state1->ori*Vector3r(pb->a[i], pb->b[i], pb->c[i]); double planeD = plane.dot(state1->pos) + pb->d[i] +pb->r;
					if ( intersectPlane(pb, state1,startingPoint,searchDir, outerRadius, jointIntersection, plane, planeD)){
						double distance = jointIntersection.norm();
						if (distance < closestPlaneDist){
							closestPlaneDist = distance;
							nodeLocalPos = state1->ori.conjugate()*(jointIntersection-state1->pos);
							nodeGlobalPos=jointIntersection;
						}
						
					}
			}
			if(nodeGlobalPos.norm() > 1.03*openingRad){ nodeGlobalPos=1.03*openingRad*searchDir;} 
			//if(nodeGlobalPos.norm() < 0.98*openingRad){ continue;} 
			//initOverlap = interfaceTension/interfaceStiffness;
			nodeGlobalPos = nodeGlobalPos + searchDir*initOverlap;
			localCoordinates.push_back(nodeLocalPos);
			refPos.push_back(nodeGlobalPos);
			int nodeID = insertNode(nodeGlobalPos, lumpedMass, contactLength);
			blockIDs.push_back(nodeID); //(nodeID); //(closestID);
			refOri.push_back(Quaternionr::Identity()); //(state1->ori);
			installed = true;
			
			axialForces.push_back(0.0);
			shearForces.push_back(0.0);
			moment.push_back(0.0);
			sigmaMax.push_back(0.0);
			sigmaMin.push_back(0.0);
			displacement.push_back(0.0);
			radialDisplacement.push_back(0.0);
		}
		totalNodes=blockIDs.size();

	
		/* Assembling global stiffness matrix */
		for (int n=0; n<totalNodes;n++){
			int nextID = n+1;
			if(nextID==totalNodes){nextID=0;}
			double Length = (refPos[nextID]-refPos[n]).norm();
			lengthNode.push_back(Length);
			
			Vector3r localDir = refPos[nextID]-refPos[n];
			localDir.normalize(); refDir.push_back(localDir);
			double angle = acos(localDir.dot(Vector3r(1,0,0)));
			Vector3r signAngle =  Vector3r(1,0.0,0).cross(localDir); 

			if (signAngle.dot(Vector3r(0,-1.0,0)) < 0.0){angle =2.0*PI - angle;}			
			refAngle.push_back(angle);
			std::cout<<"angle "<<n<<" : "<<angle/PI*180.0<<endl;

			
		}
	}