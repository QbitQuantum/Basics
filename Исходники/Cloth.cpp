/**
 * Code available for download at http://cg.alexandra.dk/?p=147 used as reference for addWindForce
 */
void Cloth::addWindForce(Particle& p1, Particle& p2, Particle& p3) {
  XMVECTOR pos1, pos2, pos3, temp1, temp2, normal, force;

  pos1 = p1.getPosition();
  pos2 = p2.getPosition();
  pos3 = p3.getPosition();

  temp1 = XMVectorSubtract(pos2, pos1);
  temp2 = XMVectorSubtract(pos3, pos1);

  normal = XMVector3Cross(temp1, temp2);
  temp1 = XMVector3Normalize(normal);

  force = XMVectorScale(normal, XMVectorScale(XMVector3Dot(temp1, windDirection), windConstant).m128_f32[0]);

  p1.addForce(force);
  p2.addForce(force);
  p3.addForce(force);
}