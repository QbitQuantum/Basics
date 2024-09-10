void FPSViewController::setPropertiesFromCamera( Ogre::Camera* source_camera )
{
  Ogre::Quaternion quat = source_camera->getOrientation() * ROBOT_TO_CAMERA_ROTATION.Inverse();
  float yaw = quat.getRoll( false ).valueRadians(); // OGRE camera frame looks along -Z, so they call rotation around Z "roll".
  float pitch = quat.getYaw( false ).valueRadians(); // OGRE camera frame has +Y as "up", so they call rotation around Y "yaw".

  Ogre::Vector3 direction = quat * Ogre::Vector3::NEGATIVE_UNIT_Z;

  if ( direction.dotProduct( Ogre::Vector3::NEGATIVE_UNIT_Z ) < 0 )
  {
    if ( pitch > Ogre::Math::HALF_PI )
    {
      pitch -= Ogre::Math::PI;
    }
    else if ( pitch < -Ogre::Math::HALF_PI )
    {
      pitch += Ogre::Math::PI;
    }

    yaw = -yaw;

    if ( direction.dotProduct( Ogre::Vector3::UNIT_X ) < 0 )
    {
      yaw -= Ogre::Math::PI;
    }
    else
    {
      yaw += Ogre::Math::PI;
    }
  }

  pitch_property_->setFloat( pitch );
  yaw_property_->setFloat( mapAngleTo0_2Pi( yaw ));
  position_property_->setVector( source_camera->getPosition() );
}