bool Panel::injectMouseMoved(const Ogre::Ray& ray)
{
    Ogre::Matrix4 transform;
    transform.makeTransform(mNode->getPosition(), mNode->getScale(), mNode->getOrientation());
   
    Ogre::AxisAlignedBox aabb = mScreenRenderable->getBoundingBox();
    aabb.transform(transform);
    pair<bool, Ogre::Real> result = Ogre::Math::intersects(ray, aabb);

    if (result.first == false)
    {
        unOverAllElements();
        return false;
    }

    Ogre::Vector3 a,b,c,d;
    Ogre::Vector2 halfSize = (mSize/100) * 0.5f;
    a = transform * Ogre::Vector3(-halfSize.x,-halfSize.y,0);
    b = transform * Ogre::Vector3( halfSize.x,-halfSize.y,0);
    c = transform * Ogre::Vector3(-halfSize.x, halfSize.y,0);
    d = transform * Ogre::Vector3( halfSize.x, halfSize.y,0);
    
    result = Ogre::Math::intersects(ray, c, b, a);
    if (result.first == false)
        result = Ogre::Math::intersects(ray, c, d, b);
    if (result.first == false)
    {
        unOverAllElements();
        return false;
    }
    if (result.second > mDistanceFromPanelToInteractWith)
    {
        unOverAllElements();
        return false;
    }

    Ogre::Vector3 hitPos = (ray.getOrigin() + (ray.getDirection() * result.second));
    Ogre::Vector3 localPos = transform.inverse() * hitPos;
    localPos.x += halfSize.x;
    localPos.y -= halfSize.y;
    localPos.x *= 100;
    localPos.y *= 100;
   
    // Cursor clip
    localPos.x = Ogre::Math::Clamp<Ogre::Real>(localPos.x, 0, mSize.x - 10);
    localPos.y = Ogre::Math::Clamp<Ogre::Real>(-localPos.y, 0, mSize.y - 18);

    mInternalMousePos = Ogre::Vector2(localPos.x, localPos.y);
    mMousePointer->position(mInternalMousePos);

    // Let's actualize the "over" for each elements
    for (size_t i=0; i < mPanelElements.size(); i++)
        mPanelElements[i]->isOver(mInternalMousePos);

    return true;
}