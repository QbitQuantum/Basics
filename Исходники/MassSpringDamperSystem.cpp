void MassPointSystem::buildDoubleTetrahedron(const Vec3d &center, const Vec3d &vel, const Vec3d &angVel)
{
    massPointVector.push_back(MassPoint(center + Vec3d(0.0, 0.0, 4.082), vel + angVel.cross(Vec3d(0.0, 0.0, 4.082))));
    massPointVector.push_back(MassPoint(center + Vec3d(-1.443, -2.5, 0.0), vel + angVel.cross(Vec3d(-1.443, -2.5, 0.0))));
    massPointVector.push_back(MassPoint(center + Vec3d(-1.443, 2.5, 0.0), vel + angVel.cross(Vec3d(-1.443, 2.5, 0.0))));
    massPointVector.push_back(MassPoint(center + Vec3d(2.886, 0.0, 0.0), vel + angVel.cross(Vec3d(2.886, 0.0, 0.0))));
    massPointVector.push_back(MassPoint(center + Vec3d(0.0, 0.0, -4.082), vel + angVel.cross(Vec3d(0.0, 0.0, -4.082))));

    jointVector.push_back(new SpringDamperJoint(0, 1, &massPointVector));
    jointVector.push_back(new SpringDamperJoint(0, 2, &massPointVector));
    jointVector.push_back(new SpringDamperJoint(0, 3, &massPointVector));
    jointVector.push_back(new SpringDamperJoint(1, 2, &massPointVector));
    jointVector.push_back(new SpringDamperJoint(1, 3, &massPointVector));
    jointVector.push_back(new SpringDamperJoint(1, 4, &massPointVector));
    jointVector.push_back(new SpringDamperJoint(2, 3, &massPointVector));
    jointVector.push_back(new SpringDamperJoint(2, 4, &massPointVector));
    jointVector.push_back(new SpringDamperJoint(3, 4, &massPointVector));
    for (unsigned int i = 0; i < massPointVector.size(); ++i)
    {
        jointVector.push_back(new GroundContactJoint(i));
        jointVector.push_back(new GravityJoint(i));
    }
}