bool StrangeNNGene::saveGene( std::wstring const& filename )
{
    FILE* pFile = _wfopen( filename.c_str(), L"wb" );
    if ( NULL == pFile )
        return false;

    // Write the file header
    fwrite( GENEFILE_HEADER, 1, strlen( GENEFILE_HEADER ), pFile );

    // Write the generation count
    {
        char buff[80];
        itoa( geneGeneration_, buff, 10 );
        fwrite( buff, 1, strlen( buff ), pFile );
    }

    // For every layer
    GeneData::iterator neuronIt = data_.begin();
    for ( ; neuronIt != data_.end(); ++neuronIt )
    {
        fwrite( GENEFILE_TOKEN_NEURON, 1, 1, pFile );
        // For every dendrite
        Neuron::iterator dendriteIt = neuronIt->begin();
        for ( ; dendriteIt != neuronIt->end(); ++dendriteIt )
        {
            fwrite( GENEFILE_TOKEN_DENDRITE, 1, 1, pFile );
            char buff[80];
            itoa( dendriteIt->first, buff, 10 );
            fwrite( buff, 1, strlen( buff ), pFile );
            fwrite( GENEFILE_TOKEN_COMMA, 1, 1, pFile );
            itoa( dendriteIt->second, buff, 10 );
            fwrite( buff, 1, strlen( buff ), pFile );
        }
    }

    fclose( pFile );
    return true;
}