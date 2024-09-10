void particleCollision(ParticleGeometryCollisionEventDetails* const details)
{
    ParticleSystemRefPtr TheSystem= details->getSystem();
    UInt32 ParticleIndex(details->getParticleIndex());


    Real32 phi= osgACos((-TheSystem->getVelocity(ParticleIndex).dot(details->getHitNormal()))/(TheSystem->getVelocity(ParticleIndex).length()*details->getHitNormal().length()));

    if( phi < osgDegree2Rad(80.0) )
    {
        TheSystem->killParticle(ParticleIndex);
    }
    else
    {
        //Reflect the Particle
        Vec3f Reflect(TheSystem->getVelocity(ParticleIndex).reflect(details->getHitNormal()));
        TheSystem->setVelocity(Reflect, ParticleIndex);
        TheSystem->setPosition(details->getHitPoint() + (0.00001f*Reflect), ParticleIndex);
    }

}