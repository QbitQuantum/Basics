MatrixXd compute_empirical_T3(SparseMatrix<double> whitened_data, VectorXd y_mean){
	int nx = (int)whitened_data.cols();
	//printf("nx = %d\n", nx);
	double shift12 = (alpha0 + 1.0)*(alpha0 + 2.0) / (2.0*(double)nx);
	double shift01 = -alpha0 *(alpha0 + 1.0) / (2.0*(double)nx);
	double shift00 = alpha0*alpha0;

	MatrixXd emp_T3_whitened = MatrixXd::Zero(KHID, KHID * KHID);
	for(int n=0; n<nx; n++){
		VectorXd y = whitened_data.col(n);
		
		MatrixXd temp0, temp1, temp2, temp3, temp4;
		temp0.noalias() = shift12 * (y * y.transpose());
		temp1.noalias() = shift01 * (y * y.transpose());
		temp2.noalias() = shift01 * (y * y_mean.transpose());
		temp3.noalias() = shift01 * (y_mean * y.transpose());
		temp4.noalias() = shift00 * (y_mean * y_mean.transpose());
		for(int i=0; i < KHID; i++){
			emp_T3_whitened.block(0,i*KHID, KHID, KHID).noalias() += temp0*y(i);
			emp_T3_whitened.block(0,i*KHID, KHID, KHID).noalias() += temp1*y_mean(i);
			emp_T3_whitened.block(0,i*KHID, KHID, KHID).noalias() += temp2*y(i);
			emp_T3_whitened.block(0,i*KHID, KHID, KHID).noalias() += temp3*y(i);
			emp_T3_whitened.block(0,i*KHID, KHID, KHID).noalias() += temp4*y_mean(i);			
		}
	}
	return emp_T3_whitened;
}