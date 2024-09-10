    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            TutorialWindow->closeWindow();
        }

        if(e->getKey() == KeyEvent::KEY_B)//generate particles when clicked
        {
            //Attach the Generator to the Particle System
            ExampleParticleSystem->pushToGenerators(ExampleBurstGenerator);
        }
    }