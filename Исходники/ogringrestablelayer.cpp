OGRErr OGRIngresTableLayer::PrepareNewStyleGeometry(
    OGRGeometry *poGeom, CPLString &osRetGeomText )

{
	OGRErr eErr = OGRERR_NONE;
    osRetGeomText = "";

    if( poGeom == NULL )
        return OGRERR_FAILURE;

/* -------------------------------------------------------------------- */
/*      Point                                                           */
/* -------------------------------------------------------------------- */
    if( wkbFlatten(poGeom->getGeometryType()) == wkbPoint )
    {
        osRetGeomText.Printf( "POINTFROMWKB( ~V )");
    }
/* -------------------------------------------------------------------- */
/*      Linestring                                                      */
/* -------------------------------------------------------------------- */
    else if( wkbFlatten(poGeom->getGeometryType()) == wkbLineString )
    {
        osRetGeomText.Printf("LINEFROMWKB( ~V )");
    }
/* -------------------------------------------------------------------- */
/*      Polygon                                                         */
/* -------------------------------------------------------------------- */
    else if( wkbFlatten(poGeom->getGeometryType()) == wkbPolygon )
    {
        osRetGeomText.Printf("POLYFROMWKB( ~V )");
    }
/* -------------------------------------------------------------------- */
/*      Multipoint                                                      */
/* -------------------------------------------------------------------- */
    else if( wkbFlatten(poGeom->getGeometryType()) == wkbMultiPoint )
    {
        osRetGeomText.Printf("MPOINTFROMWKB( ~V )");
    }
/* -------------------------------------------------------------------- */
/*      Multilinestring                                                 */
/* -------------------------------------------------------------------- */
    else if( wkbFlatten(poGeom->getGeometryType()) == wkbMultiLineString )
    {
    	osRetGeomText.Printf("MLINEFROMWKB( ~V )");
    }
/* -------------------------------------------------------------------- */
/*      Multipolygon                                                    */
/* -------------------------------------------------------------------- */
    else if( wkbFlatten(poGeom->getGeometryType()) == wkbMultiPolygon )
    {
    	osRetGeomText.Printf("MPOLYFROMWKB( ~V )");
    }
    else
    {
        eErr = OGRERR_FAILURE;
    }

    return eErr;
}