bool EntityMotionState::remoteSimulationOutOfSync(uint32_t simulationStep) {
    // NOTE: we only get here if we think we own the simulation
    assert(_body);

    bool parentTransformSuccess;
    Transform localToWorld = _entity->getParentTransform(parentTransformSuccess);
    Transform worldToLocal;
    Transform worldVelocityToLocal;
    if (parentTransformSuccess) {
        localToWorld.evalInverse(worldToLocal);
        worldVelocityToLocal = worldToLocal;
        worldVelocityToLocal.setTranslation(glm::vec3(0.0f));
    }

    // if we've never checked before, our _lastStep will be 0, and we need to initialize our state
    if (_lastStep == 0) {
        btTransform xform = _body->getWorldTransform();
        _serverPosition = worldToLocal.transform(bulletToGLM(xform.getOrigin()));
        _serverRotation = worldToLocal.getRotation() * bulletToGLM(xform.getRotation());
        _serverVelocity = worldVelocityToLocal.transform(getBodyLinearVelocityGTSigma());
        _serverAcceleration = Vectors::ZERO;
        _serverAngularVelocity = worldVelocityToLocal.transform(bulletToGLM(_body->getAngularVelocity()));
        _lastStep = simulationStep;
        _serverActionData = _entity->getActionData();
        _numInactiveUpdates = 1;
        return false;
    }

    #ifdef WANT_DEBUG
    glm::vec3 wasPosition = _serverPosition;
    glm::quat wasRotation = _serverRotation;
    glm::vec3 wasAngularVelocity = _serverAngularVelocity;
    #endif

    int numSteps = simulationStep - _lastStep;
    float dt = (float)(numSteps) * PHYSICS_ENGINE_FIXED_SUBSTEP;

    if (_numInactiveUpdates > 0) {
        const uint8_t MAX_NUM_INACTIVE_UPDATES = 20;
        if (_numInactiveUpdates > MAX_NUM_INACTIVE_UPDATES) {
            // clear local ownership (stop sending updates) and let the server clear itself
            _entity->clearSimulationOwnership();
            return false;
        }
        // we resend the inactive update every INACTIVE_UPDATE_PERIOD
        // until it is removed from the outgoing updates
        // (which happens when we don't own the simulation and it isn't touching our simulation)
        const float INACTIVE_UPDATE_PERIOD = 0.5f;
        return (dt > INACTIVE_UPDATE_PERIOD * (float)_numInactiveUpdates);
    }

    if (!_body->isActive()) {
        // object has gone inactive but our last send was moving --> send non-moving update immediately
        return true;
    }

    _lastStep = simulationStep;
    if (glm::length2(_serverVelocity) > 0.0f) {
        // the entity-server doesn't know where avatars are, so it doesn't do simple extrapolation for children of
        // avatars.  We are trying to guess what values the entity server has, so we don't do it here, either.  See
        // related code in EntitySimulation::moveSimpleKinematics.
        bool ancestryIsKnown;
        _entity->getMaximumAACube(ancestryIsKnown);
        bool hasAvatarAncestor = _entity->hasAncestorOfType(NestableType::Avatar);

        if (ancestryIsKnown && !hasAvatarAncestor) {
            _serverVelocity += _serverAcceleration * dt;
            _serverVelocity *= powf(1.0f - _body->getLinearDamping(), dt);

            // NOTE: we ignore the second-order acceleration term when integrating
            // the position forward because Bullet also does this.
            _serverPosition += dt * _serverVelocity;
        }
    }

    if (_entity->actionDataNeedsTransmit()) {
        _outgoingPriority = _entity->hasActions() ? SCRIPT_GRAB_SIMULATION_PRIORITY : SCRIPT_POKE_SIMULATION_PRIORITY;
        return true;
    }

    if (_entity->shouldSuppressLocationEdits()) {
        return false;
    }

    // Else we measure the error between current and extrapolated transform (according to expected behavior
    // of remote EntitySimulation) and return true if the error is significant.

    // NOTE: math is done in the simulation-frame, which is NOT necessarily the same as the world-frame
    // due to _worldOffset.
    // TODO: compensate for _worldOffset offset here

    // compute position error

    btTransform worldTrans = _body->getWorldTransform();
    glm::vec3 position = worldToLocal.transform(bulletToGLM(worldTrans.getOrigin()));

    float dx2 = glm::distance2(position, _serverPosition);
    const float MAX_POSITION_ERROR_SQUARED = 0.000004f; // corresponds to 2mm
    if (dx2 > MAX_POSITION_ERROR_SQUARED) {
        // we don't mind larger position error when the object has high speed
        // so we divide by speed and check again
        float speed2 = glm::length2(_serverVelocity);
        const float MIN_ERROR_RATIO_SQUARED = 0.0025f; // corresponds to 5% error in 1 second
        const float MIN_SPEED_SQUARED = 1.0e-6f; // corresponds to 1mm/sec
        if (speed2 < MIN_SPEED_SQUARED || dx2 / speed2 > MIN_ERROR_RATIO_SQUARED) {
            #ifdef WANT_DEBUG
                qCDebug(physics) << ".... (dx2 > MAX_POSITION_ERROR_SQUARED) ....";
                qCDebug(physics) << "wasPosition:" << wasPosition;
                qCDebug(physics) << "bullet position:" << position;
                qCDebug(physics) << "_serverPosition:" << _serverPosition;
                qCDebug(physics) << "dx2:" << dx2;
            #endif
            return true;
        }
    }

    if (glm::length2(_serverAngularVelocity) > 0.0f) {
        // compute rotation error
        float attenuation = powf(1.0f - _body->getAngularDamping(), dt);
        _serverAngularVelocity *= attenuation;

        // Bullet caps the effective rotation velocity inside its rotation integration step, therefore
        // we must integrate with the same algorithm and timestep in order achieve similar results.
        for (int i = 0; i < numSteps; ++i) {
            _serverRotation = glm::normalize(computeBulletRotationStep(_serverAngularVelocity,
                                                                       PHYSICS_ENGINE_FIXED_SUBSTEP) * _serverRotation);
        }
    }
    const float MIN_ROTATION_DOT = 0.99999f; // This corresponds to about 0.5 degrees of rotation
    glm::quat actualRotation = worldToLocal.getRotation() * bulletToGLM(worldTrans.getRotation());

    #ifdef WANT_DEBUG
        if ((fabsf(glm::dot(actualRotation, _serverRotation)) < MIN_ROTATION_DOT)) {
            qCDebug(physics) << ".... ((fabsf(glm::dot(actualRotation, _serverRotation)) < MIN_ROTATION_DOT)) ....";

            qCDebug(physics) << "wasAngularVelocity:" << wasAngularVelocity;
            qCDebug(physics) << "_serverAngularVelocity:" << _serverAngularVelocity;

            qCDebug(physics) << "length wasAngularVelocity:" << glm::length(wasAngularVelocity);
            qCDebug(physics) << "length _serverAngularVelocity:" << glm::length(_serverAngularVelocity);

            qCDebug(physics) << "wasRotation:" << wasRotation;
            qCDebug(physics) << "bullet actualRotation:" << actualRotation;
            qCDebug(physics) << "_serverRotation:" << _serverRotation;
        }
    #endif

    return (fabsf(glm::dot(actualRotation, _serverRotation)) < MIN_ROTATION_DOT);
}