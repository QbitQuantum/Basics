//!			O/
bool Ig2_Sphere_GridConnection_ScGridCoGeom::go(	const shared_ptr<Shape>& cm1,
						const shared_ptr<Shape>& cm2,
						const State& state1, const State& state2, const Vector3r& shift2, const bool& force,
						const shared_ptr<Interaction>& c)
{	// Useful variables :
	const State*    sphereSt  = YADE_CAST<const State*>(&state1);
	//const State*    gridCoSt  = YADE_CAST<const State*>(&state2);
	Sphere*         sphere    = YADE_CAST<Sphere*>(cm1.get());
	GridConnection* gridCo    = YADE_CAST<GridConnection*>(cm2.get());
	GridNode*       gridNo1   = YADE_CAST<GridNode*>(gridCo->node1->shape.get());
	GridNode*       gridNo2   = YADE_CAST<GridNode*>(gridCo->node2->shape.get());
	State*          gridNo1St = YADE_CAST<State*>(gridCo->node1->state.get());
	State*          gridNo2St = YADE_CAST<State*>(gridCo->node2->state.get());
	bool isNew = !c->geom;
	shared_ptr<ScGridCoGeom> scm;
	if (!isNew) scm = YADE_PTR_CAST<ScGridCoGeom>(c->geom);
	else {scm = shared_ptr<ScGridCoGeom>(new ScGridCoGeom());}
	Vector3r segt = gridCo->getSegment();
	Real len = gridCo->getLength();
	Vector3r spherePos = sphereSt->pos - shift2;
	Vector3r branch = spherePos - gridNo1St->pos;
	Vector3r branchN = spherePos - gridNo2St->pos;
	for(int i=0;i<3;i++){
		if(abs(branch[i])<1e-14) branch[i]=0.0;
		if(abs(branchN[i])<1e-14) branchN[i]=0.0;
	}
	Real relPos = branch.dot(segt)/(len*len);
	if(scm->isDuplicate==2 && scm->trueInt!=c->id2)return true;	//the contact will be deleted into the Law.
	scm->isDuplicate=0;
	scm->trueInt=-1;
	
	if(relPos<=0){	// if the sphere projection is BEFORE the segment ...
		if(gridNo1->ConnList.size()>1){//	if the node is not an extremity of the Grid (only one connection)
			for(int unsigned i=0;i<gridNo1->ConnList.size();i++){	// ... loop on all the Connections of the same Node ...
				GridConnection* GC = (GridConnection*)gridNo1->ConnList[i]->shape.get();
				if(GC==gridCo)continue;//	self comparison.
				Vector3r segtCandidate1 = GC->node1->state->pos - gridNo1St->pos; // (be sure of the direction of segtPrev to compare relPosPrev.)
				Vector3r segtCandidate2 = GC->node2->state->pos - gridNo1St->pos;
				Vector3r segtPrev = segtCandidate1.norm()>segtCandidate2.norm() ? segtCandidate1:segtCandidate2;
				for(int j=0;j<3;j++){
					if(abs(segtPrev[j])<1e-14) segtPrev[j]=0.0;
				}
				Real relPosPrev = (branch.dot(segtPrev))/(segtPrev.norm()*segtPrev.norm());
				// ... and check whether the sphere projection is before the neighbours connections too.
				const shared_ptr<Interaction> intr = scene->interactions->find(c->id1,gridNo1->ConnList[i]->getId());
				if(relPosPrev<=0){ //if the sphere projection is outside both the current Connection AND this neighbouring connection, then create the interaction if the neighbour did not already do it before.
					if(intr && intr->isReal() && isNew) return false;
					if(intr && intr->isReal() && !isNew) {scm->isDuplicate=1;/*cout<<"Declare "<<c->id1<<"-"<<c->id2<<" as duplicated."<<endl;*/}
				}
				else{//the sphere projection is outside the current Connection but inside the previous neighbour. The contact has to be handled by the Prev GridConnection, not here.
					if (isNew)return false;
					else {
						//cout<<"The contact "<<c->id1<<"-"<<c->id2<<" HAVE to be copied and deleted NOW."<<endl ;
						scm->isDuplicate=1;
						scm->trueInt=-1;
						return true;}
				}
			}
		}
	}
	
	//Exactly the same but in the case the sphere projection is AFTER the segment.
	else if(relPos>=1){
		if(gridNo2->ConnList.size()>1){
			for(int unsigned i=0;i<gridNo2->ConnList.size();i++){
				GridConnection* GC = (GridConnection*)gridNo2->ConnList[i]->shape.get();
				if(GC==gridCo)continue;//	self comparison.
				Vector3r segtCandidate1 = GC->node1->state->pos - gridNo2St->pos;
				Vector3r segtCandidate2 = GC->node2->state->pos - gridNo2St->pos;
				Vector3r segtNext = segtCandidate1.norm()>segtCandidate2.norm() ? segtCandidate1:segtCandidate2;
				for(int j=0;j<3;j++){
					if(abs(segtNext[j])<1e-14) segtNext[j]=0.0;
				}
				Real relPosNext = (branchN.dot(segtNext))/(segtNext.norm()*segtNext.norm());
				const shared_ptr<Interaction> intr = scene->interactions->find(c->id1,gridNo2->ConnList[i]->getId());
				if(relPosNext<=0){ //if the sphere projection is outside both the current Connection AND this neighbouring connection, then create the interaction if the neighbour did not already do it before.
					if(intr && intr->isReal() && isNew) return false;
					if(intr && intr->isReal() && !isNew) {scm->isDuplicate=1;/*cout<<"Declare "<<c->id1<<"-"<<c->id2<<" as duplicated."<<endl;*/}
				}
				else{//the sphere projection is outside the current Connection but inside the previous neighbour. The contact has to be handled by the Prev GridConnection, not here.
					if (isNew)return false;
					else {//cout<<"The contact "<<c->id1<<"-"<<c->id2<<" HAVE to be copied and deleted NOW."<<endl ;
						scm->isDuplicate=1 ;
						scm->trueInt=-1 ;
						return true;}
				}
			}
		}
	}
	
	else if (isNew && relPos<=0.5){
		if(gridNo1->ConnList.size()>1){//	if the node is not an extremity of the Grid (only one connection)
			for(int unsigned i=0;i<gridNo1->ConnList.size();i++){	// ... loop on all the Connections of the same Node ...
				GridConnection* GC = (GridConnection*)gridNo1->ConnList[i]->shape.get();
				if(GC==gridCo)continue;//	self comparison.
				Vector3r segtCandidate1 = GC->node1->state->pos - gridNo1St->pos; // (be sure of the direction of segtPrev to compare relPosPrev.)
				Vector3r segtCandidate2 = GC->node2->state->pos - gridNo1St->pos;
				Vector3r segtPrev = segtCandidate1.norm()>segtCandidate2.norm() ? segtCandidate1:segtCandidate2;
				for(int j=0;j<3;j++){
					if(abs(segtPrev[j])<1e-14) segtPrev[j]=0.0;
				}
				Real relPosPrev = (branch.dot(segtPrev))/(segtPrev.norm()*segtPrev.norm());
				if(relPosPrev<=0){ //the sphere projection is inside the current Connection and outide this neighbour connection.
					const shared_ptr<Interaction> intr = scene->interactions->find(c->id1,gridNo1->ConnList[i]->getId());
					if( intr && intr->isReal() ){// if an ineraction exist between the sphere and the previous connection, import parameters.
						//cout<<"Copying contact geom and phys from "<<intr->id1<<"-"<<intr->id2<<" to here ("<<c->id1<<"-"<<c->id2<<")"<<endl;
						scm=YADE_PTR_CAST<ScGridCoGeom>(intr->geom);
						c->geom=scm;
						c->phys=intr->phys;
						scm->trueInt=c->id2;
						scm->isDuplicate=2;	//command the old contact deletion.
						isNew=0;
						break;
					}
				}
			}
		}
	}
	
	else if (isNew && relPos>0.5){
		if(gridNo2->ConnList.size()>1){
			for(int unsigned i=0;i<gridNo2->ConnList.size();i++){
				GridConnection* GC = (GridConnection*)gridNo2->ConnList[i]->shape.get();
				if(GC==gridCo)continue;//	self comparison.
				Vector3r segtCandidate1 = GC->node1->state->pos - gridNo2St->pos;
				Vector3r segtCandidate2 = GC->node2->state->pos - gridNo2St->pos;
				Vector3r segtNext = segtCandidate1.norm()>segtCandidate2.norm() ? segtCandidate1:segtCandidate2;
				for(int j=0;j<3;j++){
					if(abs(segtNext[j])<1e-14) segtNext[j]=0.0;
				}
				Real relPosNext = (branchN.dot(segtNext))/(segtNext.norm()*segtNext.norm());
				if(relPosNext<=0){ //the sphere projection is inside the current Connection and outide this neighbour connection.
					const shared_ptr<Interaction> intr = scene->interactions->find(c->id1,gridNo2->ConnList[i]->getId());
					if( intr && intr->isReal() ){// if an ineraction exist between the sphere and the previous connection, import parameters.
						//cout<<"Copying contact geom and phys from "<<intr->id1<<"-"<<intr->id2<<" to here ("<<c->id1<<"-"<<c->id2<<")"<<endl;
						scm=YADE_PTR_CAST<ScGridCoGeom>(intr->geom);
						c->geom=scm;
						c->phys=intr->phys;
						scm->trueInt=c->id2;
						scm->isDuplicate=2;	//command the old contact deletion.
						isNew=0;
						break;
					}
				}
			}
		}
	}
	
	relPos=relPos<0?0:relPos;	//min value of relPos : 0
	relPos=relPos>1?1:relPos;	//max value of relPos : 1
	Vector3r fictiousPos=gridNo1St->pos+relPos*segt;
	Vector3r branchF = fictiousPos - spherePos;
 	Real dist = branchF.norm();
	if(isNew && (dist > (sphere->radius + gridCo->radius))) return false;
	
	//	Create the geometry :
	if(isNew) c->geom=scm;
	scm->radius1=sphere->radius;
	scm->radius2=gridCo->radius;
	scm->id3=gridCo->node1->getId();
	scm->id4=gridCo->node2->getId();
	scm->relPos=relPos;
	Vector3r normal=branchF/dist;
	scm->penetrationDepth = sphere->radius+gridCo->radius-dist;
	scm->fictiousState.pos = fictiousPos;
	scm->contactPoint = spherePos + normal*(scm->radius1 - 0.5*scm->penetrationDepth);
	scm->fictiousState.vel = (1-relPos)*gridNo1St->vel + relPos*gridNo2St->vel;
	scm->fictiousState.angVel =
		((1-relPos)*gridNo1St->angVel + relPos*gridNo2St->angVel).dot(segt/len)*segt/len //twist part : interpolated
		+ segt.cross(gridNo2St->vel - gridNo1St->vel);// non-twist part : defined from nodes velocities
	scm->precompute(state1,scm->fictiousState,scene,c,normal,isNew,shift2,true);//use sphere-sphere precompute (with a virtual sphere)
	return true;
}