 void
 do_run()
 {
     try
     {
         beast::error_code ec;
         beast::flat_buffer buffer;
         for(;;)
         {
             http::request_parser<http::string_body> parser;
             parser.header_limit(8192);
             parser.body_limit(1024 * 1024);
             http::read(sock_, buffer, parser, ec);
             if(ec == http::error::end_of_stream)
                 break;
             if(ec)
                 throw beast::system_error{ec};
             do_request(parser.get(), ec);
             if(ec)
             {
                 if(ec != http::error::end_of_stream)
                     throw beast::system_error{ec};
                 break;
             }
         }
         sock_.shutdown(tcp::socket::shutdown_both, ec);
         if(ec && ec != boost::asio::error::not_connected)
             throw beast::system_error{ec};
     }
     catch (const std::exception& e)
     {
         std::cerr << "Exception: " << e.what() << std::endl;
     }
 }