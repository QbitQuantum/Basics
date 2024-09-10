   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
            TutorialWindowEventProducer->closeWindow();
       }

	   float TranslateAmount(0.05f);
	   float RotateAmount(0.1f);

	   switch(e->getKey())
	   {
	   default:
		   break;
	   }
   }