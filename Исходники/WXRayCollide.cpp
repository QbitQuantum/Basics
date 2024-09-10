std::pair<bool, Real>
rayCollide(const Ogre::Ray& ray,
           Ogre::MovableObject* movable,
           bool accurate,
           CullingMode cullingMode,
           bool allowAnimable)
{
    // Get local space axis aligned bounding box
    const Ogre::AxisAlignedBox& aabb = movable->getBoundingBox();

    // Matrix4 to transform local space to world space
    const Ogre::Matrix4& localToWorld = movable->_getParentNodeFullTransform();

    // Matrix4 to transform world space to local space
    Ogre::Matrix4 worldToLocal = localToWorld.inverse();

    // Matrix3 to transform world space normal to local space
    Ogre::Matrix3 worldToLocalN;
    worldToLocal.extract3x3Matrix(worldToLocalN);

    // Convert world space ray to local space ray
    // Note:
    //      By preserving the scale between world space and local space of the
    //      direction, we don't need to recalculate the distance later.
    Ogre::Ray localRay;
    localRay.setOrigin(worldToLocal * ray.getOrigin());
    localRay.setDirection(worldToLocalN * ray.getDirection());

    // Intersect with axis aligned bounding box, but because we transformed
    // ray to local space of the bounding box, so this test just like test
    // with oriented bounding box.
    std::pair<bool, Real> ret = localRay.intersects(aabb);

    // Do accurate test if hitted bounding box and user required.
    if (ret.first && accurate)
    {
        if (movable->getMovableType() == Ogre::EntityFactory::FACTORY_TYPE_NAME ||
            allowAnimable && movable->getMovableType() == Ogre::AutoAnimationEntityFactory::FACTORY_TYPE_NAME)
        {
            Ogre::Entity* entity = static_cast<Ogre::Entity*>(movable);
            if (!entity->_isAnimated())
            {
                // Static entity

                // Get the entity mesh
                const Ogre::MeshPtr& mesh = entity->getMesh();

                // Get the collision mode
                CollisionModelPtr collisionModel = CollisionModelManager::getSingleton().getCollisionModel(mesh);

                ret = doPicking(localRay, *collisionModel, cullingMode);
            }
            else if (allowAnimable)
            {
                // Animation entity

                bool addedSoftwareAnimation = false;
                if (entity->getSoftwareAnimationRequests() <= 0)
                {
                    entity->addSoftwareAnimationRequest(false);
                    entity->_updateAnimation();
                    addedSoftwareAnimation = true;
                }

                CollisionModel collisionModel;
                collisionModel.addEntity(entity);
                collisionModel.build(true);

                ret = doPicking(localRay, collisionModel, cullingMode);

                if (addedSoftwareAnimation)
                {
                    entity->removeSoftwareAnimationRequest(false);
                }
            }
        }
    }

    return ret;
}