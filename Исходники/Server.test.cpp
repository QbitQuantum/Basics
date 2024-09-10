    bool
    connect (Socket& s, std::string const& addr, int port)
    {
        try
        {
            typename Socket::endpoint_type ep (
                boost::asio::ip::address::from_string (addr), port);
            s.connect (ep);
            pass();
            return true;
        }
        catch (std::exception const& e)
        {
            fail (e.what());
        }

        return false;
    }