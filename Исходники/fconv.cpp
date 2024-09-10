void	fconv_1( const Mat &A, const Mat &F, Mat &R )
{
	int		RowA = A.rows, ColA = A.cols, NumFeatures = A.channels();
	int		RowF = F.rows, ColF = F.cols, ChnF = F.channels();
	if( NumFeatures!=ChnF )
		throw runtime_error("");

	int    RowR = RowA - RowF + 1, ColR = ColA - ColF + 1;

	float *Rpt = (float*)R.data;
	int Rstep = R.step1();

	for( int r=0; r!=RowR; r++ ){
		float *pt = Rpt + r*Rstep;
		for( int c=0; c!=ColR; c++ ){
			Mat	Asub = A( Rect(c,r,ColF,RowF) );
			*(pt++) = (float)( F.dot( Asub ) );
		}
	}
}