void OutputStream::compress( std::ostream* ostream )
{
    _fields.clear();
    if ( !isBinary() ) return;
    
    std::stringstream schemaSource;
    if ( _useSchemaData )
    {
        _fields.push_back( "SchemaData" );
        
        std::string schemaData;
        for ( std::map<std::string, std::string>::iterator itr=_inbuiltSchemaMap.begin();
              itr!=_inbuiltSchemaMap.end(); ++itr )
        {
            schemaData += itr->first + '=';
            schemaData += itr->second;
            schemaData += '\n';
        }
        
        int size = schemaData.size();
        schemaSource.write( (char*)&size, INT_SIZE );
        schemaSource.write( schemaData.c_str(), size );
        
        _inbuiltSchemaMap.clear();
        _fields.pop_back();
    }
    
    if ( !_compressorName.empty() )
    {
        _fields.push_back( "Compression" );
        BaseCompressor* compressor = Registry::instance()->getObjectWrapperManager()->findCompressor(_compressorName);
        if ( !compressor || !ostream )
        {
            _fields.pop_back();
            return;
        }
        
        if ( !compressor->compress(*ostream, schemaSource.str() + _compressSource.str()) )
            throwException( "OutputStream: Failed to compress stream." );
        if ( getException() ) return;
        _fields.pop_back();
    }
    else if ( _useSchemaData )
    {
        std::string str = schemaSource.str() + _compressSource.str();
        ostream->write( str.c_str(), str.size() );
    }
}