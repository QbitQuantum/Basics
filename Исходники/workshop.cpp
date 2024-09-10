void workshopScene::update(sceneInfo &info)
{
    gWorld->btWorld->stepSimulation(1.f/60.f);

    mousevelx = mousevelx * 0.95f + info.dmousex * 0.2f;
    mousevely = mousevely * 0.95f + info.dmousey * 0.2f;

    if (info.keys.held.MouseM)
    {
        camera.pitch -= info.dmousey * 0.02;
        camera.yaw -= info.dmousex * 0.02;
        camera.orientationFromAngles();
    }

    sceneInfo::keyState &keys = info.keys;
    if (!glfwGetKey('E'))
    {
        if (keys.held.W)
        {
            camera.position += camera.forward * 0.1;
        }
        else if (keys.held.S)
        {
            camera.position -= camera.forward * 0.1;
        }
        if (keys.held.D)
        {
            camera.position += camera.right * 0.1;
        }
        else if (keys.held.A)
        {
            camera.position -= camera.right * 0.1;
        }
    }
    if (info.captureMouse)
    {
        if (mouseWasCaptured)
        {
            cursorx += info.dmousex;
            cursory += info.dmousey;
            if (cursorx < 0)
                cursorx = 0;
            if (cursorx > info.width)
                cursorx = info.width;
            if (cursory < 0)
                cursory = 0;
            if (cursory > info.height)
                cursory = info.height;
        }
        else
        {
            cursorx = info.lastmousex;
            cursory = info.lastmousey;
        }
    }
    else if (mouseWasCaptured)
    {
        glfwSetMousePos(cursorx, cursory);
    }
    mouseWasCaptured = info.captureMouse;

    if (info.keys.held.space && selectedItem < partnames.size())
    {
        int initialcount = gWorld->objects.size();
        loadAssembly(partnames[selectedItem], btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)), path, gWorld);
        for (unsigned int i = initialcount; i < gWorld->objects.size(); i++)
            gWorld->objects[i]->body->setDamping(0.95f, 0.96f);
    }

    if (cursorx < UI_SIZE)
    {
        if (keys.newPress.MouseL)
        {
            selectedItem = (cursory - 4) / (UI_SIZE + 8);
            selectedTool = -1;
        }
    }
    else if (cursory > info.height - UI_SMALL - 16)
    {
        if (keys.newPress.MouseL)
        {
            selectedTool = (cursorx - UI_SIZE - 16 - 8) / (UI_SMALL + 8);
            selectedItem = -1;
        }
    }
    else
    {
        mouseRayDir = camera.forward + camera.right * (cursorx - info.width / 2) / (float)info.height * 2 - camera.up * (cursory - info.height / 2) / (float)info.height * 2;
        btVector3 raystart = camera.position;
        btVector3 rayend = raystart + mouseRayDir * 100;
        mouseRayCallback = btCollisionWorld::ClosestRayResultCallback(raystart, rayend);
        gWorld->btWorld->rayTest(raystart, rayend, mouseRayCallback);

        if (keys.newPress.MouseL && mouseRayCallback.hasHit())
        {
            mouseHeldBody = (btRigidBody*)mouseRayCallback.m_collisionObject;
            if (selectedItem >= 0)
            {
                if (selectedItem < partnames.size())
                {
                    int initialcount = gWorld->objects.size();
                    btTransform trans(btQuaternion(0, 0, 0, 1), mouseRayCallback.m_hitPointWorld + mouseRayCallback.m_hitNormalWorld * 1.f);
                    loadAssembly(partnames[selectedItem], trans, path, gWorld);
                    for (unsigned int i = initialcount; i < gWorld->objects.size(); i++)
                        gWorld->objects[i]->body->setDamping(0.95f, 0.96f);
                }
            }
            else if (selectedTool == 0)
            {
                mousePerpDist = camera.forward.dot(mouseRayCallback.m_hitPointWorld - raystart);
                mouseHeldBody->setDamping(0.995, 0.98);
                mouseHeldBody->activate();
                btVector3 localPivot = mouseHeldBody->getCenterOfMassTransform().inverse() * mouseRayCallback.m_hitPointWorld;
                mouseConstraint = new btGeneric6DofConstraint(*mouseHeldBody, btTransform(btQuaternion(0, 0, 0, 1), localPivot), false);
                if (glfwGetKey('E'))
                {
                     mouseConstraint->setAngularLowerLimit(btVector3(0, 0, 0));
                    mouseConstraint->setAngularUpperLimit(btVector3(0, 0, 0));
                }
                gWorld->btWorld->addConstraint(mouseConstraint);
            }
            else if (selectedTool == 1)
            {
                if (!mouseHeldBody->isStaticObject())
                {
                    if (!axisHasFirst)
                    {
                        axisHasFirst = true;
                        axisResult = mouseRayCallback;
                        axisFirstPivot = mouseHeldBody->getCenterOfMassTransform().inverse() * axisResult.m_hitPointWorld;
                        axisFirstNormal = btTransform(mouseHeldBody->getCenterOfMassTransform().inverse().getRotation(), btVector3(0, 0, 0)) * axisResult.m_hitNormalWorld;
                        std::cout << "First point for axis.\n";
                    }
                    else
                    {
                        btVector3 axisSecondNormal = btTransform(mouseHeldBody->getCenterOfMassTransform().inverse().getRotation(), btVector3(0, 0, 0)) * mouseRayCallback.m_hitNormalWorld;
                        btVector3 axisSecondPivot = mouseHeldBody->getCenterOfMassTransform().inverse() * mouseRayCallback.m_hitPointWorld + axisSecondNormal * 0.05;
                        gWorld->addConstraint(new btHingeConstraint(*(btRigidBody*)axisResult.m_collisionObject, *mouseHeldBody, axisFirstPivot, axisSecondPivot, -axisFirstNormal, axisSecondNormal));
                        mouseHeldBody->activate();
                        axisHasFirst = false;
                    }
                }
            }
            else if (selectedTool == 2)
            {
                btRigidBody *body = (btRigidBody*)mouseRayCallback.m_collisionObject;
                if (!body->isStaticObject())
                    gWorld->removeBody(body);
            }
        }
    }

    if (mouseConstraint)
    {
        if (keys.held.MouseL)
        {
            mousePerpDist *= pow(1.1, keys.dmouseWheel);
            mouseConstraint->getFrameOffsetA().setOrigin(camera.position + mouseRayDir * mousePerpDist);        // note that raydir is not unit length: it stretches from the camera to the near plane.
        }
        else
        {
            mouseHeldBody->setDamping(0.95, 0.96);
            gWorld->btWorld->removeConstraint(mouseConstraint);
            delete mouseConstraint;
            mouseConstraint = 0;
        }
        if (glfwGetKey('E'))
        {
            btTransform invrotate;
            mouseHeldBody->getMotionState()->getWorldTransform(invrotate);
            invrotate = invrotate.inverse();
            if (keys.held.W)
                mouseHeldBody->applyImpulse(invrotate * camera.forward, invrotate * camera.up);
            if (keys.held.S)
                mouseHeldBody->applyImpulse(-camera.forward, camera.up);
            if (keys.held.A)
                mouseHeldBody->applyImpulse(-camera.right, camera.forward);
            if (keys.held.D)
                mouseHeldBody->applyImpulse(camera.right, camera.forward);
        }
    }

    if (axisHasFirst && selectedTool != 1)
        axisHasFirst = false;
}