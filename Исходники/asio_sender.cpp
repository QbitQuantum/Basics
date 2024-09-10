void asio_sender::send(ana::detail::shared_buffer buffer ,
                       tcp::socket&               socket ,
                       ana::send_handler*         handler,
                       ana::detail::sender*       sender ,
                       ana::operation_id          op_id  )
{
    ana::timer* running_timer( NULL );
    try
    {
        if ( sender->timeouts_enabled() )
        {
            running_timer = sender->create_timer();

            sender->start_timer( running_timer, buffer,
                                boost::bind(&asio_sender::handle_send, this,
                                            boost::asio::placeholders::error, handler,
                                            running_timer, op_id, true ) );
        }

        stats_collector().start_send_packet(  buffer->size()
                                            + ( raw_mode() ? 0 : ana::HEADER_LENGTH ) );

        if ( raw_mode() )
        {
            socket.async_write_some( boost::asio::buffer(buffer->base(), buffer->size() ),
                                     boost::bind(&asio_sender::handle_partial_send,this,
                                                 buffer, boost::asio::placeholders::error,
                                                 &socket, handler, running_timer, 0, _2, op_id ));
        }
        else
        {
            ana::ana_uint32 size( buffer->size() );
            ana::host_to_network_long( size );

            ana::serializer::bostream* output_stream = new ana::serializer::bostream();
            (*output_stream) << size;

            //write the header first in a separate operation, then send the full buffer
            socket.async_write_some( boost::asio::buffer( output_stream->str() ),
                                     boost::bind(&asio_sender::handle_sent_header,this,
                                                 boost::asio::placeholders::error, output_stream,
                                                 &socket, buffer,
                                                 handler, running_timer, _2, op_id ));
        }
    }
    catch(const std::exception&)
    {
        disconnect();
        delete running_timer;
    }
}