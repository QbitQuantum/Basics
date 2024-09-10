//------------------------------------------------------------------------------
//       Class:  Emitter
//      Method:  generateVelocity
// Description:
//------------------------------------------------------------------------------
Vec2 Emitter::generateVelocity(const Focus& theFocus,
                               const Vec2& theParticlePosition) const

{
   Vec2 anVelocity;

   switch (mDispersion)
   {
   case LINEAR:
      anVelocity = Vec2(std::cos(theFocus.getAngle()),
                        std::sin(theFocus.getAngle()));
      break;

   case RADIAL:
      anVelocity = theParticlePosition - theFocus.getPosition();
      anVelocity.normalize();
      break;

   case STATIC:
      anVelocity = Vec2();
      break;

   case RANDOM:
      anVelocity = Vec2(sRealRandom(), sRealRandom());
      anVelocity.normalize();
      break;

   case REFLECT:
      anVelocity = Vec2();
      break;

   default:
      anVelocity = Vec2();
      break;
   }

   anVelocity *= mGenParLV();

   return anVelocity;
}