bool Tracer::scatterDiffuse(const IntersectDescr& node, Ray& ray) const
{
	const Material& material = node.shape_->getMaterial();

	const double max_comp = std::max(
		material.getColor()[ 0 ],
		std::max( material.getColor()[ 1 ], material.getColor()[ 2 ] ) );

	if( max_comp <= 1e-4 )
	{
		return false;
	}

	const Vector w_vec = node.normal_;
	Vector u_vec = std::abs( w_vec[ 0 ] ) > .1 ? Vector( 0., 1., 0. )
											   : Vector( 1., 0., 0. );
	u_vec = u_vec.cross( w_vec ).normalized();
	const Vector v_vec = w_vec.cross( u_vec ).normalized();

	const double theta = 2. * ::PI * uniform_distrib_( rand_gen_ );
	const double radius = uniform_distrib_( rand_gen_ );
	const double radius_sqr = std::sqrt( radius );

	ray = Ray( node.point_,
			   ( u_vec * std::cos( theta ) * radius_sqr +
				 v_vec * std::sin( theta ) * radius_sqr +
				 w_vec * std::sqrt( 1. - radius ) )
				   .normalized() );
	return true;
}