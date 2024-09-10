    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TheWindowEventProducer->closeWindow();
       }

       switch(e->getKey())
       {
       case KeyEvent::KEY_1:
       case KeyEvent::KEY_2:
       case KeyEvent::KEY_3:
       case KeyEvent::KEY_4:
       case KeyEvent::KEY_5:
       case KeyEvent::KEY_6:
       case KeyEvent::KEY_7:
       case KeyEvent::KEY_8:
       case KeyEvent::KEY_9:
           {
               UInt8 Index(e->getKeyChar() - '1');
               if(Index < Sounds.size())
               {
                   Sounds[Index]->play();
               }
           }
           break;
       case KeyEvent::KEY_P:
           SoundGroups[0]->pause();
           break;
       case KeyEvent::KEY_U:
           SoundGroups[0]->unpause();
           break;
       case KeyEvent::KEY_MINUS:
           {
                Real32 Volume(SoundGroups[0]->getVolume());
                Volume -= 0.1;
                if(Volume < 0.0) Volume = 0.0;
                SoundGroups[0]->setVolume(Volume);
           }
           break;
       case KeyEvent::KEY_EQUALS:
           {
                Real32 Volume(SoundGroups[0]->getVolume());
                Volume += 0.1;
                if(Volume > 1.0) Volume = 1.0;
                SoundGroups[0]->setVolume(Volume);
           }
           break;
       }
    }