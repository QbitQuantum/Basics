    //override
    bool renderFeaturesForStyle(
        const Style&       style,
        const FeatureList& inFeatures,
        osg::Referenced*   buildData,
        const GeoExtent&   imageExtent,
        osg::Image*        image )
    {
        // local copy of the features that we can process
        FeatureList features = inFeatures;

        BuildData* bd = static_cast<BuildData*>( buildData );

        // A processing context to use with the filters:
        FilterContext context;
        context.profile() = getFeatureSource()->getFeatureProfile();

        const LineSymbol* masterLine = style.getSymbol<LineSymbol>();
        const PolygonSymbol* masterPoly = style.getSymbol<PolygonSymbol>();

        //bool embeddedStyles = getFeatureSource()->hasEmbeddedStyles();

        // if only a line symbol exists, and there are polygons in the mix, draw them
        // as outlines (line rings).
        //OE_INFO << LC << "Line Symbol = " << (masterLine == 0L ? "null" : masterLine->getConfig().toString()) << std::endl;
        //OE_INFO << LC << "Poly SYmbol = " << (masterPoly == 0L ? "null" : masterPoly->getConfig().toString()) << std::endl;

        //bool convertPolysToRings = poly == 0L && line != 0L;
        //if ( convertPolysToRings )
        //    OE_INFO << LC << "No PolygonSymbol; will draw polygons to rings" << std::endl;

        // initialize:
        double xmin = imageExtent.xMin();
        double ymin = imageExtent.yMin();
        //double s = (double)image->s();
        //double t = (double)image->t();
        double xf = (double)image->s() / imageExtent.width();
        double yf = (double)image->t() / imageExtent.height();

        // strictly speaking we should iterate over the features and buffer each one that's a line,
        // rather then checking for the existence of a LineSymbol.
        FeatureList linesToBuffer;
        for(FeatureList::iterator i = features.begin(); i != features.end(); i++)
        {
            Feature* feature = i->get();
            Geometry* geom = feature->getGeometry();

            if ( geom )
            {
                // check for an embedded style:
                const LineSymbol* line = feature->style().isSet() ? 
                    feature->style()->getSymbol<LineSymbol>() : masterLine;

                const PolygonSymbol* poly =
                    feature->style().isSet() ? feature->style()->getSymbol<PolygonSymbol>() : masterPoly;

                // if we have polygons but only a LineSymbol, draw the poly as a line.
                if ( geom->getComponentType() == Geometry::TYPE_POLYGON )
                {
                    if ( !poly && line )
                    {
                        Feature* outline = new Feature( *feature );
                        geom = geom->cloneAs( Geometry::TYPE_RING );
                        outline->setGeometry( geom );
                        *i = outline;
                        feature = outline;
                    }
                    //TODO: fix to enable outlined polys. doesn't work, not sure why -gw
                    //else if ( poly && line )
                    //{
                    //    Feature* outline = new Feature();
                    //    geom = geom->cloneAs( Geometry::TYPE_LINESTRING );
                    //    outline->setGeometry( geom );
                    //    features.push_back( outline );
                    //}
                }

                bool needsBuffering =
                    geom->getComponentType() == Geometry::TYPE_LINESTRING || 
                    geom->getComponentType() == Geometry::TYPE_RING;

                if ( needsBuffering )
                {
                    linesToBuffer.push_back( feature );
                }
            }
        }

        if ( linesToBuffer.size() > 0 )
        {
            //We are buffering in the features native extent, so we need to use the transform extent to get the proper "resolution" for the image
            GeoExtent transformedExtent = imageExtent.transform(context.profile()->getSRS());

            double trans_xf = (double)image->s() / transformedExtent.width();
            double trans_yf = (double)image->t() / transformedExtent.height();

            // resolution of the image (pixel extents):
            double xres = 1.0/trans_xf;
            double yres = 1.0/trans_yf;

            // downsample the line data so that it is no higher resolution than to image to which
            // we intend to rasterize it. If you don't do this, you run the risk of the buffer 
            // operation taking forever on very high-res input data.
            if ( _options.optimizeLineSampling() == true )
            {
                ResampleFilter resample;
                resample.minLength() = osg::minimum( xres, yres );
                context = resample.push( linesToBuffer, context );
            }

            // now run the buffer operation on all lines:
            BufferFilter buffer;
            float lineWidth = 0.5;
            if ( masterLine )
            {
                buffer.capStyle() = masterLine->stroke()->lineCap().value();

                if ( masterLine->stroke()->width().isSet() )
                    lineWidth = masterLine->stroke()->width().value();
            }

            // "relative line size" means that the line width is expressed in (approx) pixels
            // rather than in map units
            if ( _options.relativeLineSize() == true )
                buffer.distance() = xres * lineWidth;
            else
                buffer.distance() = lineWidth;

            buffer.push( linesToBuffer, context );
        }

        // First, transform the features into the map's SRS:
        TransformFilter xform( imageExtent.getSRS() );
        xform.setLocalizeCoordinates( false );
        context = xform.push( features, context );

        // set up the AGG renderer:
        agg::rendering_buffer rbuf( image->data(), image->s(), image->t(), image->s()*4 );

        // Create the renderer and the rasterizer
        agg::renderer<agg::span_abgr32> ren(rbuf);
        agg::rasterizer ras;

        // Setup the rasterizer
        ras.gamma(1.3);
        ras.filling_rule(agg::fill_even_odd);

        GeoExtent cropExtent = GeoExtent(imageExtent);
        cropExtent.scale(1.1, 1.1);

        osg::ref_ptr<Symbology::Polygon> cropPoly = new Symbology::Polygon( 4 );
        cropPoly->push_back( osg::Vec3d( cropExtent.xMin(), cropExtent.yMin(), 0 ));
        cropPoly->push_back( osg::Vec3d( cropExtent.xMax(), cropExtent.yMin(), 0 ));
        cropPoly->push_back( osg::Vec3d( cropExtent.xMax(), cropExtent.yMax(), 0 ));
        cropPoly->push_back( osg::Vec3d( cropExtent.xMin(), cropExtent.yMax(), 0 ));

        double lineWidth = 1.0;
        if ( masterLine )
            lineWidth = (double)masterLine->stroke()->width().value();

        osg::Vec4 color = osg::Vec4(1, 1, 1, 1);
        if ( masterLine )
            color = masterLine->stroke()->color();

        // render the features
        for(FeatureList::iterator i = features.begin(); i != features.end(); i++)
        {
            Feature* feature = i->get();
            //bool first = bd->_pass == 0 && i == features.begin();

            Geometry* geometry = feature->getGeometry();

            osg::ref_ptr< Geometry > croppedGeometry;
            if ( ! geometry->crop( cropPoly.get(), croppedGeometry ) )
                continue;

            // set up a default color:
            osg::Vec4 c = color;
            unsigned int a = (unsigned int)(127+(c.a()*255)/2); // scale alpha up
            agg::rgba8 fgColor( (unsigned int)(c.r()*255), (unsigned int)(c.g()*255), (unsigned int)(c.b()*255), a );

            GeometryIterator gi( croppedGeometry.get() );
            while( gi.hasMore() )
            {
                c = color;
                Geometry* g = gi.next();
            
                const LineSymbol* line = feature->style().isSet() ? 
                    feature->style()->getSymbol<LineSymbol>() : masterLine;

                const PolygonSymbol* poly =
                    feature->style().isSet() ? feature->style()->getSymbol<PolygonSymbol>() : masterPoly;

                if (g->getType() == Geometry::TYPE_RING || g->getType() == Geometry::TYPE_LINESTRING)
                {
                    if ( line )
                        c = line->stroke()->color();
                    else if ( poly )
                        c = poly->fill()->color();
                }

                else if ( g->getType() == Geometry::TYPE_POLYGON )
                {
                    if ( poly )
                        c = poly->fill()->color();
                    else if ( line )
                        c = line->stroke()->color();
                }

                a = (unsigned int)(127+(c.a()*255)/2); // scale alpha up
                fgColor = agg::rgba8( (unsigned int)(c.r()*255), (unsigned int)(c.g()*255), (unsigned int)(c.b()*255), a );

                ras.filling_rule( agg::fill_even_odd );
                for( Geometry::iterator p = g->begin(); p != g->end(); p++ )
                {
                    const osg::Vec3d& p0 = *p;
                    double x0 = xf*(p0.x()-xmin);
                    double y0 = yf*(p0.y()-ymin);

                    //const osg::Vec3d& p1 = p+1 != g->end()? *(p+1) : g->front();
                    //double x1 = xf*(p1.x()-xmin);
                    //double y1 = yf*(p1.y()-ymin);

                    if ( p == g->begin() )
                        ras.move_to_d( x0, y0 );
                    else
                        ras.line_to_d( x0, y0 );
                }
            }
            ras.render(ren, fgColor);
            ras.reset();
        }

        bd->_pass++;
        return true;            
    }