 virtual void keyPressed(const KeyEventPtr e)
 {
     if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
     {
          TutorialWindowEventProducer->closeWindow();
     }
 }