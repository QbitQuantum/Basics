    /// Default shadow camera setup implementation
    void DefaultShadowCameraSetup::getShadowCamera (const SceneManager *sm, const Camera *cam, 
        const Viewport *vp, const Light *light, Camera *texCam, size_t iteration) const
    {
        Vector3 pos, dir;

        // reset custom view / projection matrix in case already set
        texCam->setCustomViewMatrix(false);
        texCam->setCustomProjectionMatrix(false);
        texCam->setNearClipDistance(light->_deriveShadowNearClipDistance(cam));
        texCam->setFarClipDistance(light->_deriveShadowFarClipDistance(cam));

        // get the shadow frustum's far distance
        Real shadowDist = light->getShadowFarDistance();
        if (!shadowDist)
        {
            // need a shadow distance, make one up
            shadowDist = cam->getNearClipDistance() * 300;
        }
        Real shadowOffset = shadowDist * (sm->getShadowDirLightTextureOffset());

        // Directional lights 
        if (light->getType() == Light::LT_DIRECTIONAL)
        {
            // set up the shadow texture
            // Set ortho projection
            texCam->setProjectionType(PT_ORTHOGRAPHIC);
            // set ortho window so that texture covers far dist
            texCam->setOrthoWindow(shadowDist * 2, shadowDist * 2);

            // Calculate look at position
            // We want to look at a spot shadowOffset away from near plane
            // 0.5 is a little too close for angles
            Vector3 target = cam->getDerivedPosition() + 
                (cam->getDerivedDirection() * shadowOffset);

            // Calculate direction, which same as directional light direction
            dir = - light->getDerivedDirection(); // backwards since point down -z
            dir.normalise();

            // Calculate position
            // We want to be in the -ve direction of the light direction
            // far enough to project for the dir light extrusion distance
            pos = target + dir * sm->getShadowDirectionalLightExtrusionDistance();

            // Round local x/y position based on a world-space texel; this helps to reduce
            // jittering caused by the projection moving with the camera
            // Viewport is 2 * near clip distance across (90 degree fov)
            //~ Real worldTexelSize = (texCam->getNearClipDistance() * 20) / vp->getActualWidth();
            //~ pos.x -= fmod(pos.x, worldTexelSize);
            //~ pos.y -= fmod(pos.y, worldTexelSize);
            //~ pos.z -= fmod(pos.z, worldTexelSize);
            Real worldTexelSize = (shadowDist * 2) / texCam->getViewport()->getActualWidth();

             //get texCam orientation

             Vector3 up = Vector3::UNIT_Y;
             // Check it's not coincident with dir
             if (Math::Abs(up.dotProduct(dir)) >= 1.0f)
             {
                // Use camera up
                up = Vector3::UNIT_Z;
             }
             // cross twice to rederive, only direction is unaltered
             Vector3 left = dir.crossProduct(up);
             left.normalise();
             up = dir.crossProduct(left);
             up.normalise();
             // Derive quaternion from axes
             Quaternion q;
             q.FromAxes(left, up, dir);

             //convert world space camera position into light space
             Vector3 lightSpacePos = q.Inverse() * pos;
             
             //snap to nearest texel
             lightSpacePos.x -= fmod(lightSpacePos.x, worldTexelSize);
             lightSpacePos.y -= fmod(lightSpacePos.y, worldTexelSize);

             //convert back to world space
             pos = q * lightSpacePos;
            
        }
        // Spotlight
        else if (light->getType() == Light::LT_SPOTLIGHT)
        {
            // Set perspective projection
            texCam->setProjectionType(PT_PERSPECTIVE);
            // set FOV slightly larger than the spotlight range to ensure coverage
            Radian fovy = light->getSpotlightOuterAngle()*1.2;
            // limit angle
            if (fovy.valueDegrees() > 175)
                fovy = Degree(175);
            texCam->setFOVy(fovy);

            // Calculate position, which same as spotlight position
            pos = light->getDerivedPosition();

            // Calculate direction, which same as spotlight direction
            dir = - light->getDerivedDirection(); // backwards since point down -z
            dir.normalise();
        }
        // Point light
        else
        {
            // Set perspective projection
            texCam->setProjectionType(PT_PERSPECTIVE);
            // Use 120 degree FOV for point light to ensure coverage more area
            texCam->setFOVy(Degree(120));

            // Calculate look at position
            // We want to look at a spot shadowOffset away from near plane
            // 0.5 is a little too close for angles
            Vector3 target = cam->getDerivedPosition() + 
                (cam->getDerivedDirection() * shadowOffset);

            // Calculate position, which same as point light position
            pos = light->getDerivedPosition();

            dir = (pos - target); // backwards since point down -z
            dir.normalise();
        }

        // Finally set position
        texCam->setPosition(pos);

        // Calculate orientation based on direction calculated above
        /*
        // Next section (camera oriented shadow map) abandoned
        // Always point in the same direction, if we don't do this then
        // we get 'shadow swimming' as camera rotates
        // As it is, we get swimming on moving but this is less noticeable

        // calculate up vector, we want it aligned with cam direction
        Vector3 up = cam->getDerivedDirection();
        // Check it's not coincident with dir
        if (up.dotProduct(dir) >= 1.0f)
        {
        // Use camera up
        up = cam->getUp();
        }
        */
        Vector3 up = Vector3::UNIT_Y;
        // Check it's not coincident with dir
        if (Math::Abs(up.dotProduct(dir)) >= 1.0f)
        {
            // Use camera up
            up = Vector3::UNIT_Z;
        }
        // cross twice to rederive, only direction is unaltered
        Vector3 left = dir.crossProduct(up);
        left.normalise();
        up = dir.crossProduct(left);
        up.normalise();
        // Derive quaternion from axes
        Quaternion q;
        q.FromAxes(left, up, dir);
        texCam->setOrientation(q);
    }