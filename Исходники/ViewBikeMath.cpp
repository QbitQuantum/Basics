bool ViewBikeMath::calcLegJoints(const Vector3<>& footPos, const Vector3<>& footRotAng, const bool& left, const RobotDimensions& robotDimensions, float& leg0, float& leg1, float& leg2, float& leg3, float& leg4, float& leg5)
{
  float sign = (left) ? 1.f : -1.f;
  bool legTooShort = false;

  Vector3<> anklePos; //FLOAT
  anklePos = Vector3<>(footPos.x,  footPos.y, footPos.z + robotDimensions.heightLeg5Joint);

  anklePos -= Vector3<>(0.f, sign * (robotDimensions.lengthBetweenLegs / 2.f), 0.f);

  RotationMatrix rotateBecauseOfHip = RotationMatrix().rotateZ(sign * footRotAng.z).rotateX(-sign * pi_4);
  Vector3<> rotatedFootRotAng;


  anklePos = rotateBecauseOfHip * anklePos;
  leg0 = footRotAng.z;
  rotatedFootRotAng = rotateBecauseOfHip * footRotAng;

  leg2 = -std::atan2(anklePos.x, Vector2<>(anklePos.y, anklePos.z).abs());

  float diagonal = anklePos.abs();

  // upperLegLength, lowerLegLength, and diagonal form a triangle, use cosine theorem
  float a1 = (robotDimensions.upperLegLength * robotDimensions.upperLegLength -
              robotDimensions.lowerLegLength * robotDimensions.lowerLegLength + diagonal * diagonal) /
             (2 * robotDimensions.upperLegLength * diagonal);
  a1 = std::abs(a1) > 1.f ? 0 : std::acos(a1);

  float a2 = (robotDimensions.upperLegLength * robotDimensions.upperLegLength +
              robotDimensions.lowerLegLength * robotDimensions.lowerLegLength - diagonal * diagonal) /
             (2 * robotDimensions.upperLegLength * robotDimensions.lowerLegLength);
  const Range<float> clipping(-1.f, 1.f);
  if(!clipping.isInside(a2))
  {
    legTooShort = true;
  }
  a2 = std::abs(a2) > 1.f ? pi : std::acos(a2);

  leg1 = (-sign * std::atan2(anklePos.y, std::abs(anklePos.z))) - (pi / 4);
  leg2 -= a1;
  leg3 = pi - a2;

  RotationMatrix footRot = RotationMatrix().rotateX(leg1 * -sign).rotateY(leg2 + leg3);
  footRot = footRot.invert() * rotateBecauseOfHip;
  leg5 = std::asin(-footRot[2].y) * -sign;
  leg4 = -std::atan2(footRot[2].x, footRot[2].z) * -1;
  leg4 += footRotAng.y;
  leg5 += footRotAng.x;

  return legTooShort;
}