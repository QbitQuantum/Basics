//------------------------------------------------------------------------------
//!
void
PosSpring::prePositionStep( double step )
{
   // Compute word anchors.
   Vec3f worldAnchorA = _bodyA->transform() * _anchorA;
   Vec3f worldAnchorB = _bodyB->transform() * _anchorB;

   Vec3f x    = worldAnchorB-worldAnchorA;
   float dist = x.length();

   if( dist > CGConstf::epsilon() )
   {
      x *= (1.0f/dist);
   }
   else
   {
      x = Vec3f( 0.0f, -1.0f, 0.0f );
   }
   x *= (dist-_restLength);

   // Apply friction using the velocity from B to A.
   Vec3f deltaV = _bodyB->velocity( worldAnchorB ) - _bodyA->velocity( worldAnchorA );

   // Compute impulse to apply.
   // F = -kx - dv = k*(-x) + d*(-v)
   // p = F * t
   Vec3f p = x * (_stiffness * (float)step) + deltaV * (_damping * (float)step);

   _bodyA->applyImpulse(  p, worldAnchorA );
   _bodyB->applyImpulse( -p, worldAnchorB );
}