qint64 vsocketDispatcher( char * _buf, const qint64 _len,
                                const SocketOpCodes _op_code, void * _user )
{
	VSocket * sock = static_cast<VSocket *>( _user );
	switch( _op_code )
	{
		case SocketRead: return( sock->ReadExact( _buf, _len ) ?
								_len : 0 );
		case SocketWrite: return( sock->SendExact( _buf, _len ) ?
								_len : 0 );
		case SocketGetPeerAddress:
			strncpy( _buf, sock->GetPeerName(), _len );
			return( 0 );
	}
	return( 0 );

}