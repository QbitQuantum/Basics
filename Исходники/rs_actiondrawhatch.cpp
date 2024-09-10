void RS_ActionDrawHatch::trigger() {

    RS_DEBUG->print("RS_ActionDrawHatch::trigger()");

    //if (pos.valid) {
    //deletePreview();
	RS_Entity* e;

	// deselect unhatchable entities:
    for (e=container->firstEntity(RS2::ResolveNone); e!=NULL;
            e=container->nextEntity(RS2::ResolveNone)) {
        if (e->isSelected() && 
            (e->rtti()==RS2::EntityHatch ||
            /* e->rtti()==RS2::EntityEllipse ||*/ e->rtti()==RS2::EntityPoint ||
             e->rtti()==RS2::EntityMText || e->rtti()==RS2::EntityText ||
			 RS_Information::isDimension(e->rtti()))) {
			e->setSelected(false);
        }
    }
    for (e=container->firstEntity(RS2::ResolveAll); e!=NULL;
            e=container->nextEntity(RS2::ResolveAll)) {
        if (e->isSelected() && 
            (e->rtti()==RS2::EntityHatch ||
            /* e->rtti()==RS2::EntityEllipse ||*/ e->rtti()==RS2::EntityPoint ||
             e->rtti()==RS2::EntityMText || e->rtti()==RS2::EntityText ||
			 RS_Information::isDimension(e->rtti()))) {
			e->setSelected(false);
        }
    }

	// look for selected contours:
    bool haveContour = false;
    for (e=container->firstEntity(RS2::ResolveAll); e!=NULL;
            e=container->nextEntity(RS2::ResolveAll)) {
        if (e->isSelected()) {
            haveContour = true;
        }
    }

    if (!haveContour) {
        std::cerr << "no contour selected\n";
        return;
    }

    hatch = new RS_Hatch(container, data);
    hatch->setLayerToActive();
    hatch->setPenToActive();
    RS_EntityContainer* loop = new RS_EntityContainer(hatch);
    loop->setPen(RS_Pen(RS2::FlagInvalid));

    // add selected contour:
    for (RS_Entity* e=container->firstEntity(RS2::ResolveAll); e!=NULL;
            e=container->nextEntity(RS2::ResolveAll)) {

        if (e->isSelected()) {
            e->setSelected(false);
			// entity is part of a complex entity (spline, polyline, ..):
            if (e->getParent()!=NULL &&
// RVT - Don't de-delect the parent EntityPolyline, this is messing up the getFirst and getNext iterators
//			    (e->getParent()->rtti()==RS2::EntitySpline ||
//				 e->getParent()->rtti()==RS2::EntityPolyline)) {
                (e->getParent()->rtti()==RS2::EntitySpline)) {
                e->getParent()->setSelected(false);
            }
            RS_Entity* cp = e->clone();
            cp->setPen(RS_Pen(RS2::FlagInvalid));
            cp->reparent(loop);
            loop->addEntity(cp);
        }
    }

    hatch->addEntity(loop);
	if (hatch->validate()) {
		container->addEntity(hatch);

		if (document) {
			document->startUndoCycle();
			document->addUndoable(hatch);
			document->endUndoCycle();
		}
		hatch->update();

		graphicView->redraw(RS2::RedrawDrawing);

		RS_DIALOGFACTORY->commandMessage(tr("Hatch created successfully."));
	}
	else {
		delete hatch;
		hatch = NULL;
		RS_DIALOGFACTORY->commandMessage(tr("Invalid hatch area. Please check that "
		"the entities chosen form one or more closed contours."));
	}
    //}
}