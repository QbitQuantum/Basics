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
               for(int i(0); i < UnboundGeometries.size(); ++i)
               {
                   if(UnboundGeometries[i]->getTravMask() == 0)
                   {
                       beginEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
                            UnboundGeometries[i]->setTravMask(1);
                        endEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
                   } 
                   else
                   {
                       beginEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
                            UnboundGeometries[i]->setTravMask(0);
                        endEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
                   }
               }
           }
           else
           {
               //Toggle skeleton
               for(int i(0); i < SkeletonNodes.size(); ++i)
               {
                   if(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->getDrawBindPose() == false)
                   {
                       beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
                         SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawBindPose(true);
                        endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
                   } 
                   else
                   {
                       beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
                         SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawBindPose(false);
                        endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
                   }
               }
           }
       }

       //Toggle current pose
       if(e->getKey() == KeyEvent::KEY_P)
       {
           if(e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
           {
               //Toggle mesh
               for(int i(0); i < MeshNodes.size(); ++i)
               {
                   if(MeshNodes[i]->getTravMask() == 0)
                   {
                       beginEditCP(MeshNodes[i], Node::TravMaskFieldMask);
                            MeshNodes[i]->setTravMask(1);
                        endEditCP(MeshNodes[i], Node::TravMaskFieldMask);
                   } 
                   else
                   {
                       beginEditCP(MeshNodes[i], Node::TravMaskFieldMask);
                            MeshNodes[i]->setTravMask(0);
                        endEditCP(MeshNodes[i], Node::TravMaskFieldMask);
                   }
               }
           }
           else
           {
               //Toggle skeleton
               for(int i(0); i < SkeletonNodes.size(); ++i)
               {
                   if(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->getDrawPose() == false)
                   {
                       beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
                         SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawPose(true);
                        endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
                   } 
                   else
                   {
                       beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
                         SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawPose(false);
                        endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
                   }
               }
           }
       }

       //Toggle override status on second animation
       if(e->getKey() == KeyEvent::KEY_O)
       {
           if(TheSkeletonBlendedAnimation->getOverrideStatus(1))
           {
               TheSkeletonBlendedAnimation->setOverrideStatus(1, false);
           }
           else
           {
               TheSkeletonBlendedAnimation->setOverrideStatus(1, true);
           }
       }
   }