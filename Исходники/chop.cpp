/**
 * @name angle_change
 *
 * Return the change in angle (degrees) of the line segments between
 * points one and two, and two and three.
 */
int Wordrec::angle_change(EDGEPT *point1, EDGEPT *point2, EDGEPT *point3) {
  VECTOR vector1;
  VECTOR vector2;

  int angle;

  /* Compute angle */
  vector1.x = point2->pos.x - point1->pos.x;
  vector1.y = point2->pos.y - point1->pos.y;
  vector2.x = point3->pos.x - point2->pos.x;
  vector2.y = point3->pos.y - point2->pos.y;
  /* Use cross product */
  float length = std::sqrt(static_cast<float>(LENGTH(vector1)) * LENGTH(vector2));
  if (static_cast<int>(length) == 0)
    return (0);
  angle = static_cast<int>(floor(asin(CROSS (vector1, vector2) /
                                      length) / M_PI * 180.0 + 0.5));

  /* Use dot product */
  if (SCALAR (vector1, vector2) < 0)
    angle = 180 - angle;
  /* Adjust angle */
  if (angle > 180)
    angle -= 360;
  if (angle <= -180)
    angle += 360;
  return (angle);
}