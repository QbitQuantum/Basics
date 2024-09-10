void Law2_ScGeom_CapillaryPhys_Capillarity::checkFusion()
{
	//Reset fusion numbers
	InteractionContainer::iterator ii    = scene->interactions->begin();
        InteractionContainer::iterator iiEnd = scene->interactions->end();
        for( ; ii!=iiEnd ; ++ii ) {
		if ((*ii)->isReal()) {
			if (!hertzOn) static_cast<CapillaryPhys*>((*ii)->phys.get())->fusionNumber=0;
			else static_cast<MindlinCapillaryPhys*>((*ii)->phys.get())->fusionNumber=0;
		}
	}

	list< shared_ptr<Interaction> >::iterator firstMeniscus, lastMeniscus, currentMeniscus;
	Real angle1 = -1.0; Real angle2 = -1.0;
	
	for ( int i=0; i< bodiesMenisciiList.size(); ++i ) { // i is the index (or id) of the body being tested
		CapillaryPhys* cundallInteractionPhysics1=NULL;
		MindlinCapillaryPhys* mindlinInteractionPhysics1=NULL;
		CapillaryPhys* cundallInteractionPhysics2=NULL;
		MindlinCapillaryPhys* mindlinInteractionPhysics2=NULL;
		if ( !bodiesMenisciiList[i].empty() ) {
			lastMeniscus = bodiesMenisciiList[i].end();
			for ( firstMeniscus=bodiesMenisciiList[i].begin(); firstMeniscus!=lastMeniscus; ++firstMeniscus ) { //FOR EACH MENISCUS ON THIS BODY...
				currentMeniscus = firstMeniscus; ++currentMeniscus;
				if (!hertzOn) {
					cundallInteractionPhysics1 = YADE_CAST<CapillaryPhys*>((*firstMeniscus)->phys.get());
					if (i == (*firstMeniscus)->getId1()) angle1=cundallInteractionPhysics1->Delta1;//get angle of meniscus1 on body i
					else angle1=cundallInteractionPhysics1->Delta2;
				}
				else {
					mindlinInteractionPhysics1 = YADE_CAST<MindlinCapillaryPhys*>((*firstMeniscus)->phys.get());
					if (i == (*firstMeniscus)->getId1()) angle1=mindlinInteractionPhysics1->Delta1;//get angle of meniscus1 on body i
					else angle1=mindlinInteractionPhysics1->Delta2;
				}
				for ( ;currentMeniscus!= lastMeniscus; ++currentMeniscus) {//... CHECK FUSION WITH ALL OTHER MENISCII ON THE BODY
					if (!hertzOn) {
						cundallInteractionPhysics2 = YADE_CAST<CapillaryPhys*>((*currentMeniscus)->phys.get());
						if (i == (*currentMeniscus)->getId1()) angle2=cundallInteractionPhysics2->Delta1;//get angle of meniscus2 on body i
						else angle2=cundallInteractionPhysics2->Delta2;
					}
					else {
						mindlinInteractionPhysics2 = YADE_CAST<MindlinCapillaryPhys*>((*currentMeniscus)->phys.get());
						if (i == (*currentMeniscus)->getId1()) angle2=mindlinInteractionPhysics2->Delta1;//get angle of meniscus2 on body i
						else angle2=mindlinInteractionPhysics2->Delta2;
					}
					if (angle1==0 || angle2==0) cerr << "THIS SHOULD NOT HAPPEN!!"<< endl;

					//cerr << "angle1 = " << angle1 << " | angle2 = " << angle2 << endl;

					Vector3r normalFirstMeniscus = YADE_CAST<ScGeom*>((*firstMeniscus)->geom.get())->normal;
					Vector3r normalCurrentMeniscus = YADE_CAST<ScGeom*>((*currentMeniscus)->geom.get())->normal;

					Real normalDot = 0;
					if ((*firstMeniscus)->getId1() ==  (*currentMeniscus)->getId1() ||  (*firstMeniscus)->getId2()  == (*currentMeniscus)->getId2()) normalDot = normalFirstMeniscus.dot(normalCurrentMeniscus);
					else normalDot = - (normalFirstMeniscus.dot(normalCurrentMeniscus));

					Real normalAngle = 0;
					if (normalDot >= 0 ) normalAngle = Mathr::FastInvCos0(normalDot);
					else normalAngle = ((Mathr::PI) - Mathr::FastInvCos0(-(normalDot)));

					if ((angle1+angle2)*Mathr::DEG_TO_RAD > normalAngle) {
						if (!hertzOn) {++(cundallInteractionPhysics1->fusionNumber); ++(cundallInteractionPhysics2->fusionNumber);}//count +1 if 2 meniscii are overlaping
						else {++(mindlinInteractionPhysics1->fusionNumber); ++(mindlinInteractionPhysics2->fusionNumber);}
					};
				}
			}
		}
	}
}