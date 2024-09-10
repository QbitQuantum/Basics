void AnimateableCharacter::update(Ogre::Real timeSinceLastFrame)
{
    updatePosition(timeSinceLastFrame);

    if (mClipTo)
        clipToTerrainHeight();

    Ogre::Vector3 velocity = getVelocity(); // Current velocity of agent
    Ogre::Real speed = velocity.length();

    if(speed > 0.15) {
        //mAnimState->setEnabled(true);
        //mAnimState->addTime(mAnimSpeedScale * speed * timeSinceLastFrame);

        if(speed > 0/*0.8*/) {  // Avoid jitter (TODO keep this?)
            // Rotate to look in walking direction
            Ogre::Vector3 src = getLookingDirection();
            src.y = 0;  // Ignore y direction

            velocity.y = 0;
            velocity.normalise();
            mNode->rotate(src.getRotationTo(velocity));
        }
    } else {    // Assume character has stopped
        mAnimState->setEnabled(false);
        mAnimState->setTimePosition(0);
		}
}