// Generates all necessary inputs and expected outputs for EuclideanResection.
void CreateCameraSystem(const Mat3& KK,
                        const Mat3X& x_image,
                        const Vec& X_distances,
                        const Mat3& R_input,
                        const Vec3& T_input,
                        Mat2X *x_camera,
                        Mat3X *X_world,
                        Mat3  *R_expected,
                        Vec3  *T_expected) {
  int num_points = x_image.cols();

  Mat3X x_unit_cam(3, num_points);
  x_unit_cam = KK.inverse() * x_image;

  // Create normalized camera coordinates to be used as an input to the PnP
  // function, instead of using NormalizeColumnVectors(&x_unit_cam).
  *x_camera = x_unit_cam.block(0, 0, 2, num_points);
  for (int i = 0; i < num_points; ++i){
    x_unit_cam.col(i).normalize();
  }

  // Create the 3D points in the camera system.
  Mat X_camera(3, num_points);
  for (int i = 0; i < num_points; ++i) {
    X_camera.col(i) = X_distances(i) * x_unit_cam.col(i);
  }

  // Apply the transformation to the camera 3D points
  Mat translation_matrix(3, num_points);
  translation_matrix.row(0).setConstant(T_input(0));
  translation_matrix.row(1).setConstant(T_input(1));
  translation_matrix.row(2).setConstant(T_input(2));

  *X_world = R_input * X_camera + translation_matrix;

  // Create the expected result for comparison.
  *R_expected = R_input.transpose();
  *T_expected = *R_expected * ( - T_input);
};