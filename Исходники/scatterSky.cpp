void ScatterSky::_conformLights()
{
   _initCurves();

   F32 val = mCurves[0].getVal( mTimeOfDay );
   mNightInterpolant = 1.0f - val;

   VectorF lightDirection;
   F32 brightness;

   // Build the light direction from the azimuth and elevation.
   F32 yaw = mDegToRad(mClampF(mSunAzimuth,0,359));
   F32 pitch = mDegToRad(mClampF(mSunElevation,-360,+360));
   MathUtils::getVectorFromAngles(lightDirection, yaw, pitch);
   lightDirection.normalize();
   mSunDir = -lightDirection;

   yaw = mDegToRad(mClampF(mMoonAzimuth,0,359));
   pitch = mDegToRad(mClampF(mMoonElevation,-360,+360));
   MathUtils::getVectorFromAngles( mMoonLightDir, yaw, pitch );
   mMoonLightDir.normalize();
   mMoonLightDir = -mMoonLightDir;

   brightness = mCurves[2].getVal( mTimeOfDay );

   if ( mNightInterpolant >= 1.0f )
      lightDirection = -mMoonLightDir;

   mLight->setDirection( -lightDirection );
   mLight->setBrightness( brightness * mBrightness );
   mLightDir = lightDirection;

   // Have to do interpolation
   // after the light direction is set
   // otherwise the sun color will be invalid.
   _interpolateColors();

   mLight->setAmbient( mAmbientColor );
   mLight->setColor( mSunColor );
   mLight->setCastShadows( mCastShadows );

   FogData fog = getSceneManager()->getFogData();
   fog.color = mFogColor;
   getSceneManager()->setFogData( fog );
}