void ossimPlanetSceneView::getLookDirection(osg::Vec3d& direction)const
{
   osg::Vec3 eyeTemp(0,0,0);
   osg::Vec3 center(0,0,0);
   osg::Vec3 up(0,0,0);
   
   (const_cast<ossimPlanetSceneView*>(this))->getViewMatrixAsLookAt(eyeTemp, center, up);

   direction = (center-eyeTemp);

   direction.normalize();
}