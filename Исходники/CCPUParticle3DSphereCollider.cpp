//-----------------------------------------------------------------------
void PUParticle3DSphereCollider::calculateDirectionAfterCollision(PUParticle3D* particle, Vec3 distance, float distanceLength)
{
    switch (_collisionType)
    {
        case PUParticle3DBaseCollider::CT_BOUNCE:
        {
            /** If the particle is on the surface (or just inside the sphere); bounce it
                Make use of formula R = 2 * (-I dot N) * N + I, where
                R = the new direction vector
                I = the old (unit) direction vector before the collision
                N = the Normal at the collision point
            */
            float directionLength = particle->direction.length();
            particle->direction.normalize();
            distance.normalize();
            particle->direction = 2 * (-particle->direction.dot(distance)) * distance + particle->direction;

            // Adjust to original speed
            particle->direction *= directionLength;

            // Accelerate/slow down, using the bounce value
            particle->direction *= _bouncyness;
        }
        break;
        case PUParticle3DBaseCollider::CT_FLOW:
        {
            /** Reset the position (on the sphere), but keep the direction.
                This doesn't really work good for box-type collisions, because it doesn't take the particle
                dimensions into account.
            */
            float scaledRadius = 0.3333f * (_affectorScale.x + _affectorScale.y + _affectorScale.z) * _radius;
            particle->position = _derivedPosition + distance * (scaledRadius / distanceLength);
        }
        break;
        default:
        break;
    }
}