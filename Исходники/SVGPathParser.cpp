// This works by converting the SVG arc to "simple" beziers.
// Partly adapted from Niko's code in kdelibs/kdecore/svgicons.
// See also SVG implementation notes: http://www.w3.org/TR/SVG/implnote.html#ArcConversionEndpointToCenter
bool SVGPathParser::decomposeArcToCubic(float angle, float rx, float ry, FloatPoint& point1, FloatPoint& point2, bool largeArcFlag, bool sweepFlag)
{
    FloatSize midPointDistance = point1 - point2;
    midPointDistance.scale(0.5f);

    AffineTransform pointTransform;
    pointTransform.rotate(-angle);

    FloatPoint transformedMidPoint = pointTransform.mapPoint(FloatPoint(midPointDistance.width(), midPointDistance.height()));
    float squareRx = rx * rx;
    float squareRy = ry * ry;
    float squareX = transformedMidPoint.x() * transformedMidPoint.x();
    float squareY = transformedMidPoint.y() * transformedMidPoint.y();

    // Check if the radii are big enough to draw the arc, scale radii if not.
    // http://www.w3.org/TR/SVG/implnote.html#ArcCorrectionOutOfRangeRadii
    float radiiScale = squareX / squareRx + squareY / squareRy;
    if (radiiScale > 1) {
        rx *= sqrtf(radiiScale);
        ry *= sqrtf(radiiScale);
    }

    pointTransform.makeIdentity();
    pointTransform.scale(1 / rx, 1 / ry);
    pointTransform.rotate(-angle);

    point1 = pointTransform.mapPoint(point1);
    point2 = pointTransform.mapPoint(point2);
    FloatSize delta = point2 - point1;

    float d = delta.width() * delta.width() + delta.height() * delta.height();
    float scaleFactorSquared = std::max(1 / d - 0.25f, 0.f);

    float scaleFactor = sqrtf(scaleFactorSquared);
    if (sweepFlag == largeArcFlag)
        scaleFactor = -scaleFactor;

    delta.scale(scaleFactor);
    FloatPoint centerPoint = point1 + point2;
    centerPoint.scale(0.5f, 0.5f);
    centerPoint.move(-delta.height(), delta.width());

    float theta1 = FloatPoint(point1 - centerPoint).slopeAngleRadians();
    float theta2 = FloatPoint(point2 - centerPoint).slopeAngleRadians();

    float thetaArc = theta2 - theta1;
    if (thetaArc < 0 && sweepFlag)
        thetaArc += 2 * piFloat;
    else if (thetaArc > 0 && !sweepFlag)
        thetaArc -= 2 * piFloat;

    pointTransform.makeIdentity();
    pointTransform.rotate(angle);
    pointTransform.scale(rx, ry);

    // Some results of atan2 on some platform implementations are not exact enough. So that we get more
    // cubic curves than expected here. Adding 0.001f reduces the count of sgements to the correct count.
    int segments = ceilf(fabsf(thetaArc / (piOverTwoFloat + 0.001f)));
    for (int i = 0; i < segments; ++i) {
        float startTheta = theta1 + i * thetaArc / segments;
        float endTheta = theta1 + (i + 1) * thetaArc / segments;

        float t = (8 / 6.f) * tanf(0.25f * (endTheta - startTheta));
        if (!std::isfinite(t))
            return false;
        float sinStartTheta = sinf(startTheta);
        float cosStartTheta = cosf(startTheta);
        float sinEndTheta = sinf(endTheta);
        float cosEndTheta = cosf(endTheta);

        point1 = FloatPoint(cosStartTheta - t * sinStartTheta, sinStartTheta + t * cosStartTheta);
        point1.move(centerPoint.x(), centerPoint.y());
        FloatPoint targetPoint = FloatPoint(cosEndTheta, sinEndTheta);
        targetPoint.move(centerPoint.x(), centerPoint.y());
        point2 = targetPoint;
        point2.move(t * sinEndTheta, -t * cosEndTheta);

        m_consumer->curveToCubic(pointTransform.mapPoint(point1), pointTransform.mapPoint(point2),
                                 pointTransform.mapPoint(targetPoint), AbsoluteCoordinates);
    }
    return true;
}