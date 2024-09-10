 virtual void keyPressed(const KeyEventUnrecPtr e)
 {
     if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
     {
         TutorialWindow->closeWindow();
     }
 }