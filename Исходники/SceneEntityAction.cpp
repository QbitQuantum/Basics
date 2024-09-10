    //-----------------------------------------------------------------------
    Bool CCSEntityLineMoveAcion::isNeedMoveToStartPos()
    {
        if ( !mEntity )
            return false;

        if ( !mEntity->getEntity() )
            return false ;

        ISceneNode* sceneNode = mEntity->getEntity()->getSceneNode();
        if( !sceneNode )
        {
            return false ;
        }

        Vec3 currPos;
        sceneNode->getPosition(currPos);

        Vec3 ec = mEndPos - currPos;
        Vec3 es = mEndPos - mStartPos;

        ec.y = 0;
        es.y = 0;

        Flt currDis = ec.length();
        Flt dis     = es.length();

        if ( currDis > dis  )
            return true;

        return false;
    }