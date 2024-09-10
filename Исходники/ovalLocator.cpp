MBoundingBox ovalLocator::boundingbox (float multiplier /*=1.0f*/) {
	static MBoundingBox boundingbox ;
	if ( boundingbox.min () == boundingbox.max () ) {
		MPointArray vert =ovalLocator::vertices () ;
		for ( unsigned int i =0 ; i < vert.length () ; i++ )
			boundingbox.expand (vert [i]) ;
	}
	MBoundingBox bbox (boundingbox) ;
	if ( multiplier != 1.0f ) {
		double factors [3] ={ multiplier, multiplier, multiplier } ;
		MTransformationMatrix mat ;
		mat.setScale (factors, MSpace::kWorld) ;
		bbox.transformUsing (mat.asScaleMatrix ()) ;
	}
	return (bbox) ;
}