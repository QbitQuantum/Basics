/**
 * @return The intersection which is closest to 'coord'
 */
RS_Vector RS_EntityContainer::getNearestIntersection(const RS_Vector& coord,
                                                     double* dist) {

    double minDist = RS_MAXDOUBLE;  // minimum measured distance
    double curDist = RS_MAXDOUBLE;  // currently measured distance
    RS_Vector closestPoint(false);  // closest found endpoint
    RS_Vector point;                // endpoint found
    RS_VectorSolutions sol;
    RS_Entity* closestEntity;

	closestEntity = getNearestEntity(coord, nullptr, RS2::ResolveAllButTextImage);

	if (closestEntity) {
        for (RS_Entity* en = firstEntity(RS2::ResolveAllButTextImage);
             en;
             en = nextEntity(RS2::ResolveAllButTextImage)) {
            if (
                    !en->isVisible()
					|| en->getParent()->ignoredOnModification()
                    ){
                continue;
            }

            sol = RS_Information::getIntersection(closestEntity,
                                                  en,
                                                  true);

			point=sol.getClosest(coord,&curDist,nullptr);
            if(sol.getNumber()>0 && curDist<minDist){
                closestPoint=point;
                minDist=curDist;
            }

        }
    }
	if(dist && closestPoint.valid) {
        *dist = minDist;
    }

    return closestPoint;
}