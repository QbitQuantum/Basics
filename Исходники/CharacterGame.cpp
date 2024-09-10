void CharacterGame::adjustCamera(long elapsedTime)
{
    static float cameraOffset = 0.0f;

    PhysicsController* physics = Game::getInstance()->getPhysicsController();
    Node* cameraNode = _scene->getActiveCamera()->getNode();

    // Reset camera
    if (cameraOffset != 0.0f)
    {
        cameraNode->translateForward(-cameraOffset);
        cameraOffset = 0.0f;
    }

    Vector3 cameraPosition = cameraNode->getTranslationWorld();
    Vector3 cameraDirection = cameraNode->getForwardVectorWorld();
    cameraDirection.normalize();

    // Get focal point of camera (use the resolved world location of the head joint as a focal point)
    Vector3 focalPoint(cameraPosition + (cameraDirection * CAMERA_FOCUS_DISTANCE));

    Vector3 oldPosition = cameraNode->getTranslationWorld();

    PhysicsController::HitResult result;
    PhysicsCollisionObject* occlusion = NULL;
    do
    {
        // Perform a ray test to check for camera collisions
        if (!physics->sweepTest(cameraNode->getCollisionObject(), focalPoint, &result) || result.object == _character)
            break;

        occlusion = result.object;

        // Step the camera closer to the focal point to resolve the occlusion
        float d = cameraNode->getTranslationWorld().distance(result.point);
        cameraNode->translateForward(d);
        cameraOffset += d;
        while (physics->sweepTest(cameraNode->getCollisionObject(), focalPoint, &result) && result.object == occlusion)
        {
            // Prevent the camera from getting too close to the character.
            // Without this check, it's possible for the camera to fly past the character
            // and essentially end up in an infinite loop here.
            if (cameraNode->getTranslationWorld().distanceSquared(focalPoint) <= 2.0f)
                return;

            cameraNode->translateForward(0.1f);
            cameraOffset += 0.1f;
        }
    } while (true);

    // If the character is closer than 10 world units to the camera, apply transparency to the character
    // so he does not obstruct the view.
    if (occlusion)
    {
        float d = _scene->getActiveCamera()->getNode()->getTranslationWorld().distance(_characterMeshNode->getTranslationWorld());
        float alpha = d < 10 ? (d * 0.1f) : 1.0f;
        _characterMeshNode->setTransparent(alpha < 1.0f);
        _materialParameterAlpha->setValue(alpha);
    }
    else
    {
        _characterMeshNode->setTransparent(false);
        _materialParameterAlpha->setValue(1.0f);
    }

    Vector3 newPosition = cameraNode->getTranslationWorld();
    float distance = oldPosition.distance(newPosition);
    distance = 0;
}