int testPointPair(PointPair point, double distance, Vector3d normal, ElementId idA, ElementId idB, Vector3d ptA, Vector3d ptB)
{
  if (point.getDistance() != distance) {
    cerr << "Wrong distance:" << endl;
    cerr << "  Expected " << distance << ", got " << point.getDistance() << endl;
    return 1;
  }
  if (point.getNormal() != normal) {
    cerr << "  Expected " << normal.transpose() << ", got " << point.getNormal().transpose() << endl;
    cerr << "Wrong normal:" << endl;
    return 1;
  }
  if (point.getIdA() != idA) {
    cerr << "Wrong idA:" << endl;
    cerr << "  Expected " << idA << ", got " << point.getIdA() << endl;
    return 1;
  }
  if (point.getIdB() != idB) {
    cerr << "Wrong idB:" << endl;
    cerr << "  Expected " << idB << ", got " << point.getIdB() << endl;
    return 1;
  }
  if (!(point.getPtA()- ptA).isZero()) {
    cerr << "Wrong ptA:" << endl;
    cerr << "  Expected " << ptA.transpose() << ", got " << point.getPtA().transpose() << endl;
    return 1;
  }
  if (!(point.getPtB()- ptB).isZero()) {
    cerr << "Wrong ptB:" << endl;
    cerr << "  Expected " << ptB.transpose() << ", got " << point.getPtB().transpose() << endl;
    return 1;
  }
  return 0;
}