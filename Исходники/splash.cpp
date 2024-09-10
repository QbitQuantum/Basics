//----------------------------------------------------------------------------
// Create ring
//----------------------------------------------------------------------------
SplashRing Splash::createRing()
{
   SplashRing ring;
   U32 numPoints = mDataBlock->numSegments + 1;

   Point3F ejectionAxis( 0.0, 0.0, 1.0 );

   Point3F axisx;
   if (mFabs(ejectionAxis.z) < 0.999f)
      mCross(ejectionAxis, Point3F(0, 0, 1), &axisx);
   else
      mCross(ejectionAxis, Point3F(0, 1, 0), &axisx);
   axisx.normalize();

   for( U32 i=0; i<numPoints; i++ )
   {
      F32 t = F32(i) / F32(numPoints);

      AngAxisF thetaRot( axisx, mDataBlock->ejectionAngle * (M_PI / 180.0));
      AngAxisF phiRot(   ejectionAxis, t * (M_PI * 2.0));

      Point3F pointAxis = ejectionAxis;

      MatrixF temp;
      thetaRot.setMatrix(&temp);
      temp.mulP(pointAxis);
      phiRot.setMatrix(&temp);
      temp.mulP(pointAxis);

      Point3F startOffset = axisx;
      temp.mulV( startOffset );
      startOffset *= mDataBlock->startRadius;

      SplashRingPoint point;
      point.position = getPosition() + startOffset;
      point.velocity = pointAxis * mDataBlock->velocity;

      ring.points.push_back( point );
   }

   ring.color = mDataBlock->colors[0];
   ring.lifetime = mDataBlock->ringLifetime;
   ring.elapsedTime = 0.0;
   ring.v = mDataBlock->texFactor * mFmod( mElapsedTime, 1.0 );

   return ring;
}