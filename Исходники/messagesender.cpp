void MessageSender::rawSocketSend( zmq::socket_t& a_socket, const std::string& a_name, const unsigned char* a_msg, size_t a_msgSize )
{
    bool ok = false;
    try
    {
        ok = a_socket.send( a_name.data(), a_name.size(), ZMQ_SNDMORE );
        ok = a_socket.send( a_msg, a_msgSize );
    }
    catch( const zmq::error_t& ex )
    {
        //std::cout << __PRETTY_FUNCTION__ << " " << ex.what() << std::endl;
    }
}