Eigen::Vector3d CalibrateData::calibrate(Eigen::Vector3d data,
                                         Eigen::Matrix3d alignment_matrix,
                                         Eigen::Matrix3d sensitivity_matrix,
                                         Eigen::Vector3d offset_vector)
{
  Eigen::Vector3d calibrated_data;
  calibrated_data = alignment_matrix.inverse() *
      sensitivity_matrix.inverse() *
      (data - offset_vector);
  return calibrated_data;
}