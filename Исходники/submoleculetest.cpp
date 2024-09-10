void SubMoleculeTest::rotate()
{
  SubMolecule *sub = m_source_h2o->getRandomSubMolecule();

  // Rotate into xy-plane: Align the cross product of the bond vectors
  // with the z-axis
  Q_ASSERT(sub->numBonds() == 2);
  const Eigen::Vector3d b1= *sub->bond(0)->beginPos()-*sub->bond(0)->endPos();
  const Eigen::Vector3d b2= *sub->bond(1)->beginPos()-*sub->bond(1)->endPos();
  const Eigen::Vector3d cross = b1.cross(b2).normalized();

  // Axis is the cross-product of cross with zhat:
  const Eigen::Vector3d axis = cross.cross(Eigen::Vector3d::UnitZ()).normalized();

  // Angle is the angle between cross and jhat:
  const double angle = acos(cross.dot(Eigen::Vector3d::UnitZ()));

  // Rotate the submolecule
  sub->rotate(angle, axis);

  // Verify that the molecule is in the xy-plane
  QVERIFY(fabs(sub->atom(0)->pos()->z()) < 1e-2);
  QVERIFY(fabs(sub->atom(1)->pos()->z()) < 1e-2);
  QVERIFY(fabs(sub->atom(2)->pos()->z()) < 1e-2);
  delete sub;
}