  void POVPainter::drawMultiCylinder (const Vector3d &end1, const Vector3d &end2,
                           double radius, int order, double)
  {
    // Just render single bonds with the standard drawCylinder function
    if (order == 1)
    {
      drawCylinder(end1, end2, radius);
      return;
    }

    // Find the bond axis
    Vector3d axis = end2 - end1;
    double axisNorm = axis.norm();
    if( axisNorm < 1.0e-5 ) return;
    Vector3d axisNormalized = axis / axisNorm;

    // Use the plane normal vector for the molecule to draw multicylinders along
    Vector3d ortho1 = axisNormalized.cross(d->planeNormalVector);
    double ortho1Norm = ortho1.norm();
    if( ortho1Norm > 0.001 ) ortho1 /= ortho1Norm;
    else ortho1 = axisNormalized.unitOrthogonal();
    // This number seems to work well for drawing the multiCylinder inside
    ortho1 *= radius*1.5;
    Vector3d ortho2 = axisNormalized.cross(ortho1);
    // Use an angle offset of zero for double bonds, 90 for triple and 22.5 for higher order
    double angleOffset = 0.0;
    if( order >= 3 )
    {
      if( order == 3 ) angleOffset = 90.0;
      else angleOffset = 22.5;
    }
    // Actually draw the cylinders
    for( int i = 0; i < order; i++)
    {
      double alpha = angleOffset / 180.0 * M_PI + 2.0 * M_PI * i / order;
      Vector3d displacement = cos(alpha) * ortho1 + sin(alpha) * ortho2;
      Vector3d displacedEnd1 = end1 + displacement;
      Vector3d displacedEnd2 = end2 + displacement;
      // Write out a POVRay cylinder for rendering
      *(d->output) << "cylinder {\n"
        << "\t<" << displacedEnd1.x() << ", "
                 << displacedEnd1.y() << ", "
                 << displacedEnd1.z() << ">, "
        << "\t<" << displacedEnd2.x() << ", "
                 << displacedEnd2.y() << ", "
                 << displacedEnd2.z() << ">, " << radius
        << "\n\tpigment { rgbt <" << d->color.red() << ", " << d->color.green() << ", "
        << d->color.blue() << ", " << 1.0 - d->color.alpha() << "> }\n}\n";

    }
  }