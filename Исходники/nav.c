/** Navigates around (x, y). Clockwise iff radius > 0 */
void nav_circle_XY(float x, float y, float radius)
{
  struct EnuCoor_f *pos = stateGetPositionEnu_f();
  float last_trigo_qdr = nav_circle_trigo_qdr;
  nav_circle_trigo_qdr = atan2f(pos->y - y, pos->x - x);
  float sign_radius = radius > 0 ? 1 : -1;

  if (nav_in_circle) {
    float trigo_diff = nav_circle_trigo_qdr - last_trigo_qdr;
    NormRadAngle(trigo_diff);
    nav_circle_radians += trigo_diff;
    trigo_diff *= - sign_radius;
    if (trigo_diff > 0) { // do not rewind if the change in angle is in the opposite sense than nav_radius
      nav_circle_radians_no_rewind += trigo_diff;
    }
  }

  float dist2_center = DistanceSquare(pos->x, pos->y, x, y);
  float dist_carrot = CARROT * NOMINAL_AIRSPEED;

  radius += -nav_shift;

  float abs_radius = fabs(radius);

  /** Computes a prebank. Go straight if inside or outside the circle */
  circle_bank =
    (dist2_center > Square(abs_radius + dist_carrot)
     || dist2_center < Square(abs_radius - dist_carrot)) ?
    0 :
    atanf(stateGetHorizontalSpeedNorm_f() * stateGetHorizontalSpeedNorm_f() / (NAV_GRAVITY * radius));

  float carrot_angle = dist_carrot / abs_radius;
  carrot_angle = Min(carrot_angle, M_PI / 4);
  carrot_angle = Max(carrot_angle, M_PI / 16);
  float alpha_carrot = nav_circle_trigo_qdr - sign_radius * carrot_angle;
  horizontal_mode = HORIZONTAL_MODE_CIRCLE;
  float radius_carrot = abs_radius;
  if (nav_mode == NAV_MODE_COURSE) {
    radius_carrot += (abs_radius / cosf(carrot_angle) - abs_radius);
  }
  fly_to_xy(x + cosf(alpha_carrot)*radius_carrot,
            y + sinf(alpha_carrot)*radius_carrot);
  nav_in_circle = true;
  nav_circle_x = x;
  nav_circle_y = y;
  nav_circle_radius = radius;
}