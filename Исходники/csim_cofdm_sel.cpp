cvec cofdm_sel::get_sel( )
{
cvec cv;
int K = sel_carriers.length();
int i;

	cv.set_length(K);
	for (i=0; i<K; i++) {
		cv(i)= y0(sel_carriers(i));
	}
	return (cv);
}