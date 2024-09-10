void AdvancedLightBinManager::LightMaterialInfo::setLightParameters( const LightInfo *lightInfo, const SceneRenderState* renderState, const MatrixF &worldViewOnly )
{
   MaterialParameters *matParams = matInstance->getMaterialParameters();

   // Set color in the right format, set alpha to the luminance value for the color.
   ColorF col = lightInfo->getColor();

   // TODO: The specularity control of the light
   // is being scaled by the overall lumiance.
   //
   // Not sure if this may be the source of our
   // bad specularity results maybe?
   //

   const Point3F colorToLumiance( 0.3576f, 0.7152f, 0.1192f );
   F32 lumiance = mDot(*((const Point3F *)&lightInfo->getColor()), colorToLumiance );
   col.alpha *= lumiance;

   matParams->setSafe( lightColor, col );
   matParams->setSafe( lightBrightness, lightInfo->getBrightness() );

   switch( lightInfo->getType() )
   {
   case LightInfo::Vector:
      {
         VectorF lightDir = lightInfo->getDirection();
         worldViewOnly.mulV(lightDir);
         lightDir.normalize();
         matParams->setSafe( lightDirection, lightDir );

         // Set small number for alpha since it represents existing specular in
         // the vector light. This prevents a divide by zero.
         ColorF ambientColor = renderState->getAmbientLightColor();
         ambientColor.alpha = 0.00001f;
         matParams->setSafe( lightAmbient, ambientColor );

         // If no alt color is specified, set it to the average of
         // the ambient and main color to avoid artifacts.
         //
         // TODO: Trilight disabled until we properly implement it
         // in the light info!
         //
         //ColorF lightAlt = lightInfo->getAltColor();
         ColorF lightAlt( ColorF::BLACK ); // = lightInfo->getAltColor();
         if ( lightAlt.red == 0.0f && lightAlt.green == 0.0f && lightAlt.blue == 0.0f )
            lightAlt = (lightInfo->getColor() + renderState->getAmbientLightColor()) / 2.0f;

         ColorF trilightColor = lightAlt;
         matParams->setSafe(lightTrilight, trilightColor);
      }
      break;

   case LightInfo::Spot:
      {
         const F32 outerCone = lightInfo->getOuterConeAngle();
         const F32 innerCone = getMin( lightInfo->getInnerConeAngle(), outerCone );
         const F32 outerCos = mCos( mDegToRad( outerCone / 2.0f ) );
         const F32 innerCos = mCos( mDegToRad( innerCone / 2.0f ) );
         Point4F spotParams(  outerCos, 
                              innerCos - outerCos, 
                              mCos( mDegToRad( outerCone ) ), 
                              0.0f );

         matParams->setSafe( lightSpotParams, spotParams );

         VectorF lightDir = lightInfo->getDirection();
         worldViewOnly.mulV(lightDir);
         lightDir.normalize();
         matParams->setSafe( lightDirection, lightDir );
      }
      // Fall through

   case LightInfo::Point:
   {
      const F32 radius = lightInfo->getRange().x;
      matParams->setSafe( lightRange, radius );

      Point3F lightPos;
      worldViewOnly.mulP(lightInfo->getPosition(), &lightPos);
      matParams->setSafe( lightPosition, lightPos );

      // Get the attenuation falloff ratio and normalize it.
      Point3F attenRatio = lightInfo->getExtended<ShadowMapParams>()->attenuationRatio;
      F32 total = attenRatio.x + attenRatio.y + attenRatio.z;
      if ( total > 0.0f )
         attenRatio /= total;

      Point2F attenParams( ( 1.0f / radius ) * attenRatio.y,
                           ( 1.0f / ( radius * radius ) ) * attenRatio.z );

      matParams->setSafe( lightAttenuation, attenParams );
      break;
   }

   default:
      AssertFatal( false, "Bad light type!" );
      break;
   }
}