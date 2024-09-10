    virtual void apply(SoNode* node)
    {
        if (!headlightRot) {
            SoSearchAction sa;
            sa.setNode(viewer->getHeadlight());
            sa.apply(viewer->getSceneRoot());
            SoFullPath* fullPath = (SoFullPath*) sa.getPath();
            if (fullPath) {
                SoGroup *group = (SoGroup*) fullPath->getNodeFromTail(1);
                headlightRot = (SoRotation*) group->getChild(0);
                if (!headlightRot->isOfType(SoRotation::getClassTypeId()))
                    headlightRot = 0;
            }
        }

        const SbViewportRegion vpr = getViewportRegion();
        const SbVec2s & size = vpr.getViewportSizePixels();

        const int width = size[0];
        const int height = size[1];

        const int vpsize = width / 2;

        SoCamera * camera = viewer->getCamera();

        const SbVec3f position = camera->position.getValue();
        const SbRotation orientation = camera->orientation.getValue();
        const float nearplane = camera->nearDistance.getValue();
        const float farplane = camera->farDistance.getValue();

        camera->enableNotify(false);

        // Front View
        rotateCamera(SbRotation(SbVec3f(0,0,1), M_PI));

        SbViewportRegion vp;
        vp.setViewportPixels(SbVec2s(0, height-width/2), SbVec2s(width, width/2) );
        setViewportRegion(vp);

        SoGLRenderAction::apply(node);

        // Left View
        SbRotation r1(SbVec3f(0,0,1), -M_PI/2);

        rotateCamera(r1*SbRotation(SbVec3f(0,1,0), -M_PI/2));
        
        vp.setViewportPixels(SbVec2s(0, height-width), SbVec2s(width/2, width) );
        setViewportRegion(vp);

        SoGLRenderAction::apply(node);

        // Right View
        rotateCamera(SbRotation(SbVec3f(0,1,0), -M_PI));

        vp.setViewportPixels(SbVec2s(width/2, height-width), SbVec2s(width/2, width) );
        setViewportRegion(vp);

        SoGLRenderAction::apply(node);

        setViewportRegion(vpr);

        camera->position = position;
        camera->orientation = orientation;
        camera->enableNotify(true);

        // Restore original viewport region
        setViewportRegion(vpr);
    }