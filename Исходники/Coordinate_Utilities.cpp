void Convert_Geographic_To_UTM( const double&       latitude_degrees,
                                const double&       longitude_degrees,
                                const std::string&  input_datum,
                                const int&          grid_zone,
                                const bool&         is_northern,
                                double&             easting_meters,
                                double&             northing_meters,
                                const std::string&  output_datum )
{
    // Create the Spatial Reference Objects
    OGRSpatialReference sourceSRS, targetSRS;

    sourceSRS.SetWellKnownGeogCS(  input_datum.c_str() );
    targetSRS.SetWellKnownGeogCS( output_datum.c_str() );

    // Configure the Projected Coordinate Components
    targetSRS.SetUTM( grid_zone,
                      is_northern );

    // Build the Transform Engine
    OGRCoordinateTransformation* transform;
    transform = OGRCreateCoordinateTransformation( &sourceSRS,
                                                   &targetSRS );
    
    easting_meters          = longitude_degrees;
    northing_meters         = latitude_degrees;
    double output_elevation_meters = 0;

    if( !transform->Transform( 1, &easting_meters,
                                  &northing_meters,
                                  &output_elevation_meters ) )
    {
        throw std::runtime_error("Transformation Failed.");
    }

    
    // Destroy the Transform
    OCTDestroyCoordinateTransformation( transform );
}