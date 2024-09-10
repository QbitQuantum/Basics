// Solves linear system to extract klm
// P.K = k (similarly for l, m)
// Where P is matrix of control points
// K is coefficients for the line K
// k is vector of values of K evaluated at the control points
// Solving for K, thus K = P^(-1) . k
static void calc_cubic_klm(const SkPoint p[4], const SkScalar controlK[4],
                           const SkScalar controlL[4], const SkScalar controlM[4],
                           SkScalar k[3], SkScalar l[3], SkScalar m[3]) {
    SkMatrix matrix;
    matrix.setAll(p[0].fX, p[0].fY, 1.f,
                  p[1].fX, p[1].fY, 1.f,
                  p[2].fX, p[2].fY, 1.f);
    SkMatrix inverse;
    if (matrix.invert(&inverse)) {
       inverse.mapHomogeneousPoints(k, controlK, 1);
       inverse.mapHomogeneousPoints(l, controlL, 1);
       inverse.mapHomogeneousPoints(m, controlM, 1);
    }

}