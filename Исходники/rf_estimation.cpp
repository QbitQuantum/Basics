Math::Matrix<float> ResponseEstimator::gen_rotation_matrix (const Point<float>& dir) const
{
  // Generates a matrix that will rotate a unit vector into a new frame of reference,
  //   where the peak direction of the FOD is aligned in Z (3rd dimension)
  // Previously this was done using the tensor eigenvectors
  // Here the other two axes are determined at random (but both are orthogonal to the FOD peak direction)
  Math::Matrix<float> R (3, 3);
  R (2, 0) = dir[0]; R (2, 1) = dir[1]; R (2, 2) = dir[2];
  Point<float> vec2 (rng(), rng(), rng());
  vec2 = dir.cross (vec2);
  vec2.normalise();
  R (0, 0) = vec2[0]; R (0, 1) = vec2[1]; R (0, 2) = vec2[2];
  const Point<float> vec3 ((dir.cross (vec2)).normalise());
  R (1, 0) = vec3[0]; R (1, 1) = vec3[1]; R (1, 2) = vec3[2];
  return R;
}