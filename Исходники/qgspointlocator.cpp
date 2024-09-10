 void visitData( const IData& d ) override
 {
   QgsFeatureId id = d.getIdentifier();
   QgsGeometry* g = mLocator->mGeoms.value( id );
   if ( g->intersects( mGeomPt ) )
     mList << QgsPointLocator::Match( QgsPointLocator::Area, mLocator->mLayer, id, 0, QgsPoint() );
 }