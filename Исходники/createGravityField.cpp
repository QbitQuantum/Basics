//! Function to read a gravity field file
std::pair< double, double  > readGravityFieldFile(
        const std::string& fileName, const int maximumDegree, const int maximumOrder,
        std::pair< Eigen::MatrixXd, Eigen::MatrixXd >& coefficients,
        const int gravitationalParameterIndex, const int referenceRadiusIndex )
{
    // Attempt to open gravity file.
    std::fstream stream( fileName.c_str( ), std::ios::in );
    if( stream.fail( ) )
    {
        boost::throw_exception(
                    std::runtime_error( "Pds gravity field data file could not be opened." ) );
    }

    // Declare variables for reading file.
    std::vector< std::string > vectorOfIndividualStrings;
    vectorOfIndividualStrings.resize( 4 );
    std::string line;


    double gravitationalParameter = TUDAT_NAN;
    double referenceRadius = TUDAT_NAN;

    if( ( gravitationalParameterIndex >= 0 ) &&
            ( referenceRadiusIndex >= 0 ) )
    {
        // Get first line of file.
        std::getline( stream, line );

        // Get reference radius and gravitational parameter from first line of file.
        boost::algorithm::trim( line );
        boost::algorithm::split( vectorOfIndividualStrings,
                                 line,
                                 boost::algorithm::is_any_of( "\t, " ),
                                 boost::algorithm::token_compress_on );
        if( gravitationalParameterIndex >= static_cast< int >( vectorOfIndividualStrings.size( ) ) ||
                referenceRadiusIndex >= static_cast< int >( vectorOfIndividualStrings.size( ) ) )
        {
            throw std::runtime_error( "Error when reading gravity field file, requested header index exceeds file contents" );
        }

        gravitationalParameter = boost::lexical_cast< double >( vectorOfIndividualStrings[ gravitationalParameterIndex ] );
        referenceRadius = boost::lexical_cast< double >( vectorOfIndividualStrings[ referenceRadiusIndex ] );
    }
    else if( ( !( gravitationalParameterIndex >= 0 ) &&
              ( referenceRadiusIndex >= 0 ) ) ||
             ( ( gravitationalParameterIndex >= 0 ) &&
                           !( referenceRadiusIndex >= 0 ) ) )
    {
        throw std::runtime_error( "Error when reading gravity field file, must retrieve either both or neither of Re and mu" );
    }


    // Declare variables for reading in cosine and sine coefficients.
    int currentDegree = 0, currentOrder = 0;
    Eigen::MatrixXd cosineCoefficients = Eigen::MatrixXd( maximumDegree + 1, maximumOrder + 1 );
    cosineCoefficients.setZero( );
    Eigen::MatrixXd sineCoefficients = Eigen::MatrixXd( maximumDegree + 1, maximumOrder + 1 );
    sineCoefficients.setZero( );

    // Read coefficients up to required maximum degree and order.
    while ( !stream.fail( ) && !stream.eof( ) &&
            ( currentDegree <= maximumDegree || currentOrder <= maximumOrder )  )
    {
        // Read current line
        std::getline( stream, line );

        // Trim input string (removes all leading and trailing whitespaces).
        boost::algorithm::trim( line );

        // Split string into multiple strings, each containing one element from a line from the
        // data file.
        boost::algorithm::split( vectorOfIndividualStrings,
                                 line,
                                 boost::algorithm::is_any_of( ", " ),
                                 boost::algorithm::token_compress_on );

        // Check current line for consistency
        if( vectorOfIndividualStrings.size( ) < 4 )
        {
            std::cerr<<"Error when reading pds gravity field file, number of fields is "
                    <<vectorOfIndividualStrings.size( )<<std::endl;
        }
        else
        {
            // Read current degree and orde from line.
            currentDegree = boost::lexical_cast< int >( vectorOfIndividualStrings[ 0 ] );
            currentOrder = boost::lexical_cast< int >( vectorOfIndividualStrings[ 1 ] );

            // Set cosine and sine coefficients for current degree and order.
            if( currentDegree <= maximumDegree && currentOrder <= maximumOrder )
            {
                cosineCoefficients( currentDegree, currentOrder ) =
                        boost::lexical_cast< double >( vectorOfIndividualStrings[ 2 ] );
                sineCoefficients( currentDegree, currentOrder ) =
                        boost::lexical_cast< double >( vectorOfIndividualStrings[ 3 ] );
            }
        }
    }

    // Set cosine coefficient at (0,0) to 1.
    cosineCoefficients( 0, 0 ) = 1.0;
    coefficients = std::make_pair( cosineCoefficients, sineCoefficients );

    return std::make_pair( gravitationalParameter, referenceRadius );
}