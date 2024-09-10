  Button* check(const Ogre::Ray& ray, bool& isOver)
  {
   
   isOver = false;
   
   Ogre::Matrix4 transform;
   transform.makeTransform(mNode->getPosition(), mNode->getScale(), mNode->getOrientation());
   
   Ogre::AxisAlignedBox aabb = mScreen->getBoundingBox();
   aabb.transform(transform);
   std::pair<bool, Ogre::Real> result = Ogre::Math::intersects(ray, aabb);

   if (result.first == false)
     return 0;
   
   Ogre::Vector3 a,b,c,d;
   Ogre::Vector2 halfSize = mSize * 0.5f;
   a = transform * Ogre::Vector3(-halfSize.x,-halfSize.y,0);
   b = transform * Ogre::Vector3( halfSize.x,-halfSize.y,0);
   c = transform * Ogre::Vector3(-halfSize.x, halfSize.y,0);
   d = transform * Ogre::Vector3( halfSize.x, halfSize.y,0);
    
   result = Ogre::Math::intersects(ray, c, b, a);
   if (result.first == false)
    result = Ogre::Math::intersects(ray, c, d, b);
   if (result.first == false)
    return 0;
   
   if (result.second > 6.0f)
    return 0;
   
   isOver = true;
   
   Ogre::Vector3 hitPos = ( ray.getOrigin() + (ray.getDirection() * result.second) );
   Ogre::Vector3 localPos = transform.inverse() * hitPos;
   localPos.x += halfSize.x;
   localPos.y -= halfSize.y;
   localPos.x *= 100;
   localPos.y *= 100;
   
   // Cursor clip
   localPos.x = Ogre::Math::Clamp<Ogre::Real>(localPos.x, 0, (mSize.x * 100) - 10);
   localPos.y = Ogre::Math::Clamp<Ogre::Real>(-localPos.y, 0, (mSize.y * 100) - 18);
   
   mMousePointer->position(localPos.x, localPos.y);

   for (size_t i=0;i < mButtons.size();i++)
   {
    if (mButtons[i]->isOver(mMousePointer->position()))
     return mButtons[i];
   }
   
   return 0;
  }