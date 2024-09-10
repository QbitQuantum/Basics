void 
pcl::getCameraMatrixFromProjectionMatrix (
    const Eigen::Matrix<float, 3, 4, Eigen::RowMajor>& projection_matrix, 
    Eigen::Matrix3f& camera_matrix)
{
  Eigen::Matrix3f KR = projection_matrix.topLeftCorner <3, 3> ();

  Eigen::Matrix3f KR_KRT = KR * KR.transpose ();
  
  Eigen::Matrix3f cam = KR_KRT / KR_KRT.coeff (8);

  memset (&(camera_matrix.coeffRef (0)), 0, sizeof (Eigen::Matrix3f::Scalar) * 9);
  camera_matrix.coeffRef (8) = 1.0;
  
  if (camera_matrix.Flags & Eigen::RowMajorBit)
  {
    camera_matrix.coeffRef (2) = cam.coeff (2);
    camera_matrix.coeffRef (5) = cam.coeff (5);
    camera_matrix.coeffRef (4) = static_cast<float> (std::sqrt (cam.coeff (4) - cam.coeff (5) * cam.coeff (5)));
    camera_matrix.coeffRef (1) = (cam.coeff (1) - cam.coeff (2) * cam.coeff (5)) / camera_matrix.coeff (4);
    camera_matrix.coeffRef (0) = static_cast<float> (std::sqrt (cam.coeff (0) - camera_matrix.coeff (1) * camera_matrix.coeff (1) - cam.coeff (2) * cam.coeff (2)));
  }
  else
  {
    camera_matrix.coeffRef (6) = cam.coeff (2);
    camera_matrix.coeffRef (7) = cam.coeff (5);
    camera_matrix.coeffRef (4) = static_cast<float> (std::sqrt (cam.coeff (4) - cam.coeff (5) * cam.coeff (5)));
    camera_matrix.coeffRef (3) = (cam.coeff (1) - cam.coeff (2) * cam.coeff (5)) / camera_matrix.coeff (4);
    camera_matrix.coeffRef (0) = static_cast<float> (std::sqrt (cam.coeff (0) - camera_matrix.coeff (3) * camera_matrix.coeff (3) - cam.coeff (2) * cam.coeff (2)));
  }
}