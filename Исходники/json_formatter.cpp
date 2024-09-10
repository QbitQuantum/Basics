json JSONFormatter::compose_object( const Resource& value ) const
{
    auto object = json::object( );
    
    for ( auto iterator = value.begin( ); iterator not_eq value.end( ); iterator++ )
    {
        auto iterators = value.equal_range( iterator->first );
        const auto length = distance( iterators.first, iterators.second );
        
        if ( length > 1 )
        {
            auto items = json::array( );
            
            for ( auto item = iterators.first; item not_eq iterators.second; item++ )
            {
                auto field = String::to_string( item->second );
                
                if ( String::is_boolean( field ) )
                {
                    items.push_back( String::lowercase( field ) == "true" );
                }
                else if ( String::is_integer( field ) )
                {
                    try
                    {
                        items.push_back( stol( field ) );
                    }
                    catch ( const out_of_range& )
                    {
                        items.push_back( field );
                    }
                }
                else if ( String::is_fraction( field ) )
                {
                    try
                    {
                        items.push_back( stod( field ) );
                    }
                    catch ( const out_of_range& )
                    {
                        items.push_back( field );
                    }
                }
                else
                {
                    items.push_back( field );
                }
            }
            
            object[ iterator->first ] = items;
            
            advance( iterator, length - 1 );
        }
        else
        {
            auto field = String::to_string( iterator->second );
            
            if ( String::is_boolean( field ) )
            {
                object[ iterator->first ] = ( String::lowercase( field ) == "true" );
            }
            else if ( String::is_integer( field ) )
            {
                try
                {
                    object[ iterator->first ] = stol( field );
                }
                catch ( const out_of_range& )
                {
                    object[ iterator->first ] = field;
                }
            }
            else if ( String::is_fraction( field ) )
            {
                try
                {
                    object[ iterator->first ] = stod( field );
                }
                catch ( const out_of_range& )
                {
                    object[ iterator->first ] = field;
                }
            }
            else
            {
                object[ iterator->first ] = field;
            }
        }
    }
    
    return object;
}