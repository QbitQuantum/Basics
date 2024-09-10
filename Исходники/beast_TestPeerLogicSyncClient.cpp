void TestPeerLogicSyncClient::on_connect ()
{
    {
        // pre-handshake hook is optional
        on_pre_handshake ();
        if (failure (error ()))
            return ;
    }

    if (socket ().requires_handshake ())
    {
        if (failure (socket ().handshake (to_handshake_type (get_role ()), error ())))
            return;
    }

    {
        std::size_t const amount = boost::asio::write (
            socket (), boost::asio::buffer ("hello", 5), error ());

        if (failure (error ()))
            return;

        if (unexpected (amount == 5, error ()))
            return;
    }

    {
        char data [7];

        size_t const amount = boost::asio::read (
            socket (), boost::asio::buffer (data, 7), error ());

        if (failure (error ()))
            return;

        if (unexpected (amount == 7, error ()))
            return;

        if (unexpected (memcmp (&data, "goodbye", 7) == 0, error ()))
            return;
    }

    // Wait for 1 byte which should never come. Instead,
    // the server should close its end and we will get eof
    {
        char data [1];
        boost::asio::read (socket (), boost::asio::buffer (data, 1), error ());

        if (error () == boost::asio::error::eof)
        {
            error () = error_code ();
        }
        else if (unexpected (failure (error ()), error ()))
        {
            return;
        }
    }

    if (socket ().requires_handshake ())
    {
        if (failure (socket ().shutdown (error ()), true))
            return;
    }

    if (failure (socket ().shutdown (Socket::shutdown_both, error ())))
        return;

    if (failure (socket ().close (error ())))
        return;
}