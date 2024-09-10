//----------------------------------------------------------------------------
void BouncingTetrahedra::ComputePreimpulseVelocity (float* preRelVelocities)
{
    for (int i = 0; i < mNumContacts; ++i)
    {
        const Contact& contact = mContacts[i];
        const RigidBodyf& bodyA = *contact.A;
        const RigidBodyf& bodyB = *contact.B;

        Vector3f XA = bodyA.GetPosition();
        Vector3f XB = bodyB.GetPosition();
        Vector3f VA = bodyA.GetLinearVelocity();
        Vector3f VB = bodyB.GetLinearVelocity();
        Vector3f WA = bodyA.GetAngularVelocity();
        Vector3f WB = bodyB.GetAngularVelocity();

        Vector3f relA = contact.PA - XA;
        Vector3f relB = contact.PB - XB;
        Vector3f velA = VA + WA.Cross(relA);
        Vector3f velB = VB + WB.Cross(relB);
        preRelVelocities[i] = contact.N.Dot(velB - velA);
    }
}