   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
           TutorialWindow->closeWindow();
       }

       switch(e->getKey())
       {
       case KeyEvent::KEY_SPACE:
           TheAnimation->pause(!TheAnimation->isPaused());
           break;
       case KeyEvent::KEY_ENTER:
           TheAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
           TheAnimation->start();
           break;
       case KeyEvent::KEY_1:
                dynamic_pointer_cast<FieldAnimation>(TheAnimation)->setInterpolationType(Animator::STEP_INTERPOLATION);
           break;
       case KeyEvent::KEY_2:
                dynamic_pointer_cast<FieldAnimation>(TheAnimation)->setInterpolationType(Animator::LINEAR_INTERPOLATION);
           break;
       case KeyEvent::KEY_3:
                dynamic_pointer_cast<FieldAnimation>(TheAnimation)->setInterpolationType(Animator::CUBIC_INTERPOLATION);
           break;
       }
   }