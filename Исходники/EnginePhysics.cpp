void ApplyOrbitVelocity(PxRigidActor* box, float power)
{
    for(int i = 0; i < planets.size(); i++)
    {
        PxVec3 dir = planets[i]->actor->getGlobalPose().p - box->getGlobalPose().p;

        dir.normalize();

        PxVec3 velocity = RandomOrthogonalVector(dir) * power;

        box->isRigidDynamic()->addForce(velocity,PxForceMode::eACCELERATION);
    }
}