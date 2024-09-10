json::Node PreparedQueryBase::_refetchStringValue( const std::size_t index ){
    // These types which are of uncertain size we must fetch separately now that we know how much
    // space to allocate.
    MYSQL_BIND& binder = m_results[ index ];
    if( *binder.length == 0 ){
        return json::Node( "", "" );
    }

    // It is not empty, so create a new binder and copy over this one's values.
    MYSQL_BIND rightSizeBinder;
    memcpy( &rightSizeBinder, &binder, sizeof( MYSQL_BIND ) );
    rightSizeBinder.buffer          = new char[ (*binder.length) + 1 ];
    rightSizeBinder.buffer_length   = (*binder.length) + 1;

    // Now fetch the column with our right-sized buffer.
    try {
        mysql_stmt_fetch_column( m_statement, &rightSizeBinder, index, 0 );
        LW_MYSQL_STMT_CHECK_FOR_ERRORS( m_statement, "Failed to fetch column" );
    }
    catch( ... ){
        lw::util::safeDeleteArray( (char*&)rightSizeBinder.buffer );
        rethrow_exception( current_exception() );
    }

    // Now convert the value to a string JSON node, clean up, and return.
    json::Node node( "", string( (char*)rightSizeBinder.buffer, *rightSizeBinder.length ) );
    lw::util::safeDeleteArray( (char*&)rightSizeBinder.buffer );
    return node;
}