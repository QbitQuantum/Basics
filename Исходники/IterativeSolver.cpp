/*! This code doesn't make use of any preconditioner*/
void Iterative_Solver::BiCG(SparseMatrix &spm,Vector <double> &X,Vector<double> &B){
//	cout << "BiCG entered"<< endl;
	int number_of_iterations = 0;
	Vector<double> Q;
	Q.set_size(X.get_size());
	Q.initialize();
	spm.multiply(X,Q);
	//	Q = spm*X;
	Vector<double> r;
	r.set_size(X.get_size());
	r.sub(B,Q);
	//	r = B - Q;
	Vector<double> r_star;
	r_star.set_size(X.get_size());
	r_star.copy_values(r);
	double beeta;
	double alpha = 1.0;
	double rho = 1.0;
	double omega = 1.0;
	//	double p1 = 0.0;
	double error = 199;
	Vector<double> temp;
	temp.set_size(X.get_size());
	temp.initialize();
	Vector<double> p1;
	p1.set_size(X.get_size());
	p1.initialize();
	Vector<double> v;
	v.set_size(X.get_size());
	v.initialize();
	Vector<double> s;
	s.set_size(X.get_size());
	s.initialize();
	Vector<double> t;
	t.set_size(X.get_size());
	t.initialize();
	Vector<double> temp1;
	temp1.set_size(X.get_size());
	temp1.initialize();
	//	cout << "Line 145" << endl;
//	cout << "Iterations started" << endl;
	while(error > pow(10.0,-6)){
		temp.copy_values(X);
		//		cout << "Line 148" << endl;
		double rho_1 = r_star*r;
		//		cout << "Line 150" <<endl;
		beeta = (rho_1/rho)*(alpha/omega);
		//		cout << "Line 151" << endl;
		temp1.add(p1,v,-omega);
		//		p1 = r + (p1 - v*omega)*beeta;
		p1.add(r,temp1,beeta);

		//		cout << "Line 153";
		spm.multiply(p1,v);
		//		v = spm*p1;
		//		cout << "*******" << endl;
		//		v.display();
		alpha = rho_1/(r_star*v);
		//		cout << "Line 159";
		s.add(r,v,-alpha);
		//		cout << "Line 161";
		//		s = r - v*alpha;
		spm.multiply(s,t);
		//		t.display();
		//		cout << "Line 164";
		//		t = spm*s;
		double tempval1 = t*s;
		double tempval2 = t*t;
		//		t.display();
		//		cout << tempval1 << endl;
		//		cout << tempval2 << endl;


		omega = (tempval1)/(tempval2);

		//		cout << "Line 167" << endl;
		//		temp1.initialize();
		temp1.add(X,p1,alpha);
		X.add(temp1,s,omega);
		//		temp1.initialize();
		//		X = X + s*omega + p1*alpha;
		r.add(s,t,-omega);
		//		r = s - t*omega;
		rho = rho_1;
		//		cout << "Line 189" <<endl;
		error = cal_error(X,temp);
//		cout << error << endl;
		number_of_iterations++;
//		if((number_of_iterations % 100) == 0){
//					cout << "Iteration number " << number_of_iterations << "completed " << endl;
//				}
	}
//
//	cout << "Error in calculation " << error << endl;
//	cout << "Solution Converged from BiConjugate Gradient without any preconditioner after " << number_of_iterations << " iterations" << endl;
//	//	X.display();
//	//	return X;
//	cout << "Writing in file" << endl;
//	ofstream fout("solver.txt");
//	for(int i = 0; i < X.get_size(); i++){
//		fout << X[i] << endl;
//	}
//	fout.close();
//	cout << "File Written" << endl;
	//	return;

}