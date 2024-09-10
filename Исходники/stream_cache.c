static int stream_cache_open (stream_wrapper_t * wrapper,char *stream_name)
{
    int ret = 0;
    stream_ctrl_t *info = &wrapper->info;
    memset(info,0,sizeof(*info));

    //open real stream
    stream_wrapper_t *real_st = (stream_wrapper_t *)wrapper->stream_priv;
    ret = real_st->open(real_st,stream_name);
    if(ret != DTERROR_NONE)
    {
        ret = DTERROR_FAIL;
        goto ERR0;
    }
    memcpy(info,&real_st->info,sizeof(stream_ctrl_t));
    
    // ctx
    //get buf size
    char value[512];
    int cache_size = DEFAULT_CACHE_SIZE;
    if(GetEnv("STREAM","stream.cachesize",value) > 0)
    {
        cache_size = atoi(value);
        dt_info(TAG,"cache size:%d \n",cache_size);
    }
    else
        dt_info(TAG,"cache size not set, use default:%d \n",cache_size);
    
    cache_ctx_t *ctx = (cache_ctx_t *)malloc(sizeof(cache_ctx_t));
    if(!ctx)
    {
        dt_info(TAG,"cache_ctx_t malloc failed, ret\n");
        ret = DTERROR_FAIL;
        goto ERR1;
    }
    memset(ctx,0,sizeof(cache_ctx_t));
    ctx->wrapper = real_st;
    
    // get tmp buffer
    ctx->cache = create_cache(cache_size,f_pre);
    if(!ctx->cache)
    {
        ret = DTERROR_FAIL;
        goto ERR2;
    }
    wrapper->stream_priv = ctx;

    //start read thread
    ret = create_cache_thread(ctx);
    if (ret == -1)
    {
        dt_error (TAG "file:%s [%s:%d] data fill thread start failed \n", __FILE__, __FUNCTION__, __LINE__);
        goto ERR3;
    }
    return DTERROR_NONE;
ERR3:
    release_cache(ctx->cache);
ERR2:
    free(ctx);
ERR1:
    real_st->close(real_st);
ERR0:
    return ret;
}