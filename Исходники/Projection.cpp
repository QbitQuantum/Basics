void EuclideanToNormalizedCamera(const Mat2X &x, const Mat3 &K, Mat2X *n) {
  Mat3X x_image_h;
  EuclideanToHomogeneous(x, &x_image_h);
  Mat3X x_camera_h = K.inverse() * x_image_h;
  HomogeneousToEuclidean(x_camera_h, n);
}