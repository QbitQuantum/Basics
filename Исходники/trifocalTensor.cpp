/**
 * @function fillEq_PLL 
 * @brief  Fill PLL equations ( 1 Equation - 1 DOF )
 */
void trifocalTensor::fillEq_PLL( cv::Point3f _A, 
				 cv::Point3f _B,
				 cv::Point3f _C ) {

  Eigen::Vector3f A; A << _A.x, _A.y, _A.z;
  Eigen::Vector3f B; B << _B.x, _B.y, _B.z;
  Eigen::Vector3f C; C << _C.x, _C.y, _C.z;
  std::cout << "PLL Correspondence: " << A.transpose() <<"," <<B.transpose() <<"," <<C.transpose() << std::endl;

    // T0, T1, T2
    for( int i = 0; i < 3; ++i ) {
      for( int j = 0; j < 3; ++j ) {
	for( int k = 0; k < 3; ++k ) {
	    mEq( mPointer, 9*i + 3*j + k) += A(i)*B(j)*C(k);
	} // k
      } // j
    } // i
    mPointer++;

}