bool DHCPOptionParser::Parse( struct dhcp_packet *dp )
{
    int code;
    int len;
    unsigned char *data;
    int i, j;

    if( memcmp( dp->options, DHCP_OPTIONS_COOKIE, 4 ))
        return false;

    Free();

    for( i = 4; ( code = dp->options[ i++ ]) != DHO_END; )
    {
        if( code == DHO_PAD )
            continue;

        len  = dp->options[ i++ ];
        data = &dp->options[ i ];

        switch( code )
        {
            case DHO_DHCP_MESSAGE_TYPE :
                mMsgType = *data;
                break;

            case DHO_DHCP_SERVER_IDENTIFIER :
                mSID = *reinterpret_cast< struct in_addr * >( data );
                break;

            case DHO_DHCP_LEASE_TIME :
                mLeaseTime = *reinterpret_cast< u_int32_t * >( data );
                break;

            case DHO_SUBNET_MASK :
                mSubnetMask = *reinterpret_cast< struct in_addr * >( data );
                break;

            case DHO_ROUTERS :
            {
                mRouterCount = static_cast< u_int8_t >( len / 4 );
                mRouterList  = new struct in_addr[ mRouterCount ];
                for( j = 0; j < len; j += 4 )
                    mRouterList[ j / 4 ] = *reinterpret_cast
                                                < struct in_addr *>
                                                    ( &data[ j ]);
                break;
            }

            case DHO_DOMAIN_NAME_SERVERS :
            {
                mDNSCount = static_cast< u_int8_t >( len / 4 );
                mDNSList  = new struct in_addr[ mDNSCount ];
                for( j = 0; j < len; j += 4 )
                    mDNSList[ j / 4 ] = *reinterpret_cast
                                            < struct in_addr *>( &data[ j ]);
                break;
            }

            case DHO_DOMAIN_NAME :
                mDomainName = new char[ len + 1 ]();
                memcpy( mDomainName, data, len );
                break;
        }

        i += len;
    }

    return true;
}