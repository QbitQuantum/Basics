    bool StepRecognitionMovement::run(Ogre::Real elapsedTime,  Ogre::Vector3 direction, Ogre::Vector3 rotation)
    {
        Vector3 vel = mMovingCreature->getCreature()->getActor()->getPhysicalThing()->getVelocity();
        Real velY = vel.y;
        vel.y = 0;
        // raycast in the direction we should move to
        Vector3 globalDir = mMovingCreature->getCreature()->getOrientation() * direction; // the direction in global space
        if( globalDir == Vector3::ZERO )
            return true;



        // the materials that are triggered here
        PhysicsMaterialRaycast::MaterialVector materialVector;
        materialVector.push_back(PhysicsManager::getSingleton().getMaterialID("character")); // should we perhaps only use level here?
        materialVector.push_back(PhysicsManager::getSingleton().getMaterialID("camera"));



        // first of all check if we are not standing in front of a wall or sth like this
        PhysicalThing *thing = mMovingCreature->getCreature()->getActor()->getPhysicalThing();
        Real height = thing->_getBody()->getCollision()->getAABB().getSize().y;
        Vector3 start = mMovingCreature->getCreature()->getPosition() + Vector3(0,height/2,0);
        Vector3 end = start + globalDir * 0.5;
        RaycastInfo info;
        info = mRaycast.execute(
                PhysicsManager::getSingleton()._getNewtonWorld(),
                &materialVector,
                start,
                end,
                true);
        if(info.mBody)
        {
            mMoveToNextTarget = false;
            return false;
        }



        if( !mMoveToNextTarget ) // check if we need to move up for a step
        {
            Real raylen = vel.length() / 3;  // use longer ray, if higher velocity
            if ( raylen < 0.5 )
                raylen = 0.4;

            //std::ostringstream oss;
            //oss << "StepRecognition Raylen: " << raylen;
            //LOG_MESSAGE(Logger::RULES, oss.str());


            // raycasts
            Vector3 start = mMovingCreature->getCreature()->getPosition() + Vector3::UNIT_Y * 0.1f;
            globalDir.y = 0;
            globalDir.normalise();
            Vector3 end = start + globalDir*raylen;

            bool foundbody = false;
            Real foundDistance = 0;

            RaycastInfo info;
            do
            {
                info = 
                    mRaycast.execute(
                            PhysicsManager::getSingleton()._getNewtonWorld(),
                            &materialVector,
                            start, end, true);

                // do we need to check bodies left and right of this ray? (step width?)


                // already found nearer body
                if( foundbody )
                {
                    if( info.mBody && (info.mDistance*raylen >= foundDistance*raylen + 0.19) || // step deep enough
                            !info.mBody )
                    {
                        // found a step
                        mMoveToNextTarget = true;
                        mNextTarget = start + globalDir*raylen*foundDistance + 0.1 * globalDir;
                        std::ostringstream oss;
                        Vector3 stepInLocalCoords = mNextTarget - mMovingCreature->getCreature()->getPosition();
                        Quaternion ori = mMovingCreature->getCreature()->getOrientation();
                        stepInLocalCoords = ori.Inverse() * stepInLocalCoords;
                        oss << "Step-Recognition: Next Step: " << stepInLocalCoords;
                        LOG_MESSAGE(Logger::RULES, oss.str());
                        break;
                    }
                }

                if( info.mBody )
                {
                    foundbody = true;
                    foundDistance = info.mDistance;
                }


                start += Vector3::UNIT_Y * 0.05f;
                end += Vector3::UNIT_Y * 0.05f;
            }
            while( info.mBody && (start - mMovingCreature->getCreature()->getPosition()).y <= 0.5 );
        }


        // check if the target is still needed
        // perform check also to verify found step
        if( mMoveToNextTarget )
        {
            Vector3 diffToTarget = mNextTarget - mMovingCreature->getCreature()->getPosition();
            Real diffToTargetY = diffToTarget.y;
            diffToTarget.y = 0;

            // different direction
            Vector3 globalDir = mMovingCreature->getCreature()->getOrientation() * direction; // the direction in global space
            globalDir.y = 0;


            if( globalDir == Vector3::ZERO )
            {
                mMoveToNextTarget = false;
                LOG_MESSAGE(Logger::RULES, "Testing Step-Recognition: Step direction null");
                return false;
            }

            // target reached
            if( diffToTarget.squaredLength() < 0.01)
            {
                mMoveToNextTarget = false;
                LOG_MESSAGE(Logger::RULES, "Testing Step-Recognition: Step reached");
                return false;
            }

            // different direction
            Quaternion oriDiff = diffToTarget.getRotationTo(globalDir, Vector3::UNIT_Y);
            Degree angleDiff;
            Vector3 axis = Vector3::UNIT_Y;
            oriDiff.ToAngleAxis(angleDiff, axis);
            Real f = angleDiff.valueDegrees();
            //std::ostringstream oss;
            //oss << "Step-Recognition: angle: " << f << "    axis: " << axis;
            //LOG_MESSAGE(Logger::RULES, oss.str());
            //if( !diffToTarget.directionEquals(globalDir, Degree(15)) )
            if( f > 2.0f )
            {
                mMoveToNextTarget = false;
                //LOG_MESSAGE(Logger::RULES, "Testing Step-Recognition: Step direction wrong");
                return false;
            }


            // already above target, but slow velocity
            if( diffToTargetY < 0 && fabs(velY) < 0.01 )
            {
                mMoveToNextTarget = false;
                //LOG_MESSAGE(Logger::RULES, "Testing Step-Recognition: slow and abov target-height!");
                return false;
            }
        }

        return mMoveToNextTarget;
    }