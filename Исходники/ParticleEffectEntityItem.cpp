void ParticleEffectEntityItem::stepSimulation(float deltaTime) {

    _particleMinBound = glm::vec3(-1.0f, -1.0f, -1.0f);
    _particleMaxBound = glm::vec3(1.0f, 1.0f, 1.0f);

    // update particles between head and tail
    for (quint32 i = _particleHeadIndex; i != _particleTailIndex; i = (i + 1) % _maxParticles) {
        _particleLifetimes[i] -= deltaTime;

        // if particle has died.
        if (_particleLifetimes[i] <= 0.0f || _lifespan == 0.0f) {
            // move head forward
            _particleHeadIndex = (_particleHeadIndex + 1) % _maxParticles;
        }
        else {
            float age = 1.0f - _particleLifetimes[i] / _lifespan;  // 0.0 .. 1.0
            updateRadius(i, age);
            updateColor(i, age);
            updateAlpha(i, age);
            integrateParticle(i, deltaTime);
            extendBounds(_particlePositions[i]);
        }
    }

    // emit new particles, but only if we are emmitting
    if (getIsEmitting() && _emitRate > 0.0f && _lifespan > 0.0f && _polarStart <= _polarFinish) {

        float timeLeftInFrame = deltaTime;
        while (_timeUntilNextEmit < timeLeftInFrame) {

            timeLeftInFrame -= _timeUntilNextEmit;
            _timeUntilNextEmit = 1.0f / _emitRate;

            // emit a new particle at tail index.
            quint32 i = _particleTailIndex;
            _particleLifetimes[i] = _lifespan;

            // Radius
            if (_radiusSpread == 0.0f) {
                _radiusStarts[i] = getRadiusStart();
                _radiusMiddles[i] =_particleRadius;
                _radiusFinishes[i] = getRadiusFinish();
            } else {
                float spreadMultiplier;
                if (_particleRadius > 0.0f) {
                    spreadMultiplier = 1.0f + randFloatInRange(-1.0f, 1.0f) * _radiusSpread / _particleRadius;
                } else {
                    spreadMultiplier = 1.0f;
                }
                _radiusStarts[i] = 
                    glm::clamp(spreadMultiplier * getRadiusStart(), MINIMUM_PARTICLE_RADIUS, MAXIMUM_PARTICLE_RADIUS);
                _radiusMiddles[i] = 
                    glm::clamp(spreadMultiplier * _particleRadius, MINIMUM_PARTICLE_RADIUS, MAXIMUM_PARTICLE_RADIUS);
                _radiusFinishes[i] = 
                    glm::clamp(spreadMultiplier * getRadiusFinish(), MINIMUM_PARTICLE_RADIUS, MAXIMUM_PARTICLE_RADIUS);
            }
            updateRadius(i, 0.0f);

            // Position, velocity, and acceleration
            if (_polarStart == 0.0f && _polarFinish == 0.0f && _emitDimensions.z == 0.0f) {
                // Emit along z-axis from position
                _particlePositions[i] = getPosition();
                _particleVelocities[i] = 
                    (_emitSpeed + randFloatInRange(-1.0f, 1.0f) * _speedSpread) * (_emitOrientation * Z_AXIS);
                _particleAccelerations[i] = _emitAcceleration + randFloatInRange(-1.0f, 1.0f) * _accelerationSpread;

            } else {
                // Emit around point or from ellipsoid
                // - Distribute directions evenly around point
                // - Distribute points relatively evenly over ellipsoid surface
                // - Distribute points relatively evenly within ellipsoid volume

                float elevationMinZ = sin(PI_OVER_TWO - _polarFinish);
                float elevationMaxZ = sin(PI_OVER_TWO - _polarStart);
                float elevation = asin(elevationMinZ + (elevationMaxZ - elevationMinZ) * randFloat());

                float azimuth;
                if (_azimuthFinish >= _azimuthStart) {
                    azimuth = _azimuthStart + (_azimuthFinish - _azimuthStart) * randFloat();
                } else {
                    azimuth = _azimuthStart + (TWO_PI + _azimuthFinish - _azimuthStart) * randFloat();
                }

                glm::vec3 emitDirection;

                if (_emitDimensions == glm::vec3()) {
                    // Point
                    emitDirection = glm::quat(glm::vec3(PI_OVER_TWO - elevation, 0.0f, azimuth)) * Z_AXIS;

                    _particlePositions[i] = getPosition();
                } else {
                    // Ellipsoid
                    float radiusScale = 1.0f;
                    if (_emitRadiusStart < 1.0f) {
                        float emitRadiusStart = glm::max(_emitRadiusStart, EPSILON);  // Avoid math complications at center
                        float randRadius = 
                            emitRadiusStart + randFloatInRange(0.0f, MAXIMUM_EMIT_RADIUS_START - emitRadiusStart);
                        radiusScale = 1.0f - std::pow(1.0f - randRadius, 3.0f);
                    }

                    glm::vec3 radiuses = radiusScale * 0.5f * _emitDimensions;
                    float x = radiuses.x * glm::cos(elevation) * glm::cos(azimuth);
                    float y = radiuses.y * glm::cos(elevation) * glm::sin(azimuth);
                    float z = radiuses.z * glm::sin(elevation);
                    glm::vec3 emitPosition = glm::vec3(x, y, z);
                    emitDirection = glm::normalize(glm::vec3(
                        radiuses.x > 0.0f ? x / (radiuses.x * radiuses.x) : 0.0f,
                        radiuses.y > 0.0f ? y / (radiuses.y * radiuses.y) : 0.0f,
                        radiuses.z > 0.0f ? z / (radiuses.z * radiuses.z) : 0.0f
                        ));

                    _particlePositions[i] = getPosition() + _emitOrientation * emitPosition;
                }

                _particleVelocities[i] =
                    (_emitSpeed + randFloatInRange(-1.0f, 1.0f) * _speedSpread) * (_emitOrientation * emitDirection);
                _particleAccelerations[i] = _emitAcceleration + randFloatInRange(-1.0f, 1.0f) * _accelerationSpread;
            }
            integrateParticle(i, timeLeftInFrame);
            extendBounds(_particlePositions[i]);

            // Color
            if (_colorSpread == xColor{ 0, 0, 0 }) {
                _colorStarts[i] = getColorStart();
                _colorMiddles[i] = getXColor();
                _colorFinishes[i] = getColorFinish();
            } else {
                xColor startColor = getColorStart();
                xColor middleColor = getXColor();
                xColor finishColor = getColorFinish();

                float spread = randFloatInRange(-1.0f, 1.0f);
                float spreadMultiplierRed = 
                    middleColor.red > 0 ? 1.0f + spread * (float)_colorSpread.red / (float)middleColor.red : 1.0f;
                float spreadMultiplierGreen = 
                    middleColor.green > 0 ? 1.0f + spread * (float)_colorSpread.green / (float)middleColor.green : 1.0f;
                float spreadMultiplierBlue = 
                    middleColor.blue > 0 ? 1.0f + spread * (float)_colorSpread.blue / (float)middleColor.blue : 1.0f;

                _colorStarts[i].red = (int)glm::clamp(spreadMultiplierRed * (float)startColor.red, 0.0f, 255.0f);
                _colorStarts[i].green = (int)glm::clamp(spreadMultiplierGreen * (float)startColor.green, 0.0f, 255.0f);
                _colorStarts[i].blue = (int)glm::clamp(spreadMultiplierBlue * (float)startColor.blue, 0.0f, 255.0f);

                _colorMiddles[i].red = (int)glm::clamp(spreadMultiplierRed * (float)middleColor.red, 0.0f, 255.0f);
                _colorMiddles[i].green = (int)glm::clamp(spreadMultiplierGreen * (float)middleColor.green, 0.0f, 255.0f);
                _colorMiddles[i].blue = (int)glm::clamp(spreadMultiplierBlue * (float)middleColor.blue, 0.0f, 255.0f);

                _colorFinishes[i].red = (int)glm::clamp(spreadMultiplierRed * (float)finishColor.red, 0.0f, 255.0f);
                _colorFinishes[i].green = (int)glm::clamp(spreadMultiplierGreen * (float)finishColor.green, 0.0f, 255.0f);
                _colorFinishes[i].blue = (int)glm::clamp(spreadMultiplierBlue * (float)finishColor.blue, 0.0f, 255.0f);
            }
            updateColor(i, 0.0f);

            // Alpha
            if (_alphaSpread == 0.0f) {
                _alphaStarts[i] = getAlphaStart();
                _alphaMiddles[i] = _alpha;
                _alphaFinishes[i] = getAlphaFinish();
            } else {
                float spreadMultiplier = 1.0f + randFloatInRange(-1.0f, 1.0f) * _alphaSpread / _alpha;
                _alphaStarts[i] = spreadMultiplier * getAlphaStart();
                _alphaMiddles[i] = spreadMultiplier * _alpha;
                _alphaFinishes[i] = spreadMultiplier * getAlphaFinish();
            }
            updateAlpha(i, 0.0f);

            _particleTailIndex = (_particleTailIndex + 1) % _maxParticles;

            // overflow! move head forward by one.
            // because the case of head == tail indicates an empty array, not a full one.
            // This can drop an existing older particle, but this is by design, newer particles are a higher priority.
            if (_particleTailIndex == _particleHeadIndex) {
                _particleHeadIndex = (_particleHeadIndex + 1) % _maxParticles;
            }
        }

        _timeUntilNextEmit -= timeLeftInFrame;
    }
}