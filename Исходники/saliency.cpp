std::vector< float > Saliency::uniqueness( const std::vector< SuperpixelStatistic >& stat ) const {
	const int N = stat.size();
	std::vector< float > r( N );
	const float sp = 0.5 / (settings_.sigma_p_ * settings_.sigma_p_);
	for( int i=0; i<N; i++ ) {
		float u = 0, norm = 1e-10;
		Vec3f c = stat[i].mean_color_;
		Vec2f p = stat[i].mean_position_;
		
		// Evaluate the score, for now without filtering
		for( int j=0; j<N; j++ ) {
			Vec3f dc = stat[j].mean_color_ - c;
			Vec2f dp = stat[j].mean_position_ - p;
			
			float w = fast_exp( - sp * dp.dot(dp) );
			u += w*dc.dot(dc);
			norm += w;
		}
		// Let's not normalize here, must have been a typo in the paper
// 		r[i] = u / norm;
		r[i] = u;
	}
	normVec( r );
	return r;
}