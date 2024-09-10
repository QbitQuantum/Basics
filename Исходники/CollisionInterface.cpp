void CollisionInterface::updateBodyNodes() {
    int numNodes = mNodeMap.size();
    for (std::map<BodyNode*, RigidBody*>::iterator it = mNodeMap.begin(); it != mNodeMap.end(); ++it) {
        BodyNode *bn = it->first;
        RigidBody *rb = it->second;
        if (bn->getSkeleton()->getName() == "pinata")
            continue;
        Isometry3d W;
        W.setIdentity();
        W.linear() = rb->mOrientation;
        W.translation() = rb->mPosition;
        W.makeAffine();
        bn->getSkeleton()->getJoint("freeJoint")->setTransformFromParentBodyNode(W);
        //bn->updateTransform();
        bn->getSkeleton()->computeForwardKinematics(true, false, false);
    }
}