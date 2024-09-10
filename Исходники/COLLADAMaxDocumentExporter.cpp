    //---------------------------------------------------------------
    String DocumentExporter::getEnvironmentVariable ( const String & variableName )
    {
        char * buffer;
        size_t numberOfElements;
        errno_t error = _dupenv_s ( &buffer, &numberOfElements, variableName.c_str() );

        if ( error != 0 )
        {
            free ( buffer );
            return String();
        }

        String variableValue ( buffer, numberOfElements-1 );

        free ( buffer );
        return variableValue;
    }