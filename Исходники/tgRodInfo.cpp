btVector3 
tgRodInfo::getConnectionPoint(const btVector3& referencePoint,
                   const btVector3& destinationPoint,
                   const double rotation) const
{
    if (referencePoint == destinationPoint)
    {
      throw 
        std::invalid_argument("Destination point is the reference point.");
    }
    // Find the closest point on the radius from the referencePoint
    const btVector3 cylinderAxis = (getTo() - getFrom()).normalize();
    const btVector3 cylinderAxis2 = (getTo() - getFrom()).normalize();
    // Vector from reference point to destination point
    const btVector3 refToDest =
        (referencePoint - destinationPoint).normalize();

    // Find a vector perpendicular to both the cylinder axis and refToDest
    btVector3 rotationAxis = cylinderAxis.cross(refToDest);
    
    // Handle a vector crossed with itself
    if (rotationAxis.length() == 0.0)
    {
        btScalar a = cylinderAxis[0];
        btScalar b = cylinderAxis[1];
        btScalar c = cylinderAxis[2];
        // Find an arbitrary perpendicular vector
        rotationAxis = btVector3(b - c, -a, a).normalize(); 
    }

    const btVector3 directional =
        cylinderAxis.rotate(rotationAxis, -M_PI / 2.0).normalize();

    // Apply one additional rotation so we can end up anywhere we
    // want on the radius of the rod
    
    // When added to any point along the cylinder axis, this will take you
    // to the surface in the direction of the destinationPoint
    
    const btVector3 surfaceVector = directional.rotate(cylinderAxis2, rotation).normalize()
                                    * m_config.radius;

    // Return the the surface point closest to the reference point in the
    // direction of the destination point. 
    return referencePoint + surfaceVector;
}