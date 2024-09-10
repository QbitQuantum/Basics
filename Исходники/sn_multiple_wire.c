void log_SNM_REQ( const n2n_SNM_REQ_t *req )
{
    int i;
    traceEvent( TRACE_DEBUG, "REQ Communities=%d", req->comm_num );
    if (req->comm_ptr)
    {
        for(i = 0; i < req->comm_num; i++)
        {
            traceEvent( TRACE_DEBUG, "\t[%d] len=%d name=%s", i,
                        req->comm_ptr[i].size, req->comm_ptr[i].name );
        }
    }
}