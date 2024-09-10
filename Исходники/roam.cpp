float PriorityData::priority( const Vector3f& pos, const Vector3f& look ) {
	float dist = std::max( 0.00001f, 
		(midpoint_vector - pos).length_sq() );
	float dp = pos.dot( midpoint_vector ) / pos.length() / 
		midpoint_vector.length() + 1.0f;
	if( midpoint_vector.length_sq() < 0.999 ) 
		dist *= 10.f;
	return depth / dist * dp;
}