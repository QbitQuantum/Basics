/*
 * Given the line parameters  [n_x,n_y,a_x,a_y] check if
 * [n_x, n_y] dot [data.x-a_x, data.y-a_y] < m_delta
 */
bool RSTEstimator::agree(std::vector<double> &parameters, std::pair<Eigen::Vector3d,Eigen::Vector3d> &data)
{
	
	Eigen::Matrix3d R;
	Eigen::Vector3d T;
	Eigen::Vector3d dif;
	double  E1,E2;
	
	
	R << parameters[0] , parameters[1] , parameters[2],
	     parameters[3] , parameters[4] , parameters[5],
	     parameters[6] , parameters[7] , parameters[8];
	
	T << parameters[9] , parameters[10] , parameters[11];
	

    dif = data.first - R*data.second + T; //X21
	E1 = dif.transpose()*dif;
	
	dif = data.second - R.inverse() * (data.first-T); //X12
	E2 = dif.transpose()*dif;
	
	//std::cout << "E1= " << E1 << "\nE2= " << E2 << "\nE1+E2= "<< E1+E2 << " " << this->deltaSquared <<"\n";
	
	return ( (E1 + E2) < this->deltaSquared);
}