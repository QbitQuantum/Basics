// builds and tessellates a polygon (with or without holes)
void
BuildGeometryFilter::buildPolygon(Geometry*               ring,
                                  const SpatialReference* featureSRS,
                                  const SpatialReference* mapSRS,
                                  bool                    makeECEF,
                                  bool                    tessellate,
                                  osg::Geometry*          osgGeom,
                                  const osg::Matrixd      &world2local)
{
    if ( !ring->isValid() )
        return;

    ring->rewind(osgEarth::Symbology::Geometry::ORIENTATION_CCW);

    osg::ref_ptr<osg::Vec3Array> allPoints = new osg::Vec3Array();
    transformAndLocalize( ring->asVector(), featureSRS, allPoints.get(), mapSRS, world2local, makeECEF );

    Polygon* poly = dynamic_cast<Polygon*>(ring);
    if ( poly )
    {
        RingCollection ordered(poly->getHoles().begin(), poly->getHoles().end());
        std::sort(ordered.begin(), ordered.end(), holeCompare);

        for( RingCollection::const_iterator h = ordered.begin(); h != ordered.end(); ++h )
        {
            Geometry* hole = h->get();
            if ( hole->isValid() )
            {
                hole->rewind(osgEarth::Symbology::Geometry::ORIENTATION_CW);

                osg::ref_ptr<osg::Vec3Array> holePoints = new osg::Vec3Array();
                transformAndLocalize( hole->asVector(), featureSRS, holePoints.get(), mapSRS, world2local, makeECEF );

                // find the point with the highest x value
                unsigned int hCursor = 0;
                for (unsigned int i=1; i < holePoints->size(); i++)
                {
                    if ((*holePoints)[i].x() > (*holePoints)[hCursor].x())
                      hCursor = i;
                }

                double x1 = (*holePoints)[hCursor].x();
                double y1 = (*holePoints)[hCursor].y();
                double y2 = (*holePoints)[hCursor].y();

                unsigned int edgeCursor = UINT_MAX;
                double edgeDistance = DBL_MAX;
                unsigned int foundPointCursor = UINT_MAX;
                for (unsigned int i=0; i < allPoints->size(); i++)
                {
                    unsigned int next = i == allPoints->size() - 1 ? 0 : i + 1;
                    double xMax = osg::maximum((*allPoints)[i].x(), (*allPoints)[next].x());

                    if (xMax > (*holePoints)[hCursor].x())
                    {
                        double x2 = xMax + 1.0;
                        double x3 = (*allPoints)[i].x();
                        double y3 = (*allPoints)[i].y();
                        double x4 = (*allPoints)[next].x();
                        double y4 = (*allPoints)[next].y();

                        double xi=0.0, yi=0.0;
                        bool intersects = false;
                        unsigned int hitPointCursor = UINT_MAX;
                        if (y1 == y3 && x3 > x1)
                        {
                            xi = x3;
                            hitPointCursor = i;
                            intersects = true;
                        }
                        else if (y1 == y4 && x4 > x1)
                        {
                            xi = x4;
                            hitPointCursor = next;
                            intersects = true;
                        }
                        else if (segmentsIntersect(x1, y1, x2, y2, x3, y3, x4, y4, xi, yi))
                        {
                            intersects = true;
                        }

                        double dist = (osg::Vec2d(xi, yi) - osg::Vec2d(x1, y1)).length();
                        if (intersects && dist < edgeDistance)
                        {
                            foundPointCursor = hitPointCursor;
                            edgeCursor = hitPointCursor != UINT_MAX ? hitPointCursor : (x3 >= x4 ? i : next);
                            edgeDistance = dist;
                        }
                    }
                }

                if (foundPointCursor == UINT_MAX && edgeCursor != UINT_MAX)
                {
                    // test for intersecting edges between x1 and x2
                    // (skipping the two segments for which edgeCursor is a vert)

                    double x2 = (*allPoints)[edgeCursor].x();
                    y2 = (*allPoints)[edgeCursor].y();

                    bool foundIntersection = false;
                    for (unsigned int i=0; i < allPoints->size(); i++)
                    {
                        unsigned int next = i == allPoints->size() - 1 ? 0 : i + 1;

                        if (i == edgeCursor || next == edgeCursor)
                          continue;

                        double x3 = (*allPoints)[i].x();
                        double y3 = (*allPoints)[i].y();
                        double x4 = (*allPoints)[next].x();
                        double y4 = (*allPoints)[next].y();

                        foundIntersection = foundIntersection || segmentsIntersect(x1, y1, x2, y2, x3, y3, x4, y4);

                        if (foundIntersection)
                        {
                            unsigned int prev = i == 0 ? allPoints->size() - 1 : i - 1;

                            if (!isCCW((*allPoints)[prev].x(), (*allPoints)[prev].y(), x3, y3, x4, y4))
                            {
                                edgeCursor = i;
                                x2 = (*allPoints)[edgeCursor].x();
                                y2 = (*allPoints)[edgeCursor].y();
                                foundIntersection = false;
                            }
                        }

                    }
                }

                if (edgeCursor != UINT_MAX)
                {
                    // build array of correctly ordered new points to add to the outer loop
                    osg::ref_ptr<osg::Vec3Array> insertPoints = new osg::Vec3Array();
                    insertPoints->reserve(holePoints->size() + 2);

                    unsigned int p = hCursor;
                    do
                    {
                        insertPoints->push_back((*holePoints)[p]);
                        p = p == holePoints->size() - 1 ? 0 : p + 1;
                    } while(p != hCursor);

                    insertPoints->push_back((*holePoints)[hCursor]);
                    insertPoints->push_back((*allPoints)[edgeCursor]);
                    
                    // insert new points into outer loop
                    osg::Vec3Array::iterator it = edgeCursor == allPoints->size() - 1 ? allPoints->end() : allPoints->begin() + (edgeCursor + 1);
                    allPoints->insert(it, insertPoints->begin(), insertPoints->end());
                }
            }
        }
    }
    
    GLenum mode = GL_LINE_LOOP;
    if ( osgGeom->getVertexArray() == 0L )
    {
        osgGeom->addPrimitiveSet( new osg::DrawArrays( mode, 0, allPoints->size() ) );
        osgGeom->setVertexArray( allPoints.get() );
    }
    else
    {
        osg::Vec3Array* v = static_cast<osg::Vec3Array*>(osgGeom->getVertexArray());
        osgGeom->addPrimitiveSet( new osg::DrawArrays( mode, v->size(), allPoints->size() ) );
        //v->reserve(v->size() + allPoints->size());
        std::copy(allPoints->begin(), allPoints->end(), std::back_inserter(*v));
    }

    //// Normal computation.
    //// Not completely correct, but better than no normals at all. TODO: update this
    //// to generate a proper normal vector in ECEF mode.
    ////
    //// We cannot accurately rely on triangles from the tessellation, since we could have
    //// very "degraded" triangles (close to a line), and the normal computation would be bad.
    //// In this case, we would have to average the normal vector over each triangle of the polygon.
    //// The Newell's formula is simpler and more direct here.
    //osg::Vec3 normal( 0.0, 0.0, 0.0 );
    //for ( size_t i = 0; i < poly->size(); ++i )
    //{
    //    osg::Vec3 pi = (*poly)[i];
    //    osg::Vec3 pj = (*poly)[ (i+1) % poly->size() ];
    //    normal[0] += ( pi[1] - pj[1] ) * ( pi[2] + pj[2] );
    //    normal[1] += ( pi[2] - pj[2] ) * ( pi[0] + pj[0] );
    //    normal[2] += ( pi[0] - pj[0] ) * ( pi[1] + pj[1] );
    //}
    //normal.normalize();

    //osg::Vec3Array* normals = new osg::Vec3Array();
    //normals->push_back( normal );
    //osgGeom->setNormalArray( normals );
    //osgGeom->setNormalBinding( osg::Geometry::BIND_OVERALL );
}