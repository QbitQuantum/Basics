/*!
  Moves the element from its current pose to the new pose specified by \a tr.
  This motion is performed in several steps such that the translation
  between each step does not exceed \a translStepSize and the angle of
  rotation does not exceed \a rotStepSize (expressed in radians).  The
  intermediate poses are determined using linear interpolation for the
  translation and spherical linear interpolation for the rotation.  If
  a collision is encountered during the motion, the point of first contact
  is determined and the element is left in that position.  This function
  returns false if a collision was encountered (or contacts prevented the motion)
  or true if no collisions were encountered and the move was completed.
*/
bool
WorldElement::moveTo(transf &newTran,double translStepSize, double rotStepSize)
{
    bool moveFinished = false;
    transf origTran,nextTran,motion;
    Quaternion nextRotation;
    vec3 nextTranslation;
    double percentComplete,moveIncrement,translationLength;
    double angle;
    vec3 axis;
    bool success;

    CollisionReport contactReport;

    //DBGP("moveTo called");

    origTran = getTran();
    /*
    	std::cout << "WorldElement origTran: " << origTran.translation().x() << " " <<
    		origTran.translation().y() << " " <<
    		origTran.translation().z() << " " <<
    		origTran.rotation().w << " " <<
    		origTran.rotation().x << " " <<
    		origTran.rotation().y << " " <<
    		origTran.rotation().z << " " << "\n";
    */
    //calculate the difference
    translationLength = (newTran.translation() - origTran.translation()).len();
    nextRotation = newTran.rotation() * origTran.rotation().inverse();
    nextRotation.ToAngleAxis(angle,axis);

    moveIncrement = 1.0;
    if (translationLength != 0.0) {
        if (translStepSize == ONE_STEP)
            moveIncrement = 1.0;
        else
            moveIncrement = MIN(moveIncrement, translStepSize / translationLength);
    }
    if (angle != 0.0) {
        if (rotStepSize == ONE_STEP)
            moveIncrement = MIN(moveIncrement, 1.0);
        else
            moveIncrement = MIN(moveIncrement, rotStepSize / angle);
    }

    // check contacts
    nextTranslation = (1.0-moveIncrement)*origTran.translation() + moveIncrement*newTran.translation();
    nextRotation = Quaternion::Slerp(moveIncrement,origTran.rotation(), newTran.rotation());
    nextTran = transf(nextRotation,nextTranslation);
    motion = nextTran * getTran().inverse();

    if (contactsPreventMotion(motion)) {
        DBGP("contacts prevent motion")
        return false;
    }

    percentComplete = 0.0;
    while (!moveFinished) {
        percentComplete += moveIncrement;
        if (percentComplete >= 1.0) {
            percentComplete = 1.0;
            moveFinished = true;
        }

        nextTranslation = (1.0-percentComplete)*origTran.translation() + percentComplete*newTran.translation();
        nextRotation = Quaternion::Slerp(percentComplete,origTran.rotation(), newTran.rotation());
        nextTran = transf(nextRotation,nextTranslation);
        /*
        		std::cout << "moveTo NextTran: " << nextTran.translation().x() << " " <<
        			nextTran.translation().y() << " " <<
        			nextTran.translation().z() << " " <<
        			nextTran.rotation().w << " " <<
        			nextTran.rotation().x << " " <<
        			nextTran.rotation().y << " " <<
        			nextTran.rotation().z << " " << "\n";
        */
        success = jumpTo(nextTran, &contactReport);
        if (!success || contactReport.size() != 0) {
            moveFinished = true;
        }
    }

    if (!success) {
        DBGA("JumpTo error, stopping execution. Object " << myName.latin1() << " in thread "
             << getWorld()->getCollisionInterface()->getThreadId());
    } else {
        myWorld->findContacts(contactReport);
    }

    if (contactReport.size() != 0) return false;
    return true;
}