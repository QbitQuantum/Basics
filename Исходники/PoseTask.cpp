// TODO: eigen ref????
void PoseTask::getJacobian(const Eigen::VectorXd& q, 
                           Eigen::MatrixXd& Jacobian)
{
  // TODO: Check that the Jacobian is initially set to zero
  if (taskType_ == 0){
    //Jacobian.setZero();
    Jacobian.resize(3,ndof_);
    Jacobian.setZero(); // VERY IMPORTANT FOR THE JACOBIAN!!!
    //CalcPointJacobian(*model_, q, linkNum_, localpos_, Jacobian, false);
    CalcPointJacobian(*model_, q, linkNum_, localpos_, Jacobian, true);
    // std::cout << "qdes" << q.transpose() << std::endl;
    // std::cout << "rwrist: " << linkNum_ << std::endl;
    // std::cout << "localpos: " << localpos_.transpose() << std::endl;
  }
  else if (taskType_ == 1)
    std::cout << "TODO" << std::endl;
  else if (taskType_ == 2)
    std::cout << "TODO" << std::endl;
  // TODO: Use CalcBodySpatialJacobian for the orientation
}