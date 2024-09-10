/**
 * @brief hqp_wrapper::addObstacle
 * @param levelName         String to be used as ID
 * @param Jac               Jacobian (6xNc), only the first 3 rows (position) is used currently
 * @param n                 Normalised Vector between end effector and obstacles' position
 * @param b                 scalar b, n*J < b
 */
void hqp_wrapper::addObstacle(std::string levelName, const Eigen::MatrixXd Jac, const Eigen::Vector3d n, double b){
    Eigen::MatrixXd Jtmp;
    Jtmp = n.transpose()*Jac.block(0,0,3,this->NC);
    Eigen::Matrix<double,1,1>  B;
    B(0) = b;
    addStage(levelName,Jtmp,B,soth::Bound::BOUND_INF);
    std::cout <<"Adding new element:" << levelName <<", at:" << leveNameMap[levelName]<<"\n";
}