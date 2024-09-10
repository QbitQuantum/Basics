 virtual void keyPressed(const KeyEventUnrecPtr e)
 {
     if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
     {
         TutorialWindow->closeWindow();
     }
     if(e->getKey() == KeyEvent::KEY_R)
     {
         ExampleRadialAffector->setMagnitude(-(ExampleRadialAffector->getMagnitude()));
     }
 }