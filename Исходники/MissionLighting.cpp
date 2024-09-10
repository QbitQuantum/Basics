void MissionLighting::addLight( ITRBasicLighting::LightList & lightList,
   SimContainer & interior, TSLight & light, ColorF & ambient )
{
   ITRBasicLighting::Light * basicLight = new ITRBasicLighting::Light;

   // fill in the light info
   basicLight->id = 0xffff0000 + lightList.size() + 1;
   basicLight->name = NULL;
   basicLight->flags = 0;
   
   ITRBasicLighting::Light::State * state = new ITRBasicLighting::Light::State;
   
   // fill in the default state info
   state->stateDuration = 0.f;
   state->color.red = light.fLight.fRed;
   state->color.green = light.fLight.fGreen;
   state->color.blue = light.fLight.fBlue;

   ITRBasicLighting::Light::State::Emitter emitter;

   // set the ambient intensity
   ITRBasicLighting::m_ambientIntensity += ambient;
   
   // determine the light type
   switch( light.fLight.fType )
   {
      case TS::Light::LightPoint:
      {
         emitter.lightType = ITRBasicLighting::Light::State::PointLight;
         
         TMat3F mat = getInteriorTransform( interior );
         mat.inverse();

         m_mul( light.fLight.fWPosition, mat, &emitter.pos );
         
         // setup the falloff params ( no linear falloff )
         emitter.falloff = ITRBasicLighting::Light::State::Linear;
         emitter.d1 = emitter.d2 = emitter.radius = light.fLight.fRange;
         
         break;
      }
         
      // check for treating wrap lights like directional
      case TS::Light::LightDirectionalWrap:
      {
         if( !missionConvertWrapLights )
         {
            delete basicLight;
            delete state;
            return;
         }
      }
            
      case TS::Light::LightDirectional:
      {
         emitter.lightType = ITRBasicLighting::Light::State::DirectionalLight;

         RMat3F mat = getInteriorTransform( interior );
         mat.inverse();
                  
         m_mul( light.fLight.fWAim, mat, &emitter.spotVector );
         
         break;
      }
         
      default:
         
         // unsupported light type
         delete basicLight;
         delete state;
         return;
   }

   // add to the lists
   lightList.push_back( basicLight );
   basicLight->state.push_back( state );
   state->m_emitterList.push_back( emitter );
}