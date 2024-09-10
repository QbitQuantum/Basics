int32_t CoreUDPHandler::send(BinStream& bin_strm, const Inet_Addr& remote_addr)
{
    int32_t rc = sock_dgram_.send(bin_strm.get_rptr(), bin_strm.data_size(), remote_addr);
    if(rc < 0)
    {
        if(XEAGAIN == error_no() || XEINPROGRESS == error_no()) //插入一个写事件，防止SOCKET异常
        {
            CORE_WARNING("core udp send EAGAIN");
            REACTOR_INSTANCE()->register_handler(this, MASK_WRITE);

            bin_strm.rewind(true);
            return 0;
        }
        else
        {
            bin_strm.rewind(true);
            CORE_FATAL("core udp send failed, remote addr = " << remote_addr);
            return -1;
        }

        bin_strm.rewind(true);
    }

    THROTTLER()->add_udp_packet(bin_strm.data_size(), true);

    bin_strm.rewind(true);
    return rc;
}