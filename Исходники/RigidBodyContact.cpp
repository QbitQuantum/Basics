Vector3 RigidBodyContact::CalculateFrictionlessImpulse(Matrix3x3* inverseInertiaTensor)
{
    Vector3 impulseContact;
    float deltaVelocity = 0;
    for (int i = 0; i < 2; i ++)
    {
        if (Body[i] != NULL)
        {
            // Calculate a vector that shows the change in velocity in world space for a unit impulse
            // in the direction of the contact normal
            Vector3 deltaVelocityWorldspace = m_relativeContactPosition[i].Cross(ContactNormal);
            deltaVelocityWorldspace = inverseInertiaTensor[i] * deltaVelocityWorldspace;
            deltaVelocityWorldspace = deltaVelocityWorldspace.Cross(m_relativeContactPosition[i]);

            // Calculate the change in velocity in contact coordinates
            deltaVelocity += deltaVelocityWorldspace.Dot(ContactNormal);

            // Add the linear component of velocity change
            deltaVelocity += Body[i]->GetInverseMass();
        }
    }
    impulseContact.SetX(m_desiredDeltaVelocity / deltaVelocity);
    impulseContact.SetY(0.0f);
    impulseContact.SetZ(0.0f);
    return impulseContact;
}