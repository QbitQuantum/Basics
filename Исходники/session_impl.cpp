        void SessionImpl::fetch_body( const size_t length, const shared_ptr< Session > session, const function< void ( const shared_ptr< Session >, const Bytes& ) >& callback ) const
        {
            const auto data_ptr = asio::buffer_cast< const Byte* >( session->m_pimpl->m_request->m_pimpl->m_buffer->data( ) );
            const auto data = Bytes( data_ptr, data_ptr + length );
            session->m_pimpl->m_request->m_pimpl->m_buffer->consume( length );
            
            auto& body = m_request->m_pimpl->m_body;
            
            if ( body.empty( ) )
            {
                body = data;
            }
            else
            {
                body.insert( body.end( ), data.begin( ), data.end( ) );
            }

            try
            {
                callback(session, data);
            }
            catch ( const int status_code )
            {
                const auto error_handler = session->m_pimpl->get_error_handler();
                error_handler( status_code, runtime_error( m_settings->get_status_message( status_code ) ), session );
            }
            catch ( const regex_error& re )
            {
                const auto error_handler = session->m_pimpl->get_error_handler();
                error_handler( 500, re, session );
            }
            catch ( const runtime_error& re )
            {
                const auto error_handler = session->m_pimpl->get_error_handler();
                error_handler( 400, re, session );
            }
            catch ( const exception& ex )
            {
                const auto error_handler = session->m_pimpl->get_error_handler();
                error_handler( 500, ex, session );
            }
            catch ( ... )
            {
                auto cex = current_exception( );

                if ( cex not_eq nullptr )
                {
                    try
                    {
                        rethrow_exception( cex );
                    }
                    catch ( const exception& ex )
                    {
                        const auto error_handler = session->m_pimpl->get_error_handler();
                        error_handler( 500, ex, session );
                    }
                    catch ( ... )
                    {
                        const auto error_handler = session->m_pimpl->get_error_handler();
                        error_handler( 500, runtime_error( "Internal Server Error" ), session );
                    }
                }
                else
                {
                    const auto error_handler = session->m_pimpl->get_error_handler();
                    error_handler( 500, runtime_error( "Internal Server Error" ), session );
                }
            }
        }