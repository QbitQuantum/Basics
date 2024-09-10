void CDTMapToolSelectTrainingSamples::canvasReleaseEvent(QgsMapMouseEvent *e)
{
    if ( e->button() == Qt::LeftButton )
    {
        if ( mDragging )
        {
            mCanvas->panActionEnd( e->pos() );
            mDragging = false;
        }
        else // add pan to mouse cursor
        {
            // transform the mouse pos to map coordinates
            QgsPoint center = mCanvas->getCoordinateTransform()->toMapPoint( e->x(), e->y() );
            mCanvas->setExtent( QgsRectangle( center, center ) );
            mCanvas->refresh();
        }
    }
    else if (e->button()==Qt::RightButton)
    {
        QgsVectorLayer* vlayer = NULL;
        if ( !mapCanvas->currentLayer()
             || ( vlayer = qobject_cast<QgsVectorLayer *>( mapCanvas->currentLayer() ) ) == NULL )
            return;

        QRect selectRect( 0, 0, 0, 0 );
        int boxSize = 1;
        selectRect.setLeft  ( e->pos().x() - boxSize );
        selectRect.setRight ( e->pos().x() + boxSize );
        selectRect.setTop   ( e->pos().y() - boxSize );
        selectRect.setBottom( e->pos().y() + boxSize );

        const QgsMapToPixel* transform = mapCanvas->getCoordinateTransform();
        QgsPoint ll = transform->toMapCoordinates( selectRect.left(), selectRect.bottom() );
        QgsPoint ur = transform->toMapCoordinates( selectRect.right(), selectRect.top() );

        QgsPolyline points;
        points.push_back(ll);
        points.push_back(QgsPoint( ur.x(), ll.y() ));
        points.push_back(ur);
        points.push_back(QgsPoint( ll.x(), ur.y() ));

        QgsPolygon polygon;
        polygon.push_back(points);
        QgsGeometry selectGeom = *(QgsGeometry::fromPolygon(polygon) );

        if ( mapCanvas->mapSettings().hasCrsTransformEnabled() )
        {
            QgsCoordinateTransform ct( mapCanvas->mapSettings().destinationCrs(), vlayer->crs() );
            selectGeom.transform( ct );
        }

        QgsFeatureIterator fit = vlayer->getFeatures( QgsFeatureRequest().setFilterRect( selectGeom.boundingBox() ).setFlags( QgsFeatureRequest::ExactIntersect ) );
        QgsFeature f;
        qint64 closestFeatureId = 0;
        bool foundSingleFeature = false;
        double closestFeatureDist = std::numeric_limits<double>::max();
        while ( fit.nextFeature( f ) )
        {
            QgsGeometry* g = f.geometry();
            if ( !selectGeom.intersects( g ) )
                continue;
            foundSingleFeature = true;
            double distance = g->distance( selectGeom );
            if ( distance <= closestFeatureDist )
            {
                closestFeatureDist = distance;
                closestFeatureId = f.attribute("GridCode").toInt();
            }
        }

        if ( foundSingleFeature )
            addSingleSample( closestFeatureId );
    }
}