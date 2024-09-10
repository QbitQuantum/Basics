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

	   //Toggle current pose
	   if(e->getKey() == KeyEvent::KEY_P)
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

	   //Switch animation
	   if(e->getKey() == KeyEvent::KEY_1)
	   {
			TheCurrentAnimation = TheJointAnimation;
	   }
	   else if(e->getKey() == KeyEvent::KEY_2)
	   {
			TheCurrentAnimation = TheChildJointAnimation;
	   }
   }