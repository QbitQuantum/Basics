/*! Sets the frame, location and normal, but does not do anything with the friction edges.
 */
void VirtualContact::changeFrame(transf tr)
{
  frame = tr;
  loc = position(tr.translation().toSbVec3f());
  normal = vec3(0, 0, 1) * tr;
}