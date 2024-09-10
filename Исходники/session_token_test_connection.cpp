void au::SessionTokenTestConnection::HandleContentRead(
        const std::size_t bytes_transferred,
        const boost::system::error_code& ec
    )
{
    if (ec)
    {
        std::cout << "Read content: Got error: " << ec.message() << std::endl;
        request_->Fail(HttpStatusCode::bad_request);
        return;
    }

    auto handler_it = handlers_->find( request_->path );
    if ( handler_it == handlers_->end() )
    {
        std::cout << "Server error: no handler for path: " << request_->path
            << std::endl;
        request_->Fail(HttpStatusCode::not_found);
        return;
    }

    std::istream response_stream(&request_->read_buffer_);

    std::string line;
    if( std::getline(response_stream, line) )
    {
        boost::trim_right(line);
        if ( ! line.empty() )
        {
            request_->post = line;

            std::vector<std::string> post_parts;
            boost::split(
                post_parts,
                line,
                boost::is_any_of("&"));

            for ( const std::string & part : post_parts )
            {
                std::vector<std::string> key_pair;
                boost::split(
                    key_pair,
                    part,
                    boost::is_any_of("="));

                boost::optional<std::string> key = post_parameter::Decode(
                    key_pair[0] );
                if ( ! key )
                {
                    std::cout << "Got invalid POST data." << std::endl;
                    request_->Fail(HttpStatusCode::bad_request);
                    return;
                }

                if (key_pair.size() > 1)
                {
                    boost::optional<std::string> value = post_parameter::Decode(
                        key_pair[1] );
                    if ( ! value )
                    {
                        std::cout << "Got invalid POST data." << std::endl;
                        request_->Fail(HttpStatusCode::bad_request);
                        return;
                    }

                    request_->post_parts[*key] = *value;
                }
                else
                {
                    request_->post_parts[*key] = "";
                }
            }
        }
    }

    // Execute the handler.
    (handler_it->second)(std::move(request_));
}