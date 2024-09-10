 BOOST_FOREACH(const Point3Pair& pair, pairs) {
   Vector3 dp = pair.first.vector() - cp;
   Vector3 dq = pair.second.vector() - cq;
   H += dp * dq.transpose();
 }