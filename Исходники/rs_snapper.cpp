/**
 * Catches an entity which is close to the given position 'pos'.
 *
 * @param pos A graphic coordinate.
 * @param level The level of resolving for iterating through the entity
 *        container
 * @return Pointer to the entity or NULL.
 */
RS_Entity* RS_Snapper::catchEntity(const RS_Vector& pos,
                                   RS2::ResolveLevel level) {

    RS_DEBUG->print("RS_Snapper::catchEntity");

	// set default distance for points inside solids
    double dist = graphicView->toGraphDX(snapRange)*0.9;

    RS_Entity* entity = container->getNearestEntity(pos, &dist, level);

	int idx = -1;
	if (entity!=NULL && entity->getParent()!=NULL) {
		idx = entity->getParent()->findEntity(entity);
	}

    if (entity!=NULL && dist<=graphicView->toGraphDX(snapRange)) {
        // highlight:
    	RS_DEBUG->print("RS_Snapper::catchEntity: found: %d", idx);
        return entity;
    } else {
    	RS_DEBUG->print("RS_Snapper::catchEntity: not found");
        return NULL;
    }
    RS_DEBUG->print("RS_Snapper::catchEntity: OK");
}