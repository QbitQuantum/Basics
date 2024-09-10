/**
 * Determines wither point is on the surface.
 * @param point :: Point to check
 * @returns true if the point is on the surface
 */
bool MeshObject::isOnSide(const Kernel::V3D &point) const {

  BoundingBox bb = getBoundingBox();
  if (!bb.isPointInside(point)) {
    return false;
  }

  const std::vector<Kernel::V3D> directions = {
      Kernel::V3D{0, 0, 1}, Kernel::V3D{0, 1, 0},
      Kernel::V3D{1, 0, 0}}; // directions to look for intersections
  // We have to look in several directions in case a point is on a face
  // or edge parallel to the first direction or also the second direction.
  for (const auto &direction : directions) {
    std::vector<Kernel::V3D> intersectionPoints;
    std::vector<TrackDirection> entryExitFlags;

    getIntersections(point, direction, intersectionPoints, entryExitFlags);

    if (intersectionPoints.empty()) {
      return false;
    }

    for (const auto &intersectionPoint : intersectionPoints) {
      if (point.distance(intersectionPoint) < M_TOLERANCE) {
        return true;
      }
    }
  }
  return false;
}