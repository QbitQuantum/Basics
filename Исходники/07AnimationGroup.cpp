   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
           TutorialWindow->closeWindow();
       }

       switch(e->getKey())
       {
       case KeyEvent::KEY_SPACE:
           TheAnimationGroup->pause(!TheAnimationGroup->isPaused());
           break;
       case KeyEvent::KEY_ENTER:
           TheAnimationGroup->attachUpdateProducer(TutorialWindow->editEventProducer());
           TheAnimationGroup->start();
           break;
       case KeyEvent::KEY_MINUS:
           TheAnimationGroup->setScale(osgMax(TheAnimationGroup->getScale()-0.1f, 0.0f));
           break;
       case KeyEvent::KEY_PLUS:
       case KeyEvent::KEY_EQUALS:
           TheAnimationGroup->setScale(osgMax(TheAnimationGroup->getScale()+0.1f, 0.0f));
           break;
       }
   }