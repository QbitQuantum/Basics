void cofdm_map::set_pilots(bvec x)
{
int K = x.length();
complex<double> p1 ( PA , 0.0);
complex<double> p0 (-PA , 0.0);
int L = zero_carriers.length();
complex<double> c0 (0.0 , 0.0);
int i;

	if( K == pilots_carriers.length() ) {
		for (i=0; i<K; i++) {
			y0(pilots_carriers(i))=x(i)?p1:p0;
		}
		for (i=0; i<L; i++) {
			y0(zero_carriers(i))=c0;
		}
	}
	else {
		throw sci_exception("cofdm_map::set_pilots - x.size() <> pilots_carriers.size()=", pilots_carriers.length());
	}	
}