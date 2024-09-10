void SoFCIndexedFaceSet::doAction(SoAction * action)
{
    if (action->getTypeId() == Gui::SoGLSelectAction::getClassTypeId()) {
        SoNode* node = action->getNodeAppliedTo();
        if (!node) return; // on no node applied

        // The node we have is the parent of this node and the coordinate node
        // thus we search there for it.
        SoSearchAction sa;
        sa.setInterest(SoSearchAction::FIRST);
        sa.setSearchingAll(false);
        sa.setType(SoCoordinate3::getClassTypeId(), 1);
        sa.apply(node);
        SoPath * path = sa.getPath();
        if (!path) return;

        // make sure we got the node we wanted
        SoNode* coords = path->getNodeFromTail(0);
        if (!(coords && coords->getTypeId().isDerivedFrom(SoCoordinate3::getClassTypeId())))
            return;
        startSelection(action);
        renderSelectionGeometry(static_cast<SoCoordinate3*>(coords)->point.getValues(0));
        stopSelection(action);
    }
    else if (action->getTypeId() == Gui::SoVisibleFaceAction::getClassTypeId()) {
        SoNode* node = action->getNodeAppliedTo();
        if (!node) return; // on no node applied

        // The node we have is the parent of this node and the coordinate node
        // thus we search there for it.
        SoSearchAction sa;
        sa.setInterest(SoSearchAction::FIRST);
        sa.setSearchingAll(false);
        sa.setType(SoCoordinate3::getClassTypeId(), 1);
        sa.apply(node);
        SoPath * path = sa.getPath();
        if (!path) return;

        // make sure we got the node we wanted
        SoNode* coords = path->getNodeFromTail(0);
        if (!(coords && coords->getTypeId().isDerivedFrom(SoCoordinate3::getClassTypeId())))
            return;
        startVisibility(action);
        renderVisibleFaces(static_cast<SoCoordinate3*>(coords)->point.getValues(0));
        stopVisibility(action);
    }

    inherited::doAction(action);
}