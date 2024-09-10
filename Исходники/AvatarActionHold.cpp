bool AvatarActionHold::getTarget(float deltaTimeStep, glm::quat& rotation, glm::vec3& position,
                                 glm::vec3& linearVelocity, glm::vec3& angularVelocity,
                                 float& linearTimeScale, float& angularTimeScale) {
    auto avatarManager = DependencyManager::get<AvatarManager>();
    auto holdingAvatar = std::static_pointer_cast<Avatar>(avatarManager->getAvatarBySessionID(_holderID));

    if (!holdingAvatar) {
        return false;;
    }

    withReadLock([&]{
        bool isRightHand = (_hand == "right");

        glm::vec3 palmPosition;
        glm::quat palmRotation;

        if (holdingAvatar->isMyAvatar()) {
            std::shared_ptr<MyAvatar> myAvatar = avatarManager->getMyAvatar();

            // fetch the hand controller pose
            controller::Pose pose;
            if (isRightHand) {
                pose = myAvatar->getControllerPoseInWorldFrame(controller::Action::RIGHT_HAND);
            } else {
                pose = myAvatar->getControllerPoseInWorldFrame(controller::Action::LEFT_HAND);
            }

            if (pose.isValid()) {
                linearVelocity = pose.getVelocity();
                angularVelocity = pose.getAngularVelocity();
            }

            if (_ignoreIK && pose.isValid()) {

                // this position/rotation should be the same as the one in scripts/system/libraries/controllers.js
                // otherwise things will do a little hop when you grab them.

                // if (isRightHand) {
                //     pose = myAvatar->getRightHandControllerPoseInAvatarFrame();
                // } else {
                //     pose = myAvatar->getLeftHandControllerPoseInAvatarFrame();
                // }
                // glm::vec3 camRelPos = pose.getTranslation();
                // glm::quat camRelRot = pose.getRotation();

                int camRelIndex = isRightHand ?
                    CAMERA_RELATIVE_CONTROLLER_RIGHTHAND_INDEX :
                    CAMERA_RELATIVE_CONTROLLER_LEFTHAND_INDEX;
                glm::vec3 camRelPos = myAvatar->getAbsoluteJointTranslationInObjectFrame(camRelIndex);
                glm::quat camRelRot = myAvatar->getAbsoluteJointRotationInObjectFrame(camRelIndex);

                Transform avatarTransform;
                avatarTransform = myAvatar->getTransform();
                palmPosition = avatarTransform.transform(camRelPos);
                palmRotation = avatarTransform.getRotation() * camRelRot;
            } else {
                glm::vec3 avatarRigidBodyPosition;
                glm::quat avatarRigidBodyRotation;
                getAvatarRigidBodyLocation(avatarRigidBodyPosition, avatarRigidBodyRotation);

                // the offset and rotation between the avatar's rigid body and the palm were determined earlier
                // in prepareForPhysicsSimulation.  At this point, the avatar's rigid body has been moved by bullet
                // and the data in the Avatar class is stale.  This means that the result of get*PalmPosition will
                // be stale.  Instead, determine the current palm position with the current avatar's rigid body
                // location and the saved offsets.

                // this line is more correct but breaks for the current way avatar data is updated.
                // palmPosition = avatarRigidBodyPosition + avatarRigidBodyRotation * _palmOffsetFromRigidBody;
                // instead, use this for now:
                palmPosition = avatarRigidBodyPosition + _palmOffsetFromRigidBody;

                // the item jitters the least by getting the rotation based on the opinion of Avatar.h rather
                // than that of the rigid body.  leaving this next line here for future reference:
                // palmRotation = avatarRigidBodyRotation * _palmRotationFromRigidBody;

                if (isRightHand) {
                    palmRotation = holdingAvatar->getRightPalmRotation();
                } else {
                    palmRotation = holdingAvatar->getLeftPalmRotation();
                }
            }
        } else { // regular avatar
            if (isRightHand) {
                Transform controllerRightTransform = Transform(holdingAvatar->getControllerRightHandMatrix());
                Transform avatarTransform = holdingAvatar->getTransform();
                palmRotation = avatarTransform.getRotation() * controllerRightTransform.getRotation();
                palmPosition = avatarTransform.getTranslation() +
                    (avatarTransform.getRotation() * controllerRightTransform.getTranslation());
            } else {
                Transform controllerLeftTransform = Transform(holdingAvatar->getControllerLeftHandMatrix());
                Transform avatarTransform = holdingAvatar->getTransform();
                palmRotation = avatarTransform.getRotation() * controllerLeftTransform.getRotation();
                palmPosition = avatarTransform.getTranslation() +
                    (avatarTransform.getRotation() * controllerLeftTransform.getTranslation());
            }
        }

        rotation = palmRotation * _relativeRotation;
        position = palmPosition + rotation * _relativePosition;

        // update linearVelocity based on offset via _relativePosition;
        linearVelocity = linearVelocity + glm::cross(angularVelocity, position - palmPosition);

        linearTimeScale = _linearTimeScale;
        angularTimeScale = _angularTimeScale;
    });

    return true;
}