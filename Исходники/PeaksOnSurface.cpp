bool lineIntersectsSphere(const V3D &line, const V3D &lineStart,
                          const V3D &peakCenter, const double peakRadius) {
  V3D peakToStart = peakCenter - lineStart;
  V3D unitLine = line;
  unitLine.normalize();
  double proj = peakToStart.scalar_prod(unitLine); // All we are doing here is
                                                   // projecting the peak to
                                                   // segment start vector onto
                                                   // the segment itself.

  V3D closestPointOnSegment;
  if (proj <= 0) // The projection is outside the segment. So use the start
                 // point of the segment.
  {
    closestPointOnSegment = lineStart; // Start of line
  } else if (proj >= line.norm()) // The projection is greater than the segment
                                  // length. So use the end point of the
                                  // segment.
  {
    closestPointOnSegment = lineStart + line; // End of line.
  } else // The projection falls somewhere between the start and end of the line
         // segment.
  {
    V3D projectionVector = unitLine * proj;
    closestPointOnSegment = projectionVector + lineStart;
  }

  return (peakCenter - closestPointOnSegment).norm() <= peakRadius;
}