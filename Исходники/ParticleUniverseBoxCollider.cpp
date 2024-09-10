	//-----------------------------------------------------------------------
	void BoxCollider::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		mPredictedPosition = particle->position + mVelocityScale * particle->direction;
		bool collision = false;

		/** Collision detection is a two-step. First, we determine whether the particle is now colliding.
			If it is, the particle is re-positioned. However, a timeElapsed value is used, which is not the same
			as the one that was used at the moment before the particle was colliding. Therefore, we rather 
			want to predict particle collision in front. This probably isn't the fastest solution.
			The same approach was used for the other colliders.
		*/
		switch(mIntersectionType)
		{
			case BaseCollider::IT_POINT:
			{
				// Validate for a point-box intersection
				if (mInnerCollision != mBox.intersects(particle->position))
				{
					// Collision detected (re-position the particle)
					particle->position -= mVelocityScale * particle->direction;
					collision = true;
				}
				else if (mInnerCollision != mBox.intersects(mPredictedPosition))
				{
					// Collision detected
					collision = true;
				}
			}
			break;

			case BaseCollider::IT_BOX:
			{
				// Validate for a box-box intersection
				if (particle->particleType != Particle::PT_VISUAL)
					break;

				VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
				AxisAlignedBox box;
				populateAlignedBox(box,
					visualParticle->position, 
					visualParticle->width, 
					visualParticle->height,
					visualParticle->depth);

				if (mInnerCollision != box.intersects(mBox))
				{
					// Collision detected (re-position the particle)
					particle->position -= mVelocityScale * particle->direction;
					collision = true;
				}
				else
				{
					AxisAlignedBox box;
					populateAlignedBox(box,
						mPredictedPosition, 
						visualParticle->width, 
						visualParticle->height,
						visualParticle->depth);
					if (mInnerCollision != box.intersects(mBox))
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
			particle->addEventFlags(Particle::PEF_COLLIDED);
		}
	}