void dtAnim::GetCelestialCoordinates(osg::Vec3 target,
                                     const osg::Vec3 &lookForward,                                    
                                     float &azimuth, 
                                     float &elevation)
{  
   target.normalize();

   // Derive the reference frame for the "look" pose
   osg::Vec3 frameRight = lookForward ^ osg::Z_AXIS;
   osg::Vec3 frameUp    = frameRight ^ lookForward;

   osg::Matrix frameMatrix(frameRight.x(),  frameRight.y(),  frameRight.z(),  0.0f,                            
                           lookForward.x(), lookForward.y(), lookForward.z(), 0.0f,
                           frameUp.x(),     frameUp.y(),     frameUp.z(),     0.0f,
                           0.0f,            0.0f,            0.0f,            1.0f);  

   // Transform the target into the proper coordinate frame
   target = frameMatrix * target;

   // Project our target vector onto the xy plane 
   // in order to calculate azimuth
   osg::Vec3f targetRight = target ^ osg::Z_AXIS;
   targetRight.normalize();

   osg::Vec3f targetForward = osg::Z_AXIS ^ targetRight;
   targetForward.normalize();    

   // Use the projected vector to calculate the azimuth
   // between the projection and the character forward
   float lookDotTargetForward   = targetForward * osg::Y_AXIS;
   float targetDotTargetForward = targetForward * target;

   // acos needs it's parameter between -1 and 1
   dtUtil::Clamp(lookDotTargetForward, -1.0f, 1.0f);
   dtUtil::Clamp(targetDotTargetForward, -1.0f, 1.0f);

   // We need to manually determine the sign
   float azimuthSign   = ((target * osg::X_AXIS) > 0.0f) ? -1.0f: 1.0f;    
   float elevationSign = ((target * osg::Z_AXIS) > 0.0f) ? 1.0f: -1.0f;

   // We can use the angle between the projection
   // and the original target to determine elevation
   elevation  = acos(targetDotTargetForward) * elevationSign;
   azimuth    = acos(lookDotTargetForward) * azimuthSign;
}