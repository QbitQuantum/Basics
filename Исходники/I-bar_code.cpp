/*
 * Given a vector of points (p_vec), find the interpolated value
 * with the passed-in u_vec and B matrix.
 *
 * Equivalent to evaluating
 * f(u) = uBp
 * at some u.
 */
float interpolate_points(Vector4f u_vec, MatrixXf B, Vector4f p_vec) {
    float interpolated = u_vec.dot(B * p_vec);
    return interpolated;
}