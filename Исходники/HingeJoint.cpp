// Compute the current angle around the hinge axis
decimal HingeJoint::computeCurrentHingeAngle(const Quaternion& orientationBody1,
                                             const Quaternion& orientationBody2) {

    decimal hingeAngle;

    // Compute the current orientation difference between the two bodies
    Quaternion currentOrientationDiff = orientationBody2 * orientationBody1.getInverse();
    currentOrientationDiff.normalize();

    // Compute the relative rotation considering the initial orientation difference
    Quaternion relativeRotation = currentOrientationDiff * mInitOrientationDifferenceInv;
    relativeRotation.normalize();

    // A quaternion q = [cos(theta/2); sin(theta/2) * rotAxis] where rotAxis is a unit
    // length vector. We can extract cos(theta/2) with q.w and we can extract |sin(theta/2)| with :
    // |sin(theta/2)| = q.getVectorV().length() since rotAxis is unit length. Note that any
    // rotation can be represented by a quaternion q and -q. Therefore, if the relative rotation
    // axis is not pointing in the same direction as the hinge axis, we use the rotation -q which
    // has the same |sin(theta/2)| value but the value cos(theta/2) is sign inverted. Some details
    // about this trick is explained in the source code of OpenTissue (http://www.opentissue.org).
    decimal cosHalfAngle = relativeRotation.w;
    decimal sinHalfAngleAbs = relativeRotation.getVectorV().length();

    // Compute the dot product of the relative rotation axis and the hinge axis
    decimal dotProduct = relativeRotation.getVectorV().dot(mA1);

    // If the relative rotation axis and the hinge axis are pointing the same direction
    if (dotProduct >= decimal(0.0)) {
        hingeAngle = decimal(2.0) * std::atan2(sinHalfAngleAbs, cosHalfAngle);
    }
    else {
        hingeAngle = decimal(2.0) * std::atan2(sinHalfAngleAbs, -cosHalfAngle);
    }

    // Convert the angle from range [-2*pi; 2*pi] into the range [-pi; pi]
    hingeAngle = computeNormalizedAngle(hingeAngle);

    // Compute and return the corresponding angle near one the two limits
    return computeCorrespondingAngleNearLimits(hingeAngle, mLowerLimit, mUpperLimit);
}