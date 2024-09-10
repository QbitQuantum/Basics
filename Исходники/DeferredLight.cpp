bool DeferredLight::isCameraInsideLight(Ogre::Camera* camera) {
    switch (parentLight->getType()) {
        case Ogre::Light::LT_DIRECTIONAL:
            return false;
        case Ogre::Light::LT_POINT: {
            Ogre::Real distanceFromLight =
                camera->getDerivedPosition().distance(parentLight->getDerivedPosition());

            // Small epsilon fix to account for the fact that we aren't a true sphere.
            return distanceFromLight <= radius + camera->getNearClipDistance() + 0.1;
        }
        case Ogre::Light::LT_SPOTLIGHT: {
            Ogre::Vector3 lightPos = parentLight->getDerivedPosition();
            Ogre::Vector3 lightDir = parentLight->getDerivedDirection();
            Ogre::Radian attAngle = parentLight->getSpotlightOuterAngle();

            // Extend the analytic cone's radius by the near clip range by moving its tip accordingly.
            Ogre::Vector3 clipRangeFix = -lightDir * (camera->getNearClipDistance() / Ogre::Math::Tan(attAngle/2));
            lightPos = lightPos + clipRangeFix;

            Ogre::Vector3 lightToCamDir = camera->getDerivedPosition() - lightPos;
            Ogre::Real distanceFromLight = lightToCamDir.normalise();

            Ogre::Real cosAngle = lightToCamDir.dotProduct(lightDir);
            Ogre::Radian angle = Ogre::Math::ACos(cosAngle);

            // Check whether we will see the cone from our current POV.
            return (distanceFromLight <= (parentLight->getAttenuationRange() + clipRangeFix.length()))
                   && (angle <= attAngle);
        }
        default:
            return false;
    }
}