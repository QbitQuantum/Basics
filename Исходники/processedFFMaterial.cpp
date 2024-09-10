void ProcessedFFMaterial::_setPrimaryLightInfo(const MatrixF &_objTrans, LightInfo* light, U32 pass)
{
   // Just in case
   GFX->setGlobalAmbientColor(ColorF(0.0f, 0.0f, 0.0f, 1.0f));
   if ( light->getType() == LightInfo::Ambient )
   {
      // Ambient light
      GFX->setGlobalAmbientColor( light->getAmbient() );
      return;
   }

   GFX->setLight(0, NULL);
   GFX->setLight(1, NULL);
   // This is a quick hack that lets us use FF lights
   GFXLightMaterial lightMat;
   lightMat.ambient = ColorF(1.0f, 1.0f, 1.0f, 1.0f);
   lightMat.diffuse = ColorF(1.0f, 1.0f, 1.0f, 1.0f);
   lightMat.emissive = ColorF(0.0f, 0.0f, 0.0f, 0.0f);
   lightMat.specular = ColorF(0.0f, 0.0f, 0.0f, 0.0f);
   lightMat.shininess = 128.0f;
   GFX->setLightMaterial(lightMat);   

   // set object transform
   MatrixF objTrans = _objTrans;
   objTrans.inverse();

   // fill in primary light
   //-------------------------
   GFXLightInfo xlatedLight;
   light->setGFXLight(&xlatedLight);
   Point3F lightPos = light->getPosition();
   Point3F lightDir = light->getDirection();
   objTrans.mulP(lightPos);
   objTrans.mulV(lightDir);

   xlatedLight.mPos = lightPos;
   xlatedLight.mDirection = lightDir;

   GFX->setLight(0, &xlatedLight);
}