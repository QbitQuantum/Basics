//----------------------------------------------------------------------------
/// Core rendering method for this control.
///
/// This method scans through all the current client ShapeBase objects.
/// If one is named, it displays the name and damage information for it.
///
/// Information is offset from the center of the object's bounding box,
/// unless the object is a PlayerObjectType, in which case the eye point
/// is used.
///
/// @param   updateRect   Extents of control.
void afxGuiTextHud::onRender( Point2I, const RectI &updateRect)
{
   // Background fill first
   if (mShowFill)
      GFX->getDrawUtil()->drawRectFill(updateRect, mFillColor.toColorI());

   // Must be in a TS Control
   GuiTSCtrl *parent = dynamic_cast<GuiTSCtrl*>(getParent());
   if (!parent) return;

   // Must have a connection and control object
   GameConnection* conn = GameConnection::getConnectionToServer();
   if (!conn)
      return;

   GameBase * control = dynamic_cast<GameBase*>(conn->getControlObject());
   if (!control)
      return;

   // Get control camera info
   MatrixF cam;
   Point3F camPos;
   VectorF camDir;
   conn->getControlCameraTransform(0,&cam);
   cam.getColumn(3, &camPos);
   cam.getColumn(1, &camDir);

   F32 camFovCos;
   conn->getControlCameraFov(&camFovCos);
   camFovCos = mCos(mDegToRad(camFovCos) / 2);

   // Visible distance info & name fading
   F32 visDistance = gClientSceneGraph->getVisibleDistance();
   F32 visDistanceSqr = visDistance * visDistance;
   F32 fadeDistance = visDistance * mDistanceFade;

   // Collision info. We're going to be running LOS tests and we
   // don't want to collide with the control object.
   static U32 losMask = TerrainObjectType | TerrainLikeObjectType | ShapeBaseObjectType;

   if (!mEnableControlObjectOcclusion)
      control->disableCollision();

   if (mLabelAllShapes)
   {
     // This section works just like GuiShapeNameHud and renders labels for
     // all the shapes.

     // All ghosted objects are added to the server connection group,
     // so we can find all the shape base objects by iterating through
     // our current connection.
     for (SimSetIterator itr(conn); *itr; ++itr) 
     {
       ///if ((*itr)->getTypeMask() & ShapeBaseObjectType) 
       ///{
       ShapeBase* shape = dynamic_cast<ShapeBase*>(*itr);
       if ( shape ) {
         if (shape != control && shape->getShapeName()) 
         {

           // Target pos to test, if it's a player run the LOS to his eye
           // point, otherwise we'll grab the generic box center.
           Point3F shapePos;
           if (shape->getTypeMask() & PlayerObjectType) 
           {
             MatrixF eye;

             // Use the render eye transform, otherwise we'll see jittering
             shape->getRenderEyeTransform(&eye);
             eye.getColumn(3, &shapePos);
           }
           else 
           {
             // Use the render transform instead of the box center
             // otherwise it'll jitter.
             MatrixF srtMat = shape->getRenderTransform();
             srtMat.getColumn(3, &shapePos);
           }

           VectorF shapeDir = shapePos - camPos;

           // Test to see if it's in range
           F32 shapeDist = shapeDir.lenSquared();
           if (shapeDist == 0 || shapeDist > visDistanceSqr)
             continue;
           shapeDist = mSqrt(shapeDist);

           // Test to see if it's within our viewcone, this test doesn't
           // actually match the viewport very well, should consider
           // projection and box test.
           shapeDir.normalize();
           F32 dot = mDot(shapeDir, camDir);
           if (dot < camFovCos)
             continue;

           // Test to see if it's behind something, and we want to
           // ignore anything it's mounted on when we run the LOS.
           RayInfo info;
           shape->disableCollision();
           SceneObject *mount = shape->getObjectMount();
           if (mount)
             mount->disableCollision();
           bool los = !gClientContainer.castRay(camPos, shapePos,losMask, &info);
           shape->enableCollision();
           if (mount)
             mount->enableCollision();

           if (!los)
             continue;

           // Project the shape pos into screen space and calculate
           // the distance opacity used to fade the labels into the
           // distance.
           Point3F projPnt;
           shapePos.z += mVerticalOffset;
           if (!parent->project(shapePos, &projPnt))
             continue;
           F32 opacity = (shapeDist < fadeDistance)? 1.0:
             1.0 - (shapeDist - fadeDistance) / (visDistance - fadeDistance);

           // Render the shape's name
           drawName(Point2I((S32)projPnt.x, (S32)projPnt.y),shape->getShapeName(),opacity);
         }
       }
     }
   }

   // This section renders all text added by afxGuiText effects.
   for (S32 i = 0; i < text_items.size(); i++)
   {
     HudTextSpec* spec = &text_items[i];
     if (spec->text && spec->text[0] != '\0') 
     {
       VectorF shapeDir = spec->pos - camPos;

       // do range test
       F32 shapeDist = shapeDir.lenSquared();
       if (shapeDist == 0 || shapeDist > visDistanceSqr)
         continue;
       shapeDist = mSqrt(shapeDist);

       // Test to see if it's within our viewcone, this test doesn't
       // actually match the viewport very well, should consider
       // projection and box test.
       shapeDir.normalize();
       F32 dot = mDot(shapeDir, camDir);
       if (dot < camFovCos)
         continue;

       // Test to see if it's behind something, and we want to
       // ignore anything it's mounted on when we run the LOS.
       RayInfo info;
       if (spec->obj)
         spec->obj->disableCollision();
       bool los = !gClientContainer.castRay(camPos, spec->pos, losMask, &info);
       if (spec->obj)
         spec->obj->enableCollision();
       if (!los)
         continue;

       // Project the shape pos into screen space.
       Point3F projPnt;
       if (!parent->project(spec->pos, &projPnt))
         continue;

       // Calculate the distance opacity used to fade text into the distance.
       F32 opacity = (shapeDist < fadeDistance)? 1.0 : 1.0 - (shapeDist - fadeDistance) / (25.0f);
       if (opacity > 0.01f)
        drawName(Point2I((S32)projPnt.x, (S32)projPnt.y), spec->text, opacity, &spec->text_clr);
     }
   }

   // Restore control object collision
   if (!mEnableControlObjectOcclusion)
      control->enableCollision();

   // Border last
   if (mShowFrame)
      GFX->getDrawUtil()->drawRect(updateRect, mFrameColor.toColorI());

   reset();
}