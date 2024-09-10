 virtual void keyPressed(const KeyEventUnrecPtr e)
 {
     if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
     {
         TutorialWindow->closeWindow();
     }
     if(e->getKey() == KeyEvent::KEY_S)
     {
         mgr->setStatistics(true);
     }
     if(e->getKey() == KeyEvent::KEY_A)
     {
         mgr->setStatistics(false);
     }
 }