void Manifold::ApplyImpulse( void )
{
  // Early out and positional correct if both objects have infinite mass
  if(Equal( A->im + B->im, 0 ))
  {
    InfiniteMassCorrection( );
    return;
  }

  for(uint32 i = 0; i < contact_count; ++i)
  {
    // Calculate radii from COM to contact
    Vec2 ra = contacts[i] - A->position;
    Vec2 rb = contacts[i] - B->position;

    // Relative velocity
    Vec2 rv = B->velocity + Cross( B->angularVelocity, rb ) -
              A->velocity - Cross( A->angularVelocity, ra );

    // Relative velocity along the normal
    real contactVel = Dot( rv, normal );

    // Do not resolve if velocities are separating
    if(contactVel > 0)
      return;

    real raCrossN = Cross( ra, normal );
    real rbCrossN = Cross( rb, normal );
    real invMassSum = A->im + B->im + Sqr( raCrossN ) * A->iI + Sqr( rbCrossN ) * B->iI;

    // Calculate impulse scalar
    real j = -(1.0f + e) * contactVel;
    j /= invMassSum;
    j /= (real)contact_count;

    // Apply impulse
    Vec2 impulse = normal * j;
    A->ApplyImpulse( -impulse, ra );
    B->ApplyImpulse(  impulse, rb );

    // Friction impulse
    rv = B->velocity + Cross( B->angularVelocity, rb ) -
         A->velocity - Cross( A->angularVelocity, ra );

    Vec2 t = rv - (normal * Dot( rv, normal ));
    t.Normalize( );

    // j tangent magnitude
    real jt = -Dot( rv, t );
    jt /= invMassSum;
    jt /= (real)contact_count;

    // Don't apply tiny friction impulses
    if(Equal( jt, 0.0f ))
      return;

    // Coulumb's law
    Vec2 tangentImpulse;
    if(std::abs( jt ) < j * sf)
      tangentImpulse = t * jt;
    else
      tangentImpulse = t * -j * df;

    // Apply friction impulse
    A->ApplyImpulse( -tangentImpulse, ra );
    B->ApplyImpulse(  tangentImpulse, rb );
  }
}