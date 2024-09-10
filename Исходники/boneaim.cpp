		void BoneAim::update(float time){
			if (mBone == NULL){
				mBone = mGo->getEntity()->getSkeleton()->getBone(mBoneName);
				mTarget = Level::getSingleton()->getCurrentSegment()->getObjectByName(mTargetName);
				if (mTarget == NULL){
					throw("No such object : "+mTargetName);
				}
			}
			//Ogre::Entity* entity;
			//mTarget = Level::getSingleton()->getPlayerShip();
			
			
			Ogre::Matrix4 matrixA = mGo->getNode()->_getFullTransform()*mBone->_getFullTransform();
			
			Ogre::Matrix4 matrix = matrixA;
			Ogre::Matrix4 transform = matrix.inverse()*mTarget->getNode()->_getFullTransform();
			Ogre::Vector3 v = transform.getTrans();
			/*Util::Log(
					"Bone:"+ts(matrixA.getTrans())+
					" Ship:"+ts(mTarget->getNode()->_getFullTransform().getTrans())+
					" Diff:"+ts(v)
					,0
				);*/


			//targetMatrix = Ogre::Matrix4::IDENTITY;
			//matrix.setTrans(mTarget->getNode()->_getFullTransform());
			

			//Ogre::Quaternion q = transform.extractQuaternion();
			Ogre::Quaternion q;

			switch (mAxis){
				case AXIS_X:
					q.FromAngleAxis(Ogre::Math::ATan2(v.y, v.z),Ogre::Vector3(-1,0,0));
				break;
				case AXIS_Y:
					q.FromAngleAxis(Ogre::Math::ATan2(v.x, v.z),Ogre::Vector3(0,1,0));
				break;
				case AXIS_Z:
					q.FromAngleAxis(Ogre::Math::ATan2(v.x, v.y),Ogre::Vector3(0,0,1));
				break;
				case AXIS_ALL:
					//q.FromAngleAxis(Ogre::Radian(0),v);
					q = transform.extractQuaternion();// - matrixA.extractQuaternion();
					//q = transform.extractQuaternion() - matrixA.extractQuaternion();
				break;
			}

			mBone->setManuallyControlled(true);
			
			//mBone->setOrientation(q);
			float slerp = time*mStrength;
			if (slerp > 1){
				slerp = 1;
			}
			Ogre::Quaternion r = Quaternion::Slerp(slerp, Ogre::Quaternion::IDENTITY, q); //Level::getSingleton()->getTimeDelta()
			
			mBone->rotate(r);
			/*mBone->yaw(Ogre::Radian(Ogre::Math::RangeRandom(-Math::PI, Math::PI)));
			mBone->pitch(Ogre::Radian(Ogre::Math::RangeRandom(-Math::PI, Math::PI)));
			mBone->roll(Ogre::Radian(Ogre::Math::RangeRandom(-Math::PI, Math::PI)));*/
			//mBone->_update(true, true);



			Parent::update(time);
			//mSpeed += .6*time; 
			//mGo->getNode()->translate(0, 0-mSpeed, 0);*/
		}