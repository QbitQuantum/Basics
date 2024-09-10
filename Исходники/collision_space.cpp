//! The distance potential and the gradient is computed for a collision point
//! First the distance d of the collision point (sphere) to the closest
// obstacle
// is computed
//! Then 3 cases apear to compute the potential
//! - 0 if this distance is greater than the coll point clearance
//! -
bool CollisionSpace::getCollisionPointPotentialGradient(
    const CollisionPoint& collision_point,
    const Eigen::Vector3d& collision_point_pos,
    double& field_distance,
    double& potential,
    Eigen::Vector3d& gradient) const {
  Eigen::Vector3d field_gradient;

  // Compute the distance gradient and distance to nearest obstacle
  field_distance =
      this->getDistanceGradient(collision_point_pos, field_gradient);

  double d = field_distance - collision_point.getRadius();

  // three cases below:
  if (d >= collision_point.getClearance()) {
    potential = 0.0;
    gradient.setZero();
  } else if (d >= 0.0) {
    double diff = (d - collision_point.getClearance());
    potential = 0.5 * collision_point.getInvClearance() * diff * diff;
    gradient = diff * collision_point.getInvClearance() * field_gradient;
  } else  // if d < 0.0
  {
    gradient = field_gradient;
    double offset = 0.5 * collision_point.getClearance();
    potential = -d * 10 + offset;
    // potential = -d + 0.5 * collision_point.getClearance();
  }

  //    cout << "field_distance : " << field_distance
  // << ", radius : "  << collision_point.getRadius() << endl;

  // true if point is in collision
  return (field_distance <= collision_point.getRadius());
}