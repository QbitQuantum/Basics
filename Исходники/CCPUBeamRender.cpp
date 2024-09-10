void PUBeamRender::updateRender( PUParticle3D *particle, float deltaTime, bool firstParticle )
{
    if (!particle->visualData)
        return;

    PUParticle3DBeamVisualData* beamRendererVisualData = static_cast<PUParticle3DBeamVisualData*>(particle->visualData);
    beamRendererVisualData->timeSinceLastUpdate -= deltaTime;

    if (beamRendererVisualData->timeSinceLastUpdate < 0)
    {

        Vec3 end = particle->position - static_cast<PUParticleSystem3D *>(_particleSystem)->getDerivedPosition();
        Vec3 perpendicular;
        float divide = (float)_numberOfSegments + 1.0f;
        for (size_t numDev = 0; numDev < _numberOfSegments; ++numDev)
        {
            Vec3::cross(end, Vec3(CCRANDOM_MINUS1_1(), CCRANDOM_MINUS1_1(), CCRANDOM_MINUS1_1()), &perpendicular);
            perpendicular.normalize();
            beamRendererVisualData->destinationHalf[numDev] = (((float)numDev + 1.0f) / divide) * end
                + Vec3(_rendererScale.x * _deviation * perpendicular.x
                     , _rendererScale.y * _deviation * perpendicular.y
                     , _rendererScale.z * _deviation * perpendicular.z);
        }
        beamRendererVisualData->timeSinceLastUpdate += _updateInterval;
    }

    Vec3 diff;
    for (size_t numDev = 0; numDev < _numberOfSegments; ++numDev)
    {
        if (_jump)
        {
            beamRendererVisualData->half[numDev] = beamRendererVisualData->destinationHalf[numDev];
        }
        else
        {
            diff = beamRendererVisualData->destinationHalf[numDev] - beamRendererVisualData->half[numDev];
            beamRendererVisualData->half[numDev] = beamRendererVisualData->half[numDev] + deltaTime * diff;
        }
    }
}