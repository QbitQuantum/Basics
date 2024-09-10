    bool isVisibleFace(int faceIndex, const SbVec2f& pos, Gui::View3DInventorViewer* viewer)
    {
        SoSeparator* root = new SoSeparator;
        root->ref();
        root->addChild(viewer->getSoRenderManager()->getCamera());
        root->addChild(vp->getRoot());

        SoSearchAction searchAction;
        searchAction.setType(PartGui::SoBrepFaceSet::getClassTypeId());
        searchAction.setInterest(SoSearchAction::FIRST);
        searchAction.apply(root);
        SoPath* selectionPath = searchAction.getPath();

        SoRayPickAction rp(viewer->getSoRenderManager()->getViewportRegion());
        rp.setNormalizedPoint(pos);
        rp.apply(selectionPath);
        root->unref();

        SoPickedPoint* pick = rp.getPickedPoint();
        if (pick) {
            const SoDetail* detail = pick->getDetail();
            if (detail && detail->isOfType(SoFaceDetail::getClassTypeId())) {
                int index = static_cast<const SoFaceDetail*>(detail)->getPartIndex();
                if (faceIndex != index)
                    return false;
                SbVec3f dir = viewer->getViewDirection();
                const SbVec3f& nor = pick->getNormal();
                if (dir.dot(nor) > 0)
                    return false; // bottom side points to user
                return true;
            }
        }

        return false;
    }