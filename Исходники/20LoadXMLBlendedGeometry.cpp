   virtual void keyPressed(const KeyEventPtr e)
   {
	   //Exit
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
           TutorialWindowEventProducer->closeWindow();
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

				   beginEditCP(UnboundGeometry, Node::TravMaskFieldMask);
						UnboundGeometry->setTravMask(1);
					endEditCP(UnboundGeometry, Node::TravMaskFieldMask);
			   } 
			   else
			   {
				   beginEditCP(UnboundGeometry, Node::TravMaskFieldMask);
						UnboundGeometry->setTravMask(0);
					endEditCP(UnboundGeometry, Node::TravMaskFieldMask);
			   }
		   }
		   else
		   {
				//Toggle skeleton
			   if(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->getDrawBindPose() == false)
			   {
				   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
					 SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->setDrawBindPose(true);
					endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
			   } 
			   else
			   {
				   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
					 SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->setDrawBindPose(false);
					endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
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
				   beginEditCP(MeshNode, Node::TravMaskFieldMask);
						MeshNode->setTravMask(1);
					endEditCP(MeshNode, Node::TravMaskFieldMask);
			   } 
			   else
			   {
				   beginEditCP(MeshNode, Node::TravMaskFieldMask);
						MeshNode->setTravMask(0);
					endEditCP(MeshNode, Node::TravMaskFieldMask);
			   }
		   }
		   else
		   {
			   //Toggle skeleton
			   if(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->getDrawPose() == false)
			   {
				   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawPoseFieldMask);
					 SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->setDrawPose(true);
					endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawPoseFieldMask);
			   } 
			   else
			   {
				   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawPoseFieldMask);
					 SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->setDrawPose(false);
					endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawPoseFieldMask);
			   }
		   }
	   }
   }