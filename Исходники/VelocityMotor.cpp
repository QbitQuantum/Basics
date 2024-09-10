    void VelocityMotor::internal_update()
    {
        // check if we have a solid
        if (mData.solid == NULL || isEnabled() == false) return ;

        Vec3r targetVelocity = mData.velocity;
        Solid * solid = mData.solid;

        Vec3r currentAchievedVelocity = solid->getGlobalLinearVel();

        if (doesGravityAffectSolid())
        {
            Vec3r gravity = mSimulator->getGravity();
            if (gravity.length() > 0)
            {
                Vec3r gravity_velocity = project(gravity, currentAchievedVelocity);
                currentAchievedVelocity -= gravity_velocity;
            }
        }

        Vec3r deltaVelocity = targetVelocity - currentAchievedVelocity;

        Vec3r forceVector = deltaVelocity / mSimulator->getStepSize() * solid->getMass();
        if (!doesGravityAffectSolid())
            forceVector -= mSimulator->getGravity() * solid->getMass();

        if (forceVector.length() > getMaximumForce())
        {
            forceVector.normalize();
            forceVector *= getMaximumForce();
        }

        Force controllingForce;
        controllingForce.duration = 0;
        controllingForce.singleStep = true;
        controllingForce.type = GLOBAL_FORCE;
        controllingForce.vec = forceVector;

        solid->addForce(controllingForce);
    }