gsl_vector* VelStereoMatcher::stereoToVec(const StereoProperties stereo)
{
  Eigen::Affine3f tform = stereo.getLeftCamera().tform;
  Eigen::Matrix4f intrinsics = stereo.getLeftCamera().intrinsics.matrix();

  Eigen::Vector3f tran;
  tran = tform.translation();
  float x = tran[0];
  float y = tran[1];
  float z = tran[2];

  Eigen::Matrix3f mat = tform.rotation();
  Eigen::AngleAxisf axis;
  axis = mat;
  float ax = axis.axis()[0] * axis.angle();
  float ay = axis.axis()[1] * axis.angle();
  float az = axis.axis()[2] * axis.angle();

  float fx = intrinsics(0,0);
  float fy = intrinsics(1,1);
  float cx = intrinsics(0,2);
  float cy = intrinsics(1,2);

  float baseline = stereo.baseline;

  gsl_vector* vec = gsl_vector_alloc(11);
  gsl_vector_set(vec, 0, x);
  gsl_vector_set(vec, 1, y);
  gsl_vector_set(vec, 2, z);
  gsl_vector_set(vec, 3, ax);
  gsl_vector_set(vec, 4, ay);
  gsl_vector_set(vec, 5, az);

  gsl_vector_set(vec, 6, fx);
  gsl_vector_set(vec, 7, fy);
  gsl_vector_set(vec, 8, cx);
  gsl_vector_set(vec, 9, cy);
  gsl_vector_set(vec, 10, baseline);

  return vec;

}