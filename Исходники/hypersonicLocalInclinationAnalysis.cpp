//! Determine moment coefficients from pressure coefficients.
Eigen::Vector3d HypersonicLocalInclinationAnalysis::calculateMomentCoefficients(
        const int partNumber )
{
    // Declare moment coefficient vector and intialize to zeros.
    Eigen::Vector3d momentCoefficients = Eigen::Vector3d::Zero( );

    // Declare moment arm for panel moment determination.
    Eigen::Vector3d referenceDistance ;

    // Loop over all panels and add moments due pressures.
    for ( int i = 0 ; i < vehicleParts_[ partNumber ]->getNumberOfLines( ) - 1 ; i++ )
    {
        for ( int j = 0 ; j < vehicleParts_[ partNumber ]->getNumberOfPoints( ) - 1 ; j++ )
        {
            // Determine moment arm for given panel centroid.
            referenceDistance = ( vehicleParts_[ partNumber ]->
                                  getPanelCentroid( i, j ) -  momentReferencePoint_ );

            momentCoefficients -=
                    pressureCoefficient_[ partNumber ][ i ][ j ] *
                    vehicleParts_[ partNumber ]->getPanelArea( i, j ) *
                    ( referenceDistance.cross( vehicleParts_[ partNumber ]->
                                               getPanelSurfaceNormal( i, j ) ) );
        }
    }

    // Scale result by reference length and area.
    momentCoefficients /= ( referenceLength_ * referenceArea_ );

    return momentCoefficients;
}