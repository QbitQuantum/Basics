RotationMatrix ForwardKinematics::calcChestFeetRotation(const KinematicChain& theKinematicChain)
{
  RotationMatrix calculatedRotation;

  // calculate rotation based on foot - torso transformation
  const Pose3D& footLeft = theKinematicChain.theLinks[KinematicChain::LFoot].M;
  const Pose3D& footRight = theKinematicChain.theLinks[KinematicChain::RFoot].M;
  const Pose3D& body = theKinematicChain.theLinks[KinematicChain::Torso].M;

  // local in chest
  Pose3D localFootLeft(body.local(footLeft));
  Pose3D localFootRight(body.local(footRight));
    
  if(abs(localFootLeft.translation.z - localFootRight.translation.z) < 3.f/* magic number */)
  {
    // use average of the calculated rotation of each leg
    double meanX = (localFootLeft.rotation.getXAngle() + localFootRight.rotation.getXAngle())*0.5;
    double meanY = (localFootLeft.rotation.getYAngle() + localFootRight.rotation.getYAngle())*0.5;

    //calculatedRotation.fromKardanRPY(0.0, meanY, meanX);
    calculatedRotation.rotateX(meanX).rotateY(meanY);
  }
  else if(localFootLeft.translation.z > localFootRight.translation.z)
  {
    // use left foot
    calculatedRotation = localFootLeft.rotation;
  }
  else
  {
    // use right foot
    calculatedRotation = localFootRight.rotation;
  }

  return calculatedRotation.invert();
}//end calcChestFeetRotation