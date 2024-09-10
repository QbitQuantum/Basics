 virtual void keyPressed(const KeyEventPtr e)
 {
     if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
     {
          TutorialWindowEventProducer->closeWindow();
     }
     switch(e->getKey())
     {
     case KeyEvent::KEY_S:
          {
              buildSphere();
          }
          break;
     case KeyEvent::KEY_B:
          {
              buildBox();
          }
          break;
     case KeyEvent::KEY_Z:
          {
              //SceneFileHandler::the().write(rootNode, "scene.osb");
          }
          break;
     case KeyEvent::KEY_T:
          {
              buildTriMesh();
          }
          break;
     }
 }