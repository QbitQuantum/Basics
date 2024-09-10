int StrcatfHttpResponseBuffer( struct HttpEnv *e , char *format , ... )
{
	va_list		valist ;
	long		size ;
	int		len ;
	int		nret = 0 ;
	
	size = e->rsp_buf->bufsize - e->rsp_buf->len - 1 ;
	
	while(1)
	{
		va_start( valist , format );
		len = VSNPRINTF( e->rsp_buf->ptr , size , format , valist ) ;
		va_end( valist );
		
		if( len == -1 || len == size )
		{
			nret = ReallocHttpBuffer( e->rsp_buf , e->rsp_buf->bufsize * 2 ) ;
			if( nret )
				return nret;
		}
		else
		{
			break;
		}
	}
	
	e->rsp_buf->ptr += len ;
	e->rsp_buf->len += len ;
	
	return 0;
}