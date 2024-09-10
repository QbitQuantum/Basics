// -------------------------------------------------------------------------
void OgreBulletListener::shutdown ()
{
    delete mInputListener;
    delete mGuiListener;

    // OgreBullet physic delete 
    std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
    while (mBodies.end() != itBody)
    {   
        delete *itBody; 
        ++itBody;
    }

    delete mWorld->getDebugDrawer();
    mWorld->setDebugDrawer(0);
    delete mWorld;

    // Ogre delete 
    mSceneMgr->destroyQuery (mRayQuery);
    std::deque<Ogre::Entity *>::iterator itEntity = mEntities.begin();
    while (mEntities.end() != itEntity)
    {
        SceneNode *node = static_cast<SceneNode*>((*itEntity)->getParentNode());
        node->detachObject(*itEntity);
        mSceneMgr->destroyEntity(*itEntity);
        assert (node->getParent());
        static_cast <SceneNode *> (node->getParent())->removeAndDestroyChild(node->getName());

        ++itEntity;
    }
    mEntities.clear();
    mSceneMgr->destroyCamera(mCamera->getName ());
    mWindow->removeViewport(0);
    mRoot->destroySceneManager (mSceneMgr);
    delete mDebugRayLine;

    mInputListener = 0;
    mGuiListener = 0;
    mRayQuery = 0;
    mWorld = 0;
    mCamera = 0;
    mSceneMgr = 0;
    mDebugRayLine = 0;

    mBodies.clear();
    mEntities.clear();
    mShapes.clear();

}