void KickEngineData::calcLegJoints(const JointData::Joint& joint, JointRequest& jointRequest, const RobotDimensions& theRobotDimensions)
{
  float sign = joint == JointData::LHipYawPitch ? 1.f : -1.f;
  float leg0, leg1, leg2, leg3, leg4, leg5;

  const Vector3<>& footPos = (sign > 0) ? positions[Phase::leftFootTra] : positions[Phase::rightFootTra];
  const Vector3<>& footRotAng = (sign > 0) ? positions[Phase::leftFootRot] : positions[Phase::rightFootRot];

  RotationMatrix rotateBodyTilt = RotationMatrix().rotateX(comOffset.x);
  Vector3<> anklePos = rotateBodyTilt * Vector3<>(footPos.x, footPos.y, footPos.z);
  //we need just the leg length x and y have to stay the same
  anklePos.y = footPos.y;
  anklePos.x = footPos.x;
  // for the translation of the footpos we only need to translate the anklepoint, which is the intersection of the axis leg4 and leg5
  // the rotation of the foot will be made later by rotating the footpos around the anklepoint
  anklePos -= Vector3<>(0.f, sign * (theRobotDimensions.lengthBetweenLegs / 2), -theRobotDimensions.heightLeg5Joint);

  RotationMatrix rotateBecauseOfHip = RotationMatrix().rotateZ(footRotAng.z).rotateX(-sign * pi_4);

  anklePos = rotateBecauseOfHip * anklePos;

  float diagonal = anklePos.abs();

  // upperLegLength, lowerLegLength, and diagonal form a triangle, use cosine theorem
  float a1 = (theRobotDimensions.upperLegLength * theRobotDimensions.upperLegLength -
              theRobotDimensions.lowerLegLength * theRobotDimensions.lowerLegLength + diagonal * diagonal) /
             (2 * theRobotDimensions.upperLegLength * diagonal);
  //if(abs(a1) > 1.f) OUTPUT(idText, text, "clipped a1");
  a1 = abs(a1) > 1.f ? 0.f : acos(a1);

  float a2 = (theRobotDimensions.upperLegLength * theRobotDimensions.upperLegLength +
              theRobotDimensions.lowerLegLength * theRobotDimensions.lowerLegLength - diagonal * diagonal) /
             (2 * theRobotDimensions.upperLegLength * theRobotDimensions.lowerLegLength);
  //if(abs(a2) > 1.f) OUTPUT(idText, text, "clipped a2");
  a2 = abs(a2) > 1.f ? pi : acos(a2);

  leg0 = footRotAng.z * sign;
  leg2 = -a1 - atan2(anklePos.x, Vector2<>(anklePos.y, anklePos.z).abs() * -sgn(anklePos.z));

  leg1 = anklePos.z == 0.0f ? 0.0f : atan(anklePos.y / -anklePos.z) * -sign;
  leg3 = pi - a2;

  RotationMatrix footRot = RotationMatrix().rotateX(leg1 * -sign).rotateY(leg2 + leg3);
  footRot = footRot.invert() * rotateBecauseOfHip;

  leg5 = asin(-footRot[2].y) * sign * -1;
  leg4 = -atan2(footRot[2].x, footRot[2].z) * -1;

  leg4 += footRotAng.y;
  leg5 += footRotAng.x;

  jointRequest.angles[joint] = leg0;
  jointRequest.angles[joint + 1] = -pi_4 + leg1;
  jointRequest.angles[joint + 2] = leg2;
  jointRequest.angles[joint + 3] = leg3;
  jointRequest.angles[joint + 4] = leg4;
  jointRequest.angles[joint + 5] = leg5;
}