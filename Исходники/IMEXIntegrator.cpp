void static calcRotEqs(const Rod& r, const VecXe& rot, const std::vector<Vec3e>& curveBinorm,
                      VecXe& grad, std::vector<Triplet>& triplets) {
  Eigen::Matrix<real, 2, 2> J;
  J << 0.0, -1.0, 1.0, 0.0;
  for (int i=1; i<r.numEdges()-1; i++) {
    Vec3e m1 = cos(rot(i)) * r.next().u[i] + sin(rot(i)) * r.next().v(i);
    Vec3e m2 = -sin(rot(i)) * r.next().u[i] + cos(rot(i)) * r.next().v(i);
    Vec2e curvePrev(curveBinorm[i-1].dot(m2), -curveBinorm[i-1].dot(m1)); // omega ^i _i
    Vec2e curveNext(curveBinorm[i].dot(m2), -curveBinorm[i].dot(m1)); // omega ^i _i+1
    real dWprev = 1.0 / r.restVoronoiLength(i) *
      curvePrev.dot(J * r.getCS()[i].bendMat() * (curvePrev - r.restCurveNext(i)));
    real dWnext = 1.0 / r.restVoronoiLength(i+1) *
      curveNext.dot(J * r.getCS()[i+1].bendMat() * (curveNext - r.restCurvePrev(i+1)));
    real twistPrev = rot(i) - rot(i-1) + r.next().refTwist(i);
    real twistNext = rot(i+1) - rot(i) + r.next().refTwist(i+1);
    grad(i-1) = -(dWprev + dWnext + 2.0 * r.getCS()[i].twistCoeff() *
                  (twistPrev/r.restVoronoiLength(i) - twistNext/r.restVoronoiLength(i+1)));
    
    real hess = 2.0*(r.getCS()[i].twistCoeff()/r.restVoronoiLength(i) +
                     r.getCS()[i+1].twistCoeff()/r.restVoronoiLength(i+1));
    hess += 1.0 / r.restVoronoiLength(i) *
      (curvePrev.dot(J.transpose() * r.getCS()[i].bendMat() * J * curvePrev)
       - curvePrev.dot(r.getCS()[i].bendMat() * (curvePrev - r.restCurveNext(i))));
    hess += 1.0 /r.restVoronoiLength(i+1) *
      (curveNext.dot(J.transpose() * r.getCS()[i+1].bendMat() * J * curveNext)
       - curveNext.dot(r.getCS()[i+1].bendMat() * (curveNext - r.restCurvePrev(i+1))));
    triplets.push_back(Triplet(i-1, i-1, hess));
  }
}