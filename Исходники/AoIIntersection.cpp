OGRDataSource *AoIIntersection::intersectAoIWithLayers ( OGRDataSource *ogrSourceData, OGRPolygon *aoiPoly, IntersectionSummary *summary, const char *outFmt )
{
  OGRDataSource *ogrIntersection = NULL;

  // Spatial reference setup
  // make a spatial reference for the area of interest polygon
  OGRSpatialReference aoiRef;
  aoiRef.SetWellKnownGeogCS( "WGS84" );

  // make a spatial reference for the coord sys we will use to calculate area in acres - Albers USA equal area conic
  bool acreageCalcAvailable = true;
  char *aecWkt = "PROJCS[\"USA_Contiguous_Lambert_Conformal_Conic\",GEOGCS[\"GCS_North_American_1983\",DATUM[\"North_American_Datum_1983\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Lambert_Conformal_Conic_2SP\"],PARAMETER[\"False_Easting\",0],PARAMETER[\"False_Northing\",0],PARAMETER[\"Central_Meridian\",-96],PARAMETER[\"Standard_Parallel_1\",33],PARAMETER[\"Standard_Parallel_2\",45],PARAMETER[\"Latitude_Of_Origin\",39],UNIT[\"Meter\",1],AUTHORITY[\"EPSG\",\"102004\"]]";
  OGRSpatialReference aecRef;
  OGRErr ogrErr = aecRef.importFromWkt( &aecWkt );
  if ( ogrErr != OGRERR_NONE )
  {
    setError ( NO_SPATIAL_REFERENCE );
    acreageCalcAvailable = false;
  }

  // begin creating the output data structure
  // OGRDataSource is the root
  ogrIntersection = buildIntersectionDataSource( outFmt );
  if (! ogrIntersection )
  {
    setError( NO_OUTPUT_DATASOURCE );
    return 0;
  }

  int acreIndex = 0, areaIndex = 0;
  OGRFieldDefn *acreFldDefn = NULL, *areaPctFldDefn = NULL;
  OGRFeatureDefn *featureDefn = buildFeatureDefinition( acreIndex, areaIndex, acreFldDefn, areaPctFldDefn );

  // walk the layers in the input data
  //
  OGRLayer *inputLayer;
  summary->numLayers = ogrSourceData->GetLayerCount();

  for (int layerCt = 0; layerCt < summary->numLayers; ++layerCt)
  {
    inputLayer = ogrSourceData->GetLayer( layerCt );
    if ( inputLayer == NULL )
    {
      setError( NO_INPUT_LAYER );
      // clean up
      delete ogrIntersection;
      return 0;
    }
      
    // make a clone of aoi polygon to be manipulated
    OGRPolygon *aoiClone = (OGRPolygon *)aoiPoly->clone();
    if ( ! aoiClone )
    {
      setError( NO_AOI_CLONE );
      // clean up
      delete ogrIntersection;
      return 0;
    }

    // ensure that the area of interest polygon is in the same spatial reference as the data layer
    // find the spatial reference for the layer
    OGRSpatialReference *dataRef = inputLayer->GetSpatialRef();
    if ( dataRef )
    {
      OGRCoordinateTransformation *aoiTransform = OGRCreateCoordinateTransformation( &aoiRef, dataRef );
      if( aoiTransform == NULL )
      {
        setError( NO_AOI_TRANSFORM );
        // clean up
        delete ogrIntersection;
        delete aoiClone;
        return 0;
      }
      aoiClone->transform( aoiTransform );
      delete aoiTransform;
    }

    // find the transform from data layer's CS to Albers USA  
    // for acreage calculation
    OGRCoordinateTransformation *aecTransform = NULL;
    acreageCalcAvailable = false;
    if ( dataRef )
    {
      aecTransform = OGRCreateCoordinateTransformation( dataRef, &aecRef );
      if( aecTransform == NULL )
      {
        setError( NO_ACRE_TRANSFORM );
      }
      else
        acreageCalcAvailable = true;
    }

    // the area enclosed by the AoI
    // used for computing the percentage of the AoI intersected by polygons
    summary->aoiArea = aoiClone->getExteriorRing()->get_Area();

    // create a layer for outputting the intersecting polygons
    OGRLayer *intersectionLayer = ogrIntersection->CreateLayer( inputLayer->GetLayerDefn()->GetName(), dataRef, wkbPolygon, 0 );
    if ( ! intersectionLayer )
    {
      setError( NO_OUTPUT_LAYER );
      // clean up
      delete ogrIntersection;
      delete aoiClone;
      delete aecTransform;
      return 0;
    }

    // add fields to layer
    ogrErr = intersectionLayer->CreateField( acreFldDefn );
    if ( ogrErr != OGRERR_NONE )
    {
      setError( NO_ACRE_FIELD );
      // clean up
      delete ogrIntersection;
      delete aoiClone;
      delete aecTransform;
      return 0;
    }
    ogrErr = intersectionLayer->CreateField( areaPctFldDefn );
    if ( ogrErr != OGRERR_NONE )
    {
      setError( NO_AREA_FIELD );
      // clean up
      delete ogrIntersection;
      delete aoiClone;
      delete aecTransform;
      return 0;
    }

    // march through the geometry in the layer seeking overlap with area of interest
    //
    inputLayer->ResetReading();
    OGRFeature *inputFeature;
    while( (inputFeature = inputLayer->GetNextFeature()) != NULL )
    {
      // get the geometry part of the feature
      OGRGeometry *inputGeometry = inputFeature->GetGeometryRef();
      // test for polygon type - the only type we read
      if( inputGeometry != NULL 
        && wkbFlatten(inputGeometry->getGeometryType()) == wkbPolygon )
      {
        OGRPolygon *inputPolygon = (OGRPolygon *) inputGeometry;

        ++summary->totalInputPolyCt;
        double inputPolyArea = inputPolygon->get_Area();
        summary->totalInputPolyArea += inputPolyArea;

        // here's the important test - does this polygon intersect our area of interest?
        if (aoiClone->Intersects( inputGeometry ))
        {
          // generate a polygon that represents the intersection of the polygon with the AoI
          OGRGeometry *intersectionGeometry = aoiClone->Intersection( inputGeometry );

          if ( intersectionGeometry && wkbFlatten(intersectionGeometry->getGeometryType()) == wkbPolygon )
          {
            double intersectionArea = ((OGRPolygon *)intersectionGeometry)->get_Area();
            summary->totalIntersectionArea += intersectionArea;
            ++summary->intersectionCt;
            if (intersectionArea < inputPolyArea)
              ++summary->partEnclosedCt;

            // create a feature with feature definition, add geometry to it and add it to our layer
            OGRFeature *intersectionFeature = new OGRFeature( featureDefn );
            if (! intersectionFeature )
            {
              setError( NO_OUTPUT_FEATURE );
              // clean up
              delete ogrIntersection;
              delete aoiClone;
              delete aecTransform;
              return 0;
            }
            intersectionFeature->SetGeometry( intersectionGeometry );
            double percentOfAoI = intersectionArea / summary->aoiArea;
            intersectionFeature->SetField( areaIndex, percentOfAoI);
            summary->totalPercentOfAoI += percentOfAoI;

            if ( acreageCalcAvailable )
            {
              OGRGeometry *intersectionCopy = intersectionGeometry->clone();
              if ( intersectionCopy )
              {
                ogrErr = intersectionCopy->transform( aecTransform );
                if ( ogrErr != OGRERR_NONE )
                {
                  setError( NO_ACRE_TRANSFORMATION );
                  // clean up
                  delete ogrIntersection;
                  delete aoiClone;
                  delete aecTransform;
                  delete intersectionCopy;
                  return 0;
                }
                // get area in known metric CS
                double intersectionAcreage = ((OGRPolygon *)intersectionCopy)->get_Area();
                // convert sq m to acres
                double MetersToFt = 3.28084;
                double SqFtPerAcre = 43560.0;
                intersectionAcreage *= ((MetersToFt * MetersToFt) / SqFtPerAcre);
                intersectionFeature->SetField( acreIndex, intersectionAcreage );
                summary->totalIntersectionAcres += intersectionAcreage;
                delete intersectionCopy;
              }
              else
              {
                setError( NO_ACRE_OBJECT );
                // clean up
                delete ogrIntersection;
                delete aoiClone;
                delete aecTransform;
                return 0;
              }
            }
            intersectionLayer->CreateFeature( intersectionFeature );
            if ( ogrErr != OGRERR_NONE )
            {
              setError( NO_FEATURE_ADDED );
              // clean up
              delete ogrIntersection;
              delete aoiClone;
              delete aecTransform;
              return 0;
            }
          }
          else
          {
          }
        }
      }
      else
      {
        printf( "no polygon geometry\n" );
      }       
      OGRFeature::DestroyFeature( inputFeature );
    }
    delete aoiClone;
    delete aecTransform;
  }

  return ogrIntersection;
}