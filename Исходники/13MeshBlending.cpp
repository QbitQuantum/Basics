    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        //Exit
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            TutorialWindow->closeWindow();
        }

        //Toggle animation
        if(e->getKey() == KeyEvent::KEY_SPACE)
        {
            if(animationPaused)
                animationPaused = false;
            else
                animationPaused = true;
        }

        //Toggle bind pose
        if(e->getKey() == KeyEvent::KEY_B)
        {
            if(e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
            {
                //Toggle mesh
                if(UnboundGeometry->getTravMask() == 0)
                {
                    UnboundGeometry->setTravMask(1);
                } 
                else
                {
                    UnboundGeometry->setTravMask(0);
                }
            }
            else
            {
                //Toggle skeleton
                if(dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->getDrawBindPose() == false)
                {
                    dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawBindPose(true);
                } 
                else
                {
                    dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawBindPose(false);
                }
            }
        }

        //Toggle current pose
        if(e->getKey() == KeyEvent::KEY_P)
        {
            if(e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
            {
                //Toggle mesh
                if(MeshNode->getTravMask() == 0)
                {
                    MeshNode->setTravMask(1);
                } 
                else
                {
                    MeshNode->setTravMask(0);
                }
            }
            else
            {
                //Toggle skeleton
                if(dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->getDrawPose() == false)
                {
                    dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawPose(true);
                } 
                else
                {
                    dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawPose(false);
                }
            }
        }
    }