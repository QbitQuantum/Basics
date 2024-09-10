bool KFD_PosVelAcc::positionObservation(Eigen::Vector3d position, Eigen::Matrix3d covariance, float reject_position_threshol)
{
  
      Eigen::Vector3d  position_diference = position_world - position; 

      Eigen::Matrix<double, _POS_MEASUREMENT_SIZE, StatePosVelAcc::SIZE> H; 
      H.setZero(); 
      H.block<3,3>(0,0) = Eigen::Matrix3d::Identity(); 
      
      //position_world = position;
      bool reject =  filter->correctionChiSquare<_POS_MEASUREMENT_SIZE,_POS_DEGREE_OF_FREEDOM>( position_diference,  covariance,H, reject_position_threshol );
      
      x.vector() = filter->x;
      
       correct_state();
      
      return reject; 
      
}