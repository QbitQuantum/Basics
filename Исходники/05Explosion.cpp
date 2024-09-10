 virtual void keyPressed(const KeyEventUnrecPtr e)
 {
     if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
     {
         TutorialWindow->closeWindow();
     }
     switch(e->getKey())
     {
     case KeyEvent::KEY_S:
          {
              allPhysicsBodies.push_back(buildSphere());
          }
          break;
     case KeyEvent::KEY_B:
          {
              allPhysicsBodies.push_back(buildBox());
          }
          break;
     case KeyEvent::KEY_E:
         makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 1280.0f);
         break;
     case KeyEvent::KEY_1:
         makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 20.0f);
         break;
     case KeyEvent::KEY_2:
         makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 80.0f);
         break;
     case KeyEvent::KEY_3:
         makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 320.0f);
         break;
     case KeyEvent::KEY_4:
         makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 1280.0f);
         break;
     case KeyEvent::KEY_5:
         makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 5120.0f);
         break;
     case KeyEvent::KEY_6:
         makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 20480.0f);
         break;
     }
 }