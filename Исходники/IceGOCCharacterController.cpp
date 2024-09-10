void GOCCharacterController::ReceiveMessage(Msg &msg)
{
    GOComponent::ReceiveMessage(msg);
    if (msg.typeID == GlobalMessageIDs::PHYSICS_SUBSTEP && !mFreezed)
    {
        GameObjectPtr owner = mOwnerGO.lock();

        float time = msg.params.GetFloat("TIME");
        Ogre::Vector3 finalDir = Ogre::Vector3(0,0,0);
        Ogre::Vector3 userDir = owner->GetGlobalOrientation() * mDirection;

        if (mActor.getPxActor()->isSleeping())
            mActor.getPxActor()->wakeUp();		//Gravity fix

        Ogre::Vector3 playerHalfSize = mDimensions * 0.5f;

        PxTransform transform(OgrePhysX::toPx(owner->GetGlobalPosition()), OgrePhysX::toPx(owner->GetGlobalOrientation()));
        transform.p.y += playerHalfSize.y;

        //sweep filter data - only check against shapes with filter data DYNAMICBODY or STATICBODY
        PxSceneQueryFilterData filterData;
        filterData.data.word0 = CollisionGroups::DYNAMICBODY|CollisionGroups::STATICBODY;
        filterData.flags = PxSceneQueryFilterFlag::eDYNAMIC|PxSceneQueryFilterFlag::eSTATIC;

        //touches ground check
        PxBoxGeometry playerGeometry(playerHalfSize.x, playerHalfSize.y+0.1f, playerHalfSize.z);
        PxShape *outShape;
        mTouchesGround = Main::Instance().GetPhysXScene()->getPxScene()->overlapAny(playerGeometry, transform, outShape, filterData);

        //stair maxStepHeight
        float maxStepHeight = 0.6f;
        PxVec3 currPos = OgrePhysX::Convert::toPx(owner->GetGlobalPosition());

        //feet capsule
        PxBoxGeometry feetVolume(playerHalfSize.x, maxStepHeight*0.5f, playerHalfSize.z);

        //body capsule
        float bodyHeight = mDimensions.y-maxStepHeight;
        PxBoxGeometry bodyVolume(playerHalfSize.x, bodyHeight*0.5f, playerHalfSize.z);

        PxVec3 sweepDirection = OgrePhysX::toPx(userDir);
        float userDirLength = sweepDirection.normalize();

        /*
        We perform two sweeps:
         O    ==> bodyHit?
         |    ==> bodyHit?
        / \   ==> feetHit?

        If there are no hits character can walk in the desired direction.
        If there is a feetHit but no bodyHit player can climb stairs (we add an y-Offset).
        If there is a bodyHit the player can not move.
        */
        PxSweepHit sweepHit;
        transform.p.y = owner->GetGlobalPosition().y + maxStepHeight + bodyHeight*0.5f;
        bool bodyHit = Main::Instance().GetPhysXScene()->getPxScene()->sweepSingle(bodyVolume, transform, sweepDirection, time*userDirLength, PxSceneQueryFlags(), sweepHit, filterData);
        transform.p.y = owner->GetGlobalPosition().y + maxStepHeight*0.5f;
        bool feetHit = Main::Instance().GetPhysXScene()->getPxScene()->sweepSingle(feetVolume, transform, sweepDirection, time*userDirLength, PxSceneQueryFlags(), sweepHit, filterData);

        if (!bodyHit)
        {
            finalDir += userDir;	//add player movement
            if (feetHit)
                finalDir += Ogre::Vector3(0,3,0); //climb stairs
        }

        if (finalDir != Ogre::Vector3(0,0,0))
            mActor.getPxActor()->setGlobalPose(PxTransform(currPos + OgrePhysX::Convert::toPx(finalDir*time)));

        if (mJumping && mTouchesGround && (timeGetTime() - mJumpStartTime > 400))
        {
            mJumping = false;
            Msg jump_response;
            jump_response.typeID = ObjectMessageIDs::END_JUMP;
            BroadcastObjectMessage(jump_response);
        }
    }
    if (msg.typeID == GlobalMessageIDs::PHYSICS_END && !mFreezed)
    {
        SetOwnerPosition(mActor.getGlobalPosition());
        //SetOwnerOrientation(mActor->getGlobalOrientation());
    }


    if (msg.typeID == ObjectMessageIDs::UPDATE_CHARACTER_MOVEMENTSTATE)
    {
        mDirection = Ogre::Vector3(0,0,0);
        int movementFlags = msg.params.GetInt("CharacterMovementState");
        if (movementFlags & CharacterMovement::FORWARD) mDirection.z += 1;
        if (movementFlags & CharacterMovement::BACKWARD) mDirection.z -= 1;
        if (movementFlags & CharacterMovement::LEFT) mDirection.x += 1;
        if (movementFlags & CharacterMovement::RIGHT) mDirection.x -= 1;

        mDirection.normalise();
        mDirection*=(mMovementSpeed*mSpeedFactor);
    }
    if (msg.typeID == ObjectMessageIDs::INPUT_START_JUMP)
    {
        if (mTouchesGround && !mJumping)
        {
            mJumping = true;
            mJumpStartTime = timeGetTime();
            mActor.getPxActor()->addForce(PxVec3(0, mActor.getPxActor()->getMass()*8, 0), PxForceMode::eIMPULSE);
            Msg startJumpMsg;
            startJumpMsg.typeID = ObjectMessageIDs::START_JUMP;
            BroadcastObjectMessage(startJumpMsg);
        }
    }
    if (msg.typeID == ObjectMessageIDs::CHARACTER_KILL)
    {
        mFreezed = true;
    }
}