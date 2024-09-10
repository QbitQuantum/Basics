   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }

	   switch(e->getKey())
	   {
	   case KeyEvent::KEY_S:
		   statFlag = !statFlag;
		   mgr->setStatistics(statFlag);
		   break;
       case KeyEvent::KEY_EQUALS:
           {
               Vec3f Translation;
               Quaternion Rotation;
               Vec3f Scale;
               Quaternion ScaleOrient;
               Matrix ThePointLightMat = ThePointLightBeaconTransform->getMatrix();
               ThePointLightMat.getTransform(Translation,Rotation,Scale,ScaleOrient);
               Translation = Translation + Vec3f(0.0,10.0,0.0);
               ThePointLightMat.setTranslate(Translation);
               beginEditCP(ThePointLightBeaconTransform);
                   ThePointLightBeaconTransform->setMatrix(ThePointLightMat);
               endEditCP(ThePointLightBeaconTransform);
           }
           break;
       case KeyEvent::KEY_MINUS:
           {
               Vec3f Translation;
               Quaternion Rotation;
               Vec3f Scale;
               Quaternion ScaleOrient;
               Matrix ThePointLightMat = ThePointLightBeaconTransform->getMatrix();
               ThePointLightMat.getTransform(Translation,Rotation,Scale,ScaleOrient);
               Translation = Translation + Vec3f(0.0,-10.0,0.0);
               ThePointLightMat.setTranslate(Translation);
               beginEditCP(ThePointLightBeaconTransform);
                   ThePointLightBeaconTransform->setMatrix(ThePointLightMat);
               endEditCP(ThePointLightBeaconTransform);
           }
           break;
       case KeyEvent::KEY_T:
            beginEditCP(TheBlinnMat, BlinnMaterial::DiffuseTextureFieldMask);
            endEditCP(TheBlinnMat, BlinnMaterial::DiffuseTextureFieldMask);
           break;
	   }
   }