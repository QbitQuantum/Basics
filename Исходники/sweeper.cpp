std::vector<int> ptsubsetBetween2Line( std::vector<Point2f> points2d, Point2f p0, Point2f p1, Point2f t0){

	t0.Normalize() ;
	std::vector<int> res ;
	for( int i=0; i<points2d.size(); ++i ){
		Point2f p0p1 = p1-p0 ;
		if(  p0p1 * (points2d[i]-p1) <= 0 &&  !ReconstructorUtility::vectorIntersect(p0-t0*100, p0+t0*100, points2d[i], p1 ) )
			res.push_back( i ) ;
	}
	return res ;
}