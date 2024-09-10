void CustomConvexConvexPairCollision::processCollision (btCollisionObject* body0,btCollisionObject* body1,const btDispatcherInfo& dispatchInfo,btManifoldResult* resultOut)
{
#if 0
    if (!m_manifoldPtr)
    {
        //swapped?
        m_manifoldPtr = m_dispatcher->getNewManifold(body0,body1);
        m_ownManifold = true;
    }
    resultOut->setPersistentManifold(m_manifoldPtr);


    CustomConvexShape* convex0 = (CustomConvexShape*)body0->getCollisionShape();
    CustomConvexShape* convex1 = (CustomConvexShape*)body1->getCollisionShape();


    float4 bodyApos;
    float4 bodyBpos;
    Quaternion bodyAquat;
    Quaternion bodyBquat;

    const btTransform& transA = body0->getWorldTransform();
    const btTransform& transB = body1->getWorldTransform();

    const btVector3& pA = body0->getWorldTransform().getOrigin();
    const btVector3& pB = body1->getWorldTransform().getOrigin();

    btQuaternion qA = body0->getWorldTransform().getRotation();
    btQuaternion qB = body1->getWorldTransform().getRotation();

    bodyApos.x = pA.getX();
    bodyApos.y = pA.getY();
    bodyApos.z = pA.getZ();
    bodyApos.w = 0.f;

    bodyBpos.x = pB.getX();
    bodyBpos.y = pB.getY();
    bodyBpos.z = pB.getZ();
    bodyBpos.w = 0.f;

    bodyAquat.x = qA.getX();
    bodyAquat.y = qA.getY();
    bodyAquat.z = qA.getZ();
    bodyAquat.w = qA.getW();

    bodyBquat.x = qB.getX();
    bodyBquat.y = qB.getY();
    bodyBquat.z = qB.getZ();
    bodyBquat.w = qB.getW();


#define CAPACITY_CONTACTS 4

    ContactPoint4 contactsOut[CAPACITY_CONTACTS];
    int freeContactIndex = 0;
    int contactCapacity = CAPACITY_CONTACTS;
    float collisionMargin = 0.001f;

    m_manifoldPtr->refreshContactPoints(body0->getWorldTransform(),body1->getWorldTransform());

    collideStraight(convex0->m_ConvexHeightField,convex1->m_ConvexHeightField,
                    bodyApos, bodyAquat,bodyBpos,bodyBquat,
                    contactsOut, freeContactIndex, contactCapacity,
                    collisionMargin );
    collideStraight(convex1->m_ConvexHeightField,convex0->m_ConvexHeightField,
                    bodyBpos, bodyBquat,bodyApos,bodyAquat,
                    contactsOut, freeContactIndex, contactCapacity,
                    collisionMargin );

    //copy points into manifold
    //refresh manifold

    btAssert(freeContactIndex<3);
    for (int j=0; j<freeContactIndex; j++)
    {
        int numPoints = contactsOut[j].getNPoints();
//		printf("numPoints = %d\n",numPoints);

        for (int i=0; i<numPoints; i++)
        {

            ContactPoint4& c = contactsOut[j];

            btVector3 normalOnBInWorld(
                c.m_worldNormal.x,
                c.m_worldNormal.y,
                c.m_worldNormal.z);
            btVector3 pointInWorldOnB(
                c.m_worldPos[i].x,
                c.m_worldPos[i].y,
                c.m_worldPos[i].z);
            btScalar depth = c.m_worldPos[i].w;
            if (depth<0)
            {

                const btVector3 deltaC = transB.getOrigin() - transA.getOrigin();
                if((deltaC.dot(normalOnBInWorld))>0.0f)
                {
                    normalOnBInWorld= -normalOnBInWorld;
                }
                normalOnBInWorld.normalize();
                if (j)
                {
                    resultOut->addContactPoint(normalOnBInWorld, pointInWorldOnB, depth);
                } else
                {
                    resultOut->addContactPoint(normalOnBInWorld, pointInWorldOnB-normalOnBInWorld*depth, depth);
                }
            }
        }
    }
#else
    btConvexConvexAlgorithm::processCollision(body0,body1,dispatchInfo,resultOut);
#endif
}