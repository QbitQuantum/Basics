void DynamicEntityNode::DynamicMove(sf::Vector2f Disp, bool SweepBothDirections)
{
	unsigned int CollisionMask = eCollisionGroup::Monster | eCollisionGroup::Static | eCollisionGroup::Player | eCollisionGroup::Pickup;
	float SweepTmax = 1.5f;

	if (SweepBothDirections)
	{
		if (Disp.x != 0.0f)
		{
			HitInfo Hit;
			GetWorld()->GetQuadTree()->SweepShapeClosest(*GetCollisionShape(), GetWorldTransform(), sf::Vector2f(Disp.x, 0.0f), SweepTmax, CollisionMask, this, Hit);

			if (Hit.m_pObject)
			{
				Disp.x = 0.0f;
				OnTouch(Hit.m_pObject);
			}
		}

		if (Disp.y != 0.0f)
		{
			HitInfo Hit;
			GetWorld()->GetQuadTree()->SweepShapeClosest(*GetCollisionShape(), GetWorldTransform(), sf::Vector2f(0.0f, Disp.y), SweepTmax, CollisionMask, this, Hit);

			if (Hit.m_pObject)
			{
				Disp.y = 0.0f;
				OnTouch(Hit.m_pObject);
			}
		}
	}
	else
	{
		HitInfo Hit;
		GetWorld()->GetQuadTree()->SweepShapeClosest(*GetCollisionShape(), GetWorldTransform(), Disp, SweepTmax, CollisionMask, this, Hit);

		if (Hit.m_pObject)
		{
			Disp.x = 0.0f;
			Disp.y = 0.0f;
			OnTouch(Hit.m_pObject);
		}
	}

	Move(Disp);
}