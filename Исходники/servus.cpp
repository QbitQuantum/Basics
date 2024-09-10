    bool announce( const unsigned short port, const std::string& instance )
    {
#ifdef LUNCHBOX_USE_DNSSD
        if( service_ )
            return false;

        TXTRecordRef record;
        createTXTRecord_( record );

        const DNSServiceErrorType error =
            DNSServiceRegister( &service_, 0 /* flags */,
                                0 /* all interfaces */,
                                instance.empty() ? 0 : instance.c_str(),
                                name_.c_str(), 0 /* default domains */,
                                0 /* hostname */, htons( port ),
                                TXTRecordGetLength( &record ),
                                TXTRecordGetBytesPtr( &record ),
                                (DNSServiceRegisterReply)registerCBS_,
                                this );
        TXTRecordDeallocate( &record );

        if( error == kDNSServiceErr_NoError )
        {
            handleEvents_( service_ );
            return service_ != 0;
        }

        LBWARN << "DNSServiceRegister returned: " << error << std::endl;
#endif
        return false;
    }