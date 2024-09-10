void FBBaseFunction< Dimension, Scalar >::compute(
			const Vector& x, const Vector& y, Vector& fb,
			Matrix& dFb_dx, Matrix& dFb_dy )
{
	const unsigned d = x.rows() ;

	// see [Daviet et al 2011], Appendix A.1

	Vector z2(d) ;

	z2[0] = x.squaredNorm() + y.squaredNorm() ;
	Traits::tp( z2 ) = x[0] * Traits::tp( x ) + y[0] * Traits::tp( y ) ;
	const Scalar nz2t = Traits::tp( z2 ).norm() ;

	Vector omega1(d), omega2(d) ;
	omega1[0] = omega2[0] = .5 ;

	if( NumTraits< Scalar >::isZero( nz2t ) )
	{
		Traits::tp( omega1 ).setZero() ;
		omega1[1] = -.5 ;
		Traits::tp( omega2 ).setZero() ;
		omega2[1] =  .5 ;
	} else {
		Traits::tp( omega1 ) = -.5* Traits::tp( z2 ) / nz2t ;
		Traits::tp( omega2 ) =  .5* Traits::tp( z2 ) / nz2t ;
	}

	const Scalar rlambda1 = std::sqrt( std::max( (Scalar) 0, z2[0] - 2*nz2t ) ) ;
	const Scalar rlambda2 = std::sqrt( z2[0] + 2*nz2t ) ;

	const Vector z = rlambda1 * omega1 + rlambda2 * omega2 ;
	fb = x + y - z ;

	if( JacobianAsWell )
	{
		const Matrix Id( Matrix::Identity( d, d ) ) ;

		if( NumTraits< Scalar >::isZero( rlambda2 ) )
		{
			// x = y = 0
			dFb_dx.setZero( d,d ) ;
			dFb_dy.setZero( d,d ) ;
		} else {
			if( NumTraits< Scalar >::isZero( rlambda1 ) )
			{
				const Scalar izn = 1. / ( x[0]*x[0] + y[0]*y[0] ) ;
				dFb_dx = ( 1. - x[0]*izn ) * Id ;
				dFb_dy = ( 1. - y[0]*izn ) * Id ;
			} else {
				const Scalar det = rlambda1 * rlambda2 ;

				Matrix L, invLz(d,d) ;

				invLz(0, 0) = z[0] ;
				Traits::ntb( invLz ) = -Traits::tp( z ).transpose() ;
				Traits::tnb( invLz ) = -Traits::tp( z ) ;
				Traits::ttb( invLz ) =
					( det * Traits::TgMatrix::Identity( d-1, d-1 ) +
					  Traits::tp( z ) * Traits::tp( z ).transpose() ) / z[0] ;
				invLz /= det ;

				L = x[0] * Id ;
				Traits::ntb( L ) = Traits::tp( x ).transpose() ;
				Traits::tnb( L ) = Traits::tp( x ) ;
				dFb_dx.setIdentity( d,d ) ;
				dFb_dx.noalias() -= invLz * L ;

				L = y[0] * Id ;
				Traits::ntb( L ) = Traits::tp( y ).transpose() ;
				Traits::tnb( L ) = Traits::tp( y ) ;
				dFb_dy.setIdentity( d,d ) ;
				dFb_dy.noalias() -= invLz * L ;

			}
		}

	}

}