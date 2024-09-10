int CDanmakuSegmentLine::Fire()
{
	double vx1 = v1 * Cos( a1 );
	double vy1 = v1 * Sin( a1 );
	double vx2 = v2 * Cos( a2 );
	double vy2 = v2 * Sin( a2 );
	double nn = n - 1;
	for( int i = 0; i < n; ++i ) {
		double vx = vx1 * i / nn + vx2 * ( nn - i ) / nn;
		double vy = vy1 * i / nn + vy2 * ( nn - i ) / nn;
		double vv = sqrt(pow2(vx) + pow2(vy));
		double aa = Atan2(vx,vy);
		for( int j = 0; j < m; ++j ) {
			CTama *p = pTama->Copy();
			if( m == 1 )
				p->v = vv;
			else
				p->v = vv * j / (m-1) + vv * ev * (m-1-j) / (m-1);
			p->a = aa;
			g_lTama.Add( p );
		}
	}
	return 1;
}