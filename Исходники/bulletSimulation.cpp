bool bulletSimulation::SetFrame(int in_Frame)
{
   // see if we have to reset the world
   if(in_Frame <= 0)
   {
      ResetWorld();
      return true;
   }

   // now let's skip if we already have that frame or the interval>5 - we don't want bullet to compute the whole sequence if you move to the last frame.
   if(mLastFrame >= in_Frame || (in_Frame-mLastFrame)>5)
   {
      return false;
   }

   mChangingFrame = true;

   // if this is not the first frame, let's update all rbd!
   for(btRigidBodyIt it = mRigidBodies.begin();it!=mRigidBodies.end();it++)
   {
      // skip corrupt bodies
      if(it->second->body==NULL)
         continue;
      if(it->first.secondary != -1)
         continue;

      btCollisionShape * shape = (btBoxShape*)it->second->body->getCollisionShape();
      if(shape != NULL)
      {
         // refresh the kine ptr
         it->second->kine.Set(it->second->kine.GetAsText());

         XSI::MATH::CTransformation xf = XSI::KinematicState(it->second->kine).GetTransform();//(float)in_Frame);
         shape->setLocalScaling(btVector3(xf.GetSclX(),xf.GetSclY(),xf.GetSclZ()));

         // skip non valid ops
         if(!it->second->op.IsValid())
            continue;

         // update the mass an inertia
         it->second->mass = XSI::CustomOperator(it->second->op).GetParameterValue(L"mass");
         btVector3 inertia(0,0,0);
         if(it->second->mass > 0.0f)
            shape->calculateLocalInertia(it->second->mass,inertia);
         it->second->body->setMassProps(it->second->mass,inertia);

         // if we are passive rigid body, let's update the transform
         if(it->second->mass == 0.0f)
         {
            btDefaultMotionState * motionState = (btDefaultMotionState*)it->second->body->getMotionState();
            if(motionState != NULL)
            {
               btTransform transform;
               transform.setOrigin(btVector3(xf.GetPosX(),xf.GetPosY(),xf.GetPosZ()));

               XSI::MATH::CQuaternion q = xf.GetRotationQuaternion();
               transform.setRotation(btQuaternion(q.GetX(),q.GetY(),q.GetZ(),q.GetW()));
               it->second->body->proceedToTransform( transform );
            }
         }
      }
   }

   // step to the given frame
   if(in_Frame > 0)
   {
      while(in_Frame > mLastFrame)
      {
         float dt=(1.0f/mFps)/(float)mSubSteps;
         //Step every subframe
         for (int i=0;i<mSubSteps;i++)
             mDynamicsWorld->stepSimulation(dt,0,1.0f/mFps);

         mLastFrame++;
      }
   }
   mLastFrame = in_Frame;

   mChangingFrame = false;
   return true;
}