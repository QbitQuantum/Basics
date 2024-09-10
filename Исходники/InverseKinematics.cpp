bool InverseKinematics::calcLegJoints(const Pose3D& position, Joints jointAngles, bool left, const RobotDimensions& robotDimensions) {
  Pose3D target(position);
  Joint firstJoint(left ? LHipYawPitch : RHipYawPitch);
  int sign(left ? -1 : 1);
  target.translation.y += (float) robotDimensions.values_[RobotDimensions::lengthBetweenLegs] / 2.f * sign; // translate to origin of leg
  // rotate by 45° around origin for Nao
  // calculating sqrtf(2) is faster than calculating the resp. rotation matrix with getRotationX()
  static const float sqrt2_2 = sqrtf(2.0f) * 0.5f;
  RotationMatrix rotationX_pi_4 = RotationMatrix(Vector3<float>(1, 0, 0), Vector3<float>(0, sqrt2_2, sqrt2_2 * sign), Vector3<float>(0, sqrt2_2 * -sign, sqrt2_2));
  target.translation = rotationX_pi_4 * target.translation;
  target.rotation = rotationX_pi_4 * target.rotation;

  target = target.invert(); // invert pose to get position of body relative to foot

  // use geometrical solution to compute last three joints
  float length = target.translation.abs();
  float sqrLength = length * length;
  float upperLeg = robotDimensions.values_[RobotDimensions::upperLegLength];
  float sqrUpperLeg = upperLeg * upperLeg;
  float lowerLeg = robotDimensions.values_[RobotDimensions::lowerLegLength];
  float sqrLowerLeg = lowerLeg * lowerLeg;
  float cosLowerLeg = (sqrLowerLeg + sqrLength - sqrUpperLeg) / (2 * lowerLeg * length);
  float cosKnee = (sqrUpperLeg + sqrLowerLeg - sqrLength) / (2 * upperLeg * lowerLeg);

  // clip for the case of unreachable position
  const Range<float> clipping(-1.0f, 1.0f);
  bool reachable = true;
  if(!clipping.isInside(cosKnee) || clipping.isInside(cosLowerLeg))
  {
    cosKnee = clipping.limit(cosKnee);
    cosLowerLeg = clipping.limit(cosLowerLeg);
    reachable = false;
  }
  float joint3 = M_PI - acosf(cosKnee); // implicitly solve discrete ambiguousness (knee always moves forward)
  float joint4 = -acosf(cosLowerLeg);
  joint4 -= atan2f(target.translation.x, Vector2<float>(target.translation.y, target.translation.z).abs());
  float joint5 = atan2f(target.translation.y, target.translation.z) * sign;

  // calulate rotation matrix before hip joints
  RotationMatrix hipFromFoot;
  hipFromFoot.rotateX(joint5 * -sign);
  hipFromFoot.rotateY(-joint4 - joint3);

  // compute rotation matrix for hip from rotation before hip and desired rotation
  RotationMatrix hip = hipFromFoot.invert() * target.rotation;

  // compute joints from rotation matrix using theorem of euler angles
  // see http://www.geometrictools.com/Documentation/EulerAngles.pdf
  // this is possible because of the known order of joints (z, x, y seen from body resp. y, x, z seen from foot)
  float joint1 = asinf(-hip[2].y) * -sign;
  joint1 -= M_PI_4; // because of the 45°-rotational construction of the Nao legs
  float joint2 = -atan2f(hip[2].x, hip[2].z);
  float joint0 = atan2f(hip[0].y, hip[1].y) * -sign;

  // set computed joints in jointAngles
  jointAngles[firstJoint + 0] = joint0;
  jointAngles[firstJoint + 1] = joint1;
  jointAngles[firstJoint + 2] = joint2;
  jointAngles[firstJoint + 3] = joint3;
  jointAngles[firstJoint + 4] = joint4;
  jointAngles[firstJoint + 5] = joint5;

  return reachable;
}