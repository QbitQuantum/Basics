int main() {
	int n = 2000;
	double T = 2000_ns;
	double delta_t = T/n;
	vector<double> f1_list = { -30_MHz,-25_MHz,-20_MHz,-14.5_MHz,-10_MHz,-5_MHz,0_MHz,5_MHz,10_MHz,14.5_MHz,20_MHz,25_MHz,30_MHz };
	for(auto k=f1_list.begin();k!=f1_list.end();k++) {
		/* Hamiltonian */
		double f1 = *k;
		Operator H = 2*pi*(fe*Sz(0)+f1*Sx(0));
		for(int i=0;i<N;i++)
			H += 2*pi*(fi*Sz(i+1)+Sz(0)*(Azx[i]*Sx(i+1)+Azy[i]*Sy(i+1)+Azz[i]*Sz(i+1)));
		auto U = H.U();
		/* initial state */
		double alpha_e = 7.6216e-4;
		double alpha_i = -1.1579e-6;
		//Operator rho0 = Op<2>(0,0.5*(1-alpha_e),0,0,0.5*(1+alpha_e));
		Operator rho0 = Op<2>(0,0.5,0.5,0.5,0.5);
		for(int i=1;i<=N;i++)
			rho0 *= Op<2>(i,0.5*(1-alpha_i),0,0,0.5*(1+alpha_i));
		/* output stream */
		stringstream fnstream;
		fnstream << "malonic-DNP_" << f1/1_MHz << "MHz.txt";
		string fn = fnstream.str();
		ofstream out(fn);
		cout << fn << ":" << endl;
		/* calculate and output */
		for(int i=0;i<=n;i++) {
			double t = delta_t*i;
			cout << fn << ":\t" << t/T*100 << "%" << endl;
			out << t/1_ns << '\t';
			Operator rho = U(t)*rho0*U(-t);
			Operator rhoe = rho;
			for(int j=1;j<=N;j++)
				rhoe = rhoe.tr(j);
			out << real(tr(rhoe*Sx(0))) << '\t';
			out << real(tr(rhoe*Sy(0))) << '\t';
			out << real(tr(rhoe*Sz(0))) << '\t';
			for(int j=1;j<=N;j++) {
				Operator rhoj = rho;
				for(int k=0;k<=N;k++) {
					if(k==j)
						continue;
					rhoj = rhoj.tr(k);
				}
				out << real(tr(rhoj*Sz(j))) << '\t';
			}
			out << endl;
		}
		out.close();
	}
}