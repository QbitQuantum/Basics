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
        if(e->getKey()== KeyEvent::KEY_3)// increase velocity conservation
        {
            ExampleConserveVelocityAffector->setConserve(osgMax(0.0f,ExampleConserveVelocityAffector->getConserve() - 0.03f));
        }
        if(e->getKey()== KeyEvent::KEY_4) // decrease velocity conservation
        {
            ExampleConserveVelocityAffector->setConserve(osgMin(1.0f,ExampleConserveVelocityAffector->getConserve() + 0.03f));

        }
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            TutorialWindow->closeWindow();
        }
    }