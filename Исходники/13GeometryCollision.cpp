    virtual void particleCollision(const ParticleGeometryCollisionEventUnrecPtr ColE)
    {
        ParticleSystemRefPtr TheSystem= ColE->getSystem();
        UInt32 ParticleIndex(ColE->getParticleIndex());

        Vec3f Reflect(TheSystem->getVelocity(ParticleIndex).reflect(ColE->getHitNormal()));
        TheSystem->setVelocity(Reflect, ParticleIndex);
        TheSystem->setPosition(ColE->getHitPoint() + (0.00001f*Reflect), ParticleIndex);

    }