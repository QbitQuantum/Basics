   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
            TutorialWindowEventProducer->closeWindow();
       }

	   switch(e->getKey())
	   {
       case KeyEvent::KEY_T:
           break;
	   }
   }