bool
ExtrudeGeometryFilter::buildStructure(const Geometry*         input,
                                      double                  height,
                                      double                  heightOffset,
                                      bool                    flatten,
                                      const SkinResource*     wallSkin,
                                      const SkinResource*     roofSkin,
                                      Structure&              structure,
                                      FilterContext&          cx )
{
    bool  makeECEF                 = false;
    const SpatialReference* srs    = 0L;
    const SpatialReference* mapSRS = 0L;

    if ( cx.isGeoreferenced() )
    {
       srs      = cx.extent()->getSRS();
       makeECEF = cx.getSession()->getMapInfo().isGeocentric();
       mapSRS   = cx.getSession()->getMapInfo().getProfile()->getSRS();
    }

    // whether this is a closed polygon structure.
    structure.isPolygon = (input->getComponentType() == Geometry::TYPE_POLYGON);

    // extrusion working variables
    double     targetLen = -DBL_MAX;
    osg::Vec3d minLoc(DBL_MAX, DBL_MAX, DBL_MAX);
    double     minLoc_len = DBL_MAX;
    osg::Vec3d maxLoc(0,0,0);
    double     maxLoc_len = 0;

    // Initial pass over the geometry does two things:
    // 1: Calculate the minimum Z across all parts.
    // 2: Establish a "target length" for extrusion
    double absHeight = fabs(height);

    ConstGeometryIterator zfinder( input );
    while( zfinder.hasMore() )
    {
        const Geometry* geom = zfinder.next();
        for( Geometry::const_iterator m = geom->begin(); m != geom->end(); ++m )
        {
            osg::Vec3d m_point = *m;

            if ( m_point.z() + absHeight > targetLen )
                targetLen = m_point.z() + absHeight;

            if (m_point.z() < minLoc.z())
                minLoc = m_point;

            if (m_point.z() > maxLoc.z())
                maxLoc = m_point;
        }
    }

    // apply the height offsets
    height    -= heightOffset;
    targetLen -= heightOffset;
    
    float   roofRotation  = 0.0f;
    Bounds  roofBounds;
    float   sinR = 0.0f, cosR = 0.0f;
    double  roofTexSpanX = 0.0, roofTexSpanY = 0.0;
    osg::ref_ptr<const SpatialReference> roofProjSRS;

    if ( roofSkin )
    {
        roofBounds = input->getBounds();

        // if our data is lat/long, we need to reproject the geometry and the bounds into a projected
        // coordinate system in order to properly generate tex coords.
        if ( srs && srs->isGeographic() )
        {
            osg::Vec2d geogCenter = roofBounds.center2d();
            roofProjSRS = srs->createUTMFromLonLat( Angle(geogCenter.x()), Angle(geogCenter.y()) );
            if ( roofProjSRS.valid() )
            {
                roofBounds.transform( srs, roofProjSRS.get() );
                osg::ref_ptr<Geometry> projectedInput = input->clone();
                srs->transform( projectedInput->asVector(), roofProjSRS.get() );
                roofRotation = getApparentRotation( projectedInput.get() );
            }
        }
        else
        {
            roofRotation = getApparentRotation( input );
        }
            
        sinR = sin(roofRotation);
        cosR = cos(roofRotation);

        if ( !roofSkin->isTiled().value() )
        {
            //note: non-tiled roofs don't really work atm.
            roofTexSpanX = cosR*roofBounds.width() - sinR*roofBounds.height();
            roofTexSpanY = sinR*roofBounds.width() + cosR*roofBounds.height();
        }
        else
        {
            roofTexSpanX = roofSkin->imageWidth().isSet() ? *roofSkin->imageWidth() : roofSkin->imageHeight().isSet() ? *roofSkin->imageHeight() : 10.0;
            if ( roofTexSpanX <= 0.0 ) roofTexSpanX = 10.0;
            roofTexSpanY = roofSkin->imageHeight().isSet() ? *roofSkin->imageHeight() : roofSkin->imageWidth().isSet() ? *roofSkin->imageWidth() : 10.0;
            if ( roofTexSpanY <= 0.0 ) roofTexSpanY = 10.0;
        }
    }

    // prep for wall texture coordinate generation.
    double texWidthM  = wallSkin ? *wallSkin->imageWidth() : 0.0;
    double texHeightM = wallSkin ? *wallSkin->imageHeight() : 1.0;

    ConstGeometryIterator iter( input );
    while( iter.hasMore() )
    {
        const Geometry* part = iter.next();

        // skip a part that's too small
        if (part->size() < 2)
            continue;

        // add a new wall.
        structure.elevations.push_back(Elevation());
        Elevation& elevation = structure.elevations.back();

        double maxHeight = targetLen - minLoc.z();

        // Adjust the texture height so it is a multiple of the maximum height
        double div = osg::round(maxHeight / texHeightM);
        elevation.texHeightAdjustedM = div > 0.0 ? maxHeight / div : maxHeight;

        // Step 1 - Create the real corners and transform them into our target SRS.
        Corners corners;
        for(Geometry::const_iterator m = part->begin(); m != part->end(); ++m)
        {
            Corners::iterator corner = corners.insert(corners.end(), Corner());
            
            // mark as "from source", as opposed to being inserted by the algorithm.
            corner->isFromSource = true;
            corner->base = *m;

            // extrude:
            if ( height >= 0 ) // extrude up
            {
                if ( flatten )
                    corner->roof.set( corner->base.x(), corner->base.y(), targetLen );
                else
                    corner->roof.set( corner->base.x(), corner->base.y(), corner->base.z() + height );
            }
            else // height < 0 .. extrude down
            {
                corner->roof = *m;
                corner->base.z() += height;
            }
            
            // figure out the rooftop texture coords before doing any transformation:
            if ( roofSkin && srs )
            {
                double xr, yr;

                if ( srs && srs->isGeographic() && roofProjSRS )
                {
                    osg::Vec3d projRoofPt;
                    srs->transform( corner->roof, roofProjSRS.get(), projRoofPt );
                    xr = (projRoofPt.x() - roofBounds.xMin());
                    yr = (projRoofPt.y() - roofBounds.yMin());
                }
                else
                {
                    xr = (corner->roof.x() - roofBounds.xMin());
                    yr = (corner->roof.y() - roofBounds.yMin());
                }

                corner->roofTexU = (cosR*xr - sinR*yr) / roofTexSpanX;
                corner->roofTexV = (sinR*xr + cosR*yr) / roofTexSpanY;
            }
            
            // transform into target SRS.
            transformAndLocalize( corner->base, srs, corner->base, mapSRS, _world2local, makeECEF );
            transformAndLocalize( corner->roof, srs, corner->roof, mapSRS, _world2local, makeECEF );
        }

        // Step 2 - Insert intermediate Corners as needed to satify texturing
        // requirements (if necessary) and record each corner offset (horizontal distance
        // from the beginning of the part geometry to the corner.)
        double cornerOffset    = 0.0;
        double nextTexBoundary = texWidthM;

        for(Corners::iterator c = corners.begin(); c != corners.end(); ++c)
        {
            Corners::iterator this_corner = c;

            Corners::iterator next_corner = c;
            if ( ++next_corner == corners.end() )
                next_corner = corners.begin();

            osg::Vec3d base_vec = next_corner->base - this_corner->base;
            double span = base_vec.length();

            this_corner->offsetX = cornerOffset;

            if (wallSkin)
            {
                base_vec /= span; // normalize
                osg::Vec3d roof_vec = next_corner->roof - this_corner->roof;
                roof_vec.normalize();

                while(nextTexBoundary < cornerOffset+span)
                {
                    // insert a new fake corner.
                    Corners::iterator new_corner = corners.insert(next_corner, Corner());
                    new_corner->isFromSource = false;
                    double advance = nextTexBoundary-cornerOffset;
                    new_corner->base = this_corner->base + base_vec*advance;
                    new_corner->roof = this_corner->roof + roof_vec*advance;
                    new_corner->offsetX = cornerOffset + advance;
                    nextTexBoundary += texWidthM;

                    // advance the main iterator
                    c = new_corner;
                }
            }

            cornerOffset += span;
        }

        // Step 3 - Calculate the angle of each corner.
        osg::Vec3d prev_vec;
        for(Corners::iterator c = corners.begin(); c != corners.end(); ++c)
        {
            Corners::const_iterator this_corner = c;

            Corners::const_iterator next_corner = c;
            if ( ++next_corner == corners.end() )
                next_corner = corners.begin();

            if ( this_corner == corners.begin() )
            {
                Corners::const_iterator prev_corner = corners.end();
                --prev_corner;
                prev_vec = this_corner->roof - prev_corner->roof;
                prev_vec.normalize();
            }

            osg::Vec3d this_vec = next_corner->roof - this_corner->roof;
            this_vec.normalize();
            if ( c != corners.begin() )
            {
                c->cosAngle = prev_vec * this_vec;
            }
        }

        // Step 4 - Create faces connecting each pair of Posts.
        Faces& faces = elevation.faces;
        for(Corners::const_iterator c = corners.begin(); c != corners.end(); ++c)
        {
            Corners::const_iterator this_corner = c;

            Corners::const_iterator next_corner = c;
            if ( ++next_corner == corners.end() )
                next_corner = corners.begin();
            
            // only close the shape for polygons.
            if (next_corner != corners.begin() || structure.isPolygon)
            {
                faces.push_back(Face());
                Face& face = faces.back();
                face.left  = *this_corner;
                face.right = *next_corner;

                // recalculate the final offset on the last face
                if ( next_corner == corners.begin() )
                {
                    osg::Vec3d vec = next_corner->roof - this_corner->roof;
                    face.right.offsetX = face.left.offsetX + vec.length();
                }

                face.widthM = next_corner->offsetX - this_corner->offsetX;
            }
        }
    }

    return true;
}