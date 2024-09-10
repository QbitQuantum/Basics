void ShapeTextureFeature::add( const Eigen::Matrix< double, 6, 1 >& p_src, const Eigen::Matrix< double, 6, 1 >& p_dst, const Eigen::Vector3d& n_src, const Eigen::Vector3d& n_dst, float weight ) {
	// surflet pair relation as in "model globally match locally"
	const Eigen::Vector3d& p1 = p_src.block<3,1>(0,0);
	const Eigen::Vector3d& p2 = p_dst.block<3,1>(0,0);
	const Eigen::Vector3d& n1 = n_src;
	const Eigen::Vector3d& n2 = n_dst;

	Eigen::Vector3d d = p2-p1;
	d.normalize();

	const int s1 = std::min( (SHAPE_TEXTURE_TABLE_SIZE-1), std::max( 0, (int)round((SHAPE_TEXTURE_TABLE_SIZE-1.0) * 0.5 * (n1.dot( d )+1.0) ) ) );
	const int s2 = std::min( (SHAPE_TEXTURE_TABLE_SIZE-1), std::max( 0, (int)round((SHAPE_TEXTURE_TABLE_SIZE-1.0) * 0.5 * (n2.dot( d )+1.0) ) ) );
	const int s3 = std::min( (SHAPE_TEXTURE_TABLE_SIZE-1), std::max( 0, (int)round((SHAPE_TEXTURE_TABLE_SIZE-1.0) * 0.5 * (n1.dot( n2 )+1.0) ) ) );

	shape_.block<1,NUM_SHAPE_BINS>(0,0) += weight * ShapeTextureTable::instance()->shape_value_table_[0][s1];
	shape_.block<1,NUM_SHAPE_BINS>(1,0) += weight * ShapeTextureTable::instance()->shape_value_table_[1][s2];
	shape_.block<1,NUM_SHAPE_BINS>(2,0) += weight * ShapeTextureTable::instance()->shape_value_table_[2][s3];


	const int c1 = std::min( (SHAPE_TEXTURE_TABLE_SIZE-1), std::max( 0, (int)round((SHAPE_TEXTURE_TABLE_SIZE-1.0) * 0.5 * ((p_dst(3,0) - p_src(3,0))+1.0) ) ) );
	const int c2 = std::min( (SHAPE_TEXTURE_TABLE_SIZE-1), std::max( 0, (int)round((SHAPE_TEXTURE_TABLE_SIZE-1.0) * 0.25 * ((p_dst(4,0) - p_src(4,0))+2.0) ) ) );
	const int c3 = std::min( (SHAPE_TEXTURE_TABLE_SIZE-1), std::max( 0, (int)round((SHAPE_TEXTURE_TABLE_SIZE-1.0) * 0.25 * ((p_dst(5,0) - p_src(5,0))+2.0) ) ) );

	texture_.block<1,NUM_TEXTURE_BINS>(0,0) += weight * ShapeTextureTable::instance()->texture_value_table_[0][c1];
	texture_.block<1,NUM_TEXTURE_BINS>(1,0) += weight * ShapeTextureTable::instance()->texture_value_table_[1][c2];
	texture_.block<1,NUM_TEXTURE_BINS>(2,0) += weight * ShapeTextureTable::instance()->texture_value_table_[2][c3];

	num_points_ += weight;
}