//
//  This one works for planes that are explicitly parallel to the z
//  axis and are bounded in the z direction.
//  This time we get ourselves a square at zMin and search that
//  for our intersections.
//
int FieldView::ViewPlane(Point3D& p, double theta, double zMin, double zMax)
{
  const double degree = 3.141592653589 / 180.0;
  //
  //  We know <0,0,1> lies in the plane, figure out what else
  //  does from the angle.
  //
  Vector3D norm(cos(theta * degree), sin(theta * degree), 0.0);
  const Real* min = mField->GetBounds()->GetMin().mCoords;
  const Real* max = mField->GetBounds()->GetMax().mCoords;
  Point3D corner[4];
  for (int i = 0; i < 4; i++) {
    corner[i].mCoords[0] = (((i/2)&1)==0) ? min[0] : max[0];
    corner[i].mCoords[1] = ((((i+1)/2)&1)==0) ? min[1] : max[1];
    corner[i].mCoords[2] = zMin;
  }
  int nIntersection = 0;
  Point3D frameCorner[4];
  for (int edge = 0; edge < 4; edge++) {
    if (Intersect(p, norm,
                  corner[edge], corner[(edge+1)%4],
                  frameCorner[nIntersection])) {
      bool used = false;
      for (int e = 0; e < nIntersection; e++) {
        if (frameCorner[nIntersection] == frameCorner[e]) {
          used = true;
        }
      }
      if (!used) {
        nIntersection++;
        if (nIntersection >= 2) break;
      }
    }
  }
  if (nIntersection != 2) {
    return -1;        // MUST have two intersections.
  }
  //
  //  Right, we have two intersections. They are on the min side in the
  //  dir direction. The other two intersections are on the max side
  //  so we make them from these two. The order is chosen carefully
  //  to make corners adjacent.
  //
  frameCorner[2] = frameCorner[1];
  frameCorner[2].mCoords[2] = zMax;
  frameCorner[3] = frameCorner[0];
  frameCorner[3].mCoords[2] = zMax;
  //
  //  Now we can construct the FrameRect3D representing the intersection.
  //
  mFrame = new FrameRect3D(frameCorner);
  if (mFrame->IsValid()) {
    mValid = true;
  }
  //
  //  Then we can construct the legend. It sits in the same plane as
  //  the mFrame but is thinner and translated by 10% of the mFrame width.
  //
  Vector3D horiz = mFrame->GetHorizontal();
  horiz.Normalize();
  double displacement = mFrame->GetWidth() * 0.1;
  double legendWidth = displacement * 1.3; // 3% of frame
  frameCorner[0] = frameCorner[1] + horiz * displacement;
  frameCorner[1] = frameCorner[0] + horiz * legendWidth;
  frameCorner[3] = frameCorner[2] + horiz * displacement;
  frameCorner[2] = frameCorner[3] + horiz * legendWidth;
  mLegendFrame = new FrameRect3D(frameCorner);
  return 0;
}