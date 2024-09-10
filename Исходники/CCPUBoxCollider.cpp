void PUBoxCollider::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        _predictedPosition = particle->position + _velocityScale * particle->direction;
        bool collision = false;

        /** Collision detection is a two-step. First, we determine whether the particle is now colliding.
            If it is, the particle is re-positioned. However, a timeElapsed value is used, which is not the same
            as the one that was used at the moment before the particle was colliding. Therefore, we rather 
            want to predict particle collision in front. This probably isn't the fastest solution.
            The same approach was used for the other colliders.
        */
        switch(_intersectionType)
        {
            case PUBaseCollider::IT_POINT:
            {
                // Validate for a point-box intersection
                if (_innerCollision != _box.containPoint(particle->position))
                {
                    // Collision detected (re-position the particle)
                    particle->position -= _velocityScale * particle->direction;
                    collision = true;
                }
                else if (_innerCollision != _box.containPoint(_predictedPosition))
                {
                    // Collision detected
                    collision = true;
                }
            }
            break;

            case PUBaseCollider::IT_BOX:
            {
                AABB box;
                populateAlignedBox(box,
                    particle->position, 
                    particle->width, 
                    particle->height,
                    particle->depth);

                if (_innerCollision != box.intersects(_box))
                {
                    // Collision detected (re-position the particle)
                    particle->position -= _velocityScale * particle->direction;
                    collision = true;
                }
                else
                {
                    populateAlignedBox(box,
                        _predictedPosition, 
                        particle->width, 
                        particle->height,
                        particle->depth);
                    if (_innerCollision != box.intersects(_box))
                    {
                        // Collision detected
                        collision = true;
                    }
                }
            }
            break;
        }

        if (collision)
        {
            calculateDirectionAfterCollision(particle);
            calculateRotationSpeedAfterCollision(particle);
            particle->addEventFlags(PUParticle3D::PEF_COLLIDED);
        }
    }

}