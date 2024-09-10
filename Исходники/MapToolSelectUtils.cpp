void QgsMapToolSelectUtils::setSelectFeatures( QgsMapCanvas* canvas,
	QgsGeometry* selectGeometry,
	bool doContains,
	bool doDifference,
	bool singleSelect )
{
	if ( selectGeometry->type() != QGis::Polygon )
	{
		return;
	}
	QgsVectorLayer* vlayer = QgsMapToolSelectUtils::getCurrentVectorLayer( canvas );
	if ( vlayer == nullptr )
	{
		return;
	}

	// toLayerCoordinates will throw an exception for any 'invalid' points in
	// the rubber band.
	// For example, if you project a world map onto a globe using EPSG 2163
	// and then click somewhere off the globe, an exception will be thrown.
	//QgsGeometry selectGeomTrans( *selectGeometry );

	//if ( canvas->mapSettings().hasCrsTransformEnabled() )
	//{
	//	try
	//	{
	//		QgsCoordinateTransform ct( canvas->mapSettings().destinationCrs(), vlayer->crs() );
	//		selectGeomTrans.transform( ct );
	//	}
	//	catch ( QgsCsException &cse )
	//	{
	//		Q_UNUSED( cse );
	//		// catch exception for 'invalid' point and leave existing selection unchanged
	//		QgsLogger::warning( "Caught CRS exception " + QString( __FILE__ ) + ": " + QString::number( __LINE__ ) );
	//		LOG_INFO( "CRS Exception\nSelection extends beyond layer's coordinate system" );
	//		return;
	//	}
	//}
	QgsGeometry selectGeomTrans;
	try{
		selectGeomTrans = toLayerCoordinates( canvas, selectGeometry, vlayer );
	}
	catch ( QgsCsException & )
	{
		return;
	}

	QApplication::setOverrideCursor( Qt::WaitCursor );

	QgsDebugMsg( "Selection layer: " + vlayer->name() );
	QgsDebugMsg( "Selection polygon: " + selectGeomTrans.exportToWkt() );
	QgsDebugMsg( "doContains: " + QString( doContains ? "T" : "F" ) );
	QgsDebugMsg( "doDifference: " + QString( doDifference ? "T" : "F" ) );

	QgsRenderContext context = QgsRenderContext::fromMapSettings( canvas->mapSettings() );
	QgsFeatureRendererV2* r = vlayer->rendererV2();
	if ( r )
		r->startRender( context, vlayer->pendingFields() );

	QgsFeatureRequest request;
	request.setFilterRect( selectGeomTrans.boundingBox() );
	request.setFlags( QgsFeatureRequest::ExactIntersect );
	if ( r )
		request.setSubsetOfAttributes( r->usedAttributes(), vlayer->pendingFields() );
	else
		request.setSubsetOfAttributes( QgsAttributeList() );

	QgsFeatureIterator fit = vlayer->getFeatures( request );

	QgsFeatureIds newSelectedFeatures;
	QgsFeature f;
	QgsFeatureId closestFeatureId = 0;
	bool foundSingleFeature = false;
	double closestFeatureDist = std::numeric_limits<double>::max();
	while ( fit.nextFeature( f ) )
	{
#if (VERSION_INT >= 21601)
		context.expressionContext().setFeature( f );		//taken from QGIS 2.16.1
		// make sure to only use features that are visible
		if ( r && !r->willRenderFeature( f, context ) )
#else
		if ( r && !r->willRenderFeature( f ) )
#endif
			continue;

		QgsGeometry* g = f.geometry();
		if ( doContains )
		{
			if ( !selectGeomTrans.contains( g ) )
				continue;
		}
		else
		{
			if ( !selectGeomTrans.intersects( g ) )
				continue;
		}
		if ( singleSelect )
		{
			foundSingleFeature = true;
			double distance = g->distance( selectGeomTrans );
			if ( distance <= closestFeatureDist )
			{
				closestFeatureDist = distance;
				closestFeatureId = f.id();
			}
		}
		else
		{
			newSelectedFeatures.insert( f.id() );
		}
	}
	if ( singleSelect && foundSingleFeature )
	{
		newSelectedFeatures.insert( closestFeatureId );
	}

	if ( r )
		r->stopRender( context );

	QgsDebugMsg( "Number of new selected features: " + QString::number( newSelectedFeatures.size() ) );

	if ( doDifference )
	{
		QgsFeatureIds layerSelectedFeatures = vlayer->selectedFeaturesIds();

		QgsFeatureIds selectedFeatures;
		QgsFeatureIds deselectedFeatures;

		QgsFeatureIds::const_iterator i = newSelectedFeatures.constEnd();
		while ( i != newSelectedFeatures.constBegin() )
		{
			--i;
			if ( layerSelectedFeatures.contains( *i ) )
			{
				deselectedFeatures.insert( *i );
			}
			else
			{
				selectedFeatures.insert( *i );
			}
		}

		vlayer->modifySelection( selectedFeatures, deselectedFeatures );
	}
	else
	{
		SelectFeatures( vlayer, newSelectedFeatures );		//		vlayer->setSelectedFeatures( newSelectedFeatures );
	}

	QApplication::restoreOverrideCursor();
}