    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey()== KeyEvent::KEY_1) // Use the Point Drawer
        {
            ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
        }

        if(e->getKey()== KeyEvent::KEY_2)//Use the Line Drawer for 2
        {
            ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
        }
        if(e->getKey()== KeyEvent::KEY_R)
        {   // reverse the magnitude of the field
            ExampleUniformAffector->setMagnitude(-(ExampleUniformAffector->getMagnitude()));


        }

        // change direction of the field
        if(e->getKey()== KeyEvent::KEY_A)
        {
            ExampleUniformAffector->setDirection(Vec3f(-1.0,0.0,0.0));

        }
        if(e->getKey()== KeyEvent::KEY_W)
        {
            ExampleUniformAffector->setDirection(Vec3f(0.0,1.0,0.0));

        }
        if(e->getKey()== KeyEvent::KEY_S)
        {
            ExampleUniformAffector->setDirection(Vec3f(0.0,-1.0,0.0));

        }
        if(e->getKey()== KeyEvent::KEY_D)
        {
            ExampleUniformAffector->setDirection(Vec3f(1.0,0.0,0.0));

        }
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            TutorialWindow->closeWindow();
        }
    }