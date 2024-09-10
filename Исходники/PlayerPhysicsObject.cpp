void PlayerPhysicsObject::hover(float delta, float hoverHeight)
{
    float deltaHeightMaximum = 0.0f;
    btVector3 offset[] = {btVector3( 0.15f, 0.0f,  0.15f),
                          btVector3( 0.15f, 0.0f, -0.15f),
                          btVector3(-0.15f, 0.0f,  0.15f),
                          btVector3(-0.15f, 0.0f, -0.15f)
                         };
    for(unsigned int i=0; i<4; i++)
    {
        btVector3 from = btVector3(0.0f, 0.0f, 0.0f);
        btVector3 to = (from - btVector3(0.0f,hoverHeight*2.0f,0.0f)) + offset[i];
        from += offset[i];

        from += getWorldTransform().getOrigin();
        to   += getWorldTransform().getOrigin();

        btQuaternion btqt = getWorldTransform().getRotation();

        btCollisionWorld::ClosestRayResultCallback ray(from,to);
        ray.m_collisionFilterGroup = XKILL_Enums::PhysicsAttributeType::RAY;
        ray.m_collisionFilterMask = XKILL_Enums::PhysicsAttributeType::WORLD;
        dynamicsWorld_->rayTest(from,to,ray); //cast ray from player position straight down
        if(ray.hasHit())
        {
            btVector3 point = from.lerp(to,ray.m_closestHitFraction);
            float length = (point - from).length();
            float deltaHeight = hoverHeight-length;
            if(deltaHeight > deltaHeightMaximum)
            {
                deltaHeightMaximum = deltaHeight;
            }
        }
        debugDrawer_->drawLine(from, to, btVector3(0.2f, 1.0f, 0.2f));
    }

    bool isHovering = false;

    if(deltaHeightMaximum > 0.0f)
    {
        btTransform worldTransform;
        worldTransform = getWorldTransform();
        worldTransform.setOrigin(worldTransform.getOrigin() + btVector3(0.0f,deltaHeightMaximum,0.0f)*delta/0.25f);
        setWorldTransform(worldTransform);

        setLinearVelocity(getLinearVelocity()+btVector3(0.0f,-getLinearVelocity().y(),0.0f));

        isHovering = true;
    }

    std::vector<int> playerAttributes = itrPhysics_3.ownerAt(attributeIndex_)->getAttributes(ATTRIBUTE_PLAYER);
    for(unsigned int i=0; i<playerAttributes.size(); i++)
    {
        AttributePtr<Attribute_Player> ptr_player = itrPlayer.at(playerAttributes.at(i));
        ptr_player->hovering = isHovering;
    }
}