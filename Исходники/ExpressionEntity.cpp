__m128 Expression::EvaluatePosition(EntityContext &aContext)
{
	if (const Entity *entity = Database::entity.Get(aContext.mId))
	{
		const Transform2 transform = entity->GetInterpolatedTransform(sim_fraction);
		return _mm_setr_ps(transform.p.x, transform.p.y, transform.a, 1.0f);
	}
	else
	{
		return _mm_setzero_ps();
	}
}