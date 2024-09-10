    // -------------------------------------------------------------------------
    void Object::setOrientation(const btQuaternion &quat)
    {   
		mRootNode->setOrientation(quat.getW(),quat.getX(), quat.getY(), quat.getZ());
    }