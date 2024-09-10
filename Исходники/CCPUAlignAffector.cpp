void PUAlignAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //auto particles = _particleSystem->getParticles();
    //if (!particles.empty())
    {
        //PUParticle3D *preParticle = particles[0];
        //for (unsigned int i = 1; i < particles.size(); ++i)
        {
            //PUParticle3D *particle = particles[i];
            Vec3 diff = _previousParticle->position - particle->position;
            if (_resize)
            {
                particle->setOwnDimensions(particle->width, diff.length(), particle->depth);
            }
            diff.normalize();
            particle->orientation.x = diff.x;
            particle->orientation.y = diff.y;
            particle->orientation.z = diff.z;
            _previousParticle = particle;
        }
    }
}