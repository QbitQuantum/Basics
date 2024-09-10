/**
 * graphene_quaternion_to_angles:
 * @q: a #graphene_quaternion_t
 * @deg_x: (out) (optional): return location for the rotation angle on
 *   the X axis (yaw), in degress
 * @deg_y: (out) (optional): return location for the rotation angle on
 *   the Y axis (pitch), in degrees
 * @deg_z: (out) (optional): return location for the rotation angle on
 *   the Z axis (roll), in degrees
 *
 * Converts a #graphene_quaternion_t to its corresponding rotations
 * on the [Euler angles](http://en.wikipedia.org/wiki/Euler_angles)
 * on each axis.
 *
 * Since: 1.2
 */
void
graphene_quaternion_to_angles (const graphene_quaternion_t *q,
                               float                       *deg_x,
                               float                       *deg_y,
                               float                       *deg_z)
{
  graphene_vec4_t v;
  graphene_vec4_t sq;
  float qx, qy, qz, qw, sqx, sqy, sqz, sqw;

  graphene_quaternion_to_vec4 (q, &v);
  graphene_vec4_multiply (&v, &v, &sq);

  qx = graphene_vec4_get_x (&v);
  qy = graphene_vec4_get_y (&v);
  qz = graphene_vec4_get_z (&v);
  qw = graphene_vec4_get_w (&v);

  sqx = graphene_vec4_get_x (&sq);
  sqy = graphene_vec4_get_y (&sq);
  sqz = graphene_vec4_get_z (&sq);
  sqw = graphene_vec4_get_w (&sq);

  if (deg_x != NULL)
    {
      float res = atan2f (2 * (qx * qw - qy * qz), (sqw - sqx - sqy + sqz));

      *deg_x = GRAPHENE_RAD_TO_DEG (res);
    }

  if (deg_y != NULL)
    {
      float res = asinf (CLAMP (2 * ( qx * qz + qy * qw), -1, 1));

      *deg_y = GRAPHENE_RAD_TO_DEG (res);
    }

  if (deg_z != NULL)
    {
      float res = atan2f (2 * (qz * qw - qx * qy), (sqw + sqx - sqy - sqz));

      *deg_z = GRAPHENE_RAD_TO_DEG (res);
    }
}