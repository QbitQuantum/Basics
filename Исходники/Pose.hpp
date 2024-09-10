	/** 
	 * Test if the delta of the provided transformations is greater in 
	 * either distance or angle than the threshold.
	 *
	 * @param a2b the initial transformation from A to B
	 * @param aprime2b the next transformation from A' to B
	 *
	 * @result true if the transformation A' to A is greater than the stored thresholds
	 */
	bool test( const Eigen::Affine3d& a2b, const Eigen::Affine3d& aprime2b )
	{
	    return test( a2b.inverse() * aprime2b );
	}