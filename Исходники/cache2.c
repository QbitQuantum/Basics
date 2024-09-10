/**
 * \return 1 on success, 0 if the function was interrupted and -1 on error
 */
int stream_enable_cache(stream_t *stream,int64_t size,int64_t min,int64_t seek_limit){
  int ss = stream->sector_size ? stream->sector_size : STREAM_BUFFER_SIZE;
  int res = -1;
  cache_vars_t* s;

  if (stream->flags & STREAM_NON_CACHEABLE) {
    mp_msg(MSGT_CACHE,MSGL_STATUS,"\rThis stream is non-cacheable\n");
    return 1;
  }
  if (size > SIZE_MAX) {
    mp_msg(MSGT_CACHE, MSGL_FATAL, "Cache size larger than max. allocation size\n");
    return -1;
  }

  s=cache_init(size,ss);
  if(s == NULL) return -1;
  stream->cache_data=s;
  s->stream=stream; // callback
  s->seek_limit=seek_limit;


  //make sure that we won't wait from cache_fill
  //more data than it is allowed to fill
  if (s->seek_limit > s->buffer_size - s->fill_limit ){
     s->seek_limit = s->buffer_size - s->fill_limit;
  }
  if (min > s->buffer_size - s->fill_limit) {
     min = s->buffer_size - s->fill_limit;
  }
  // to make sure we wait for the cache process/thread to be active
  // before continuing
  if (min <= 0)
    min = 1;

#if FORKED_CACHE
  if((stream->cache_pid=fork())){
    if ((pid_t)stream->cache_pid == -1)
      stream->cache_pid = 0;
#else
  {
    stream_t* stream2=malloc(sizeof(stream_t));
    memcpy(stream2,s->stream,sizeof(stream_t));
    s->stream=stream2;
#if defined(__MINGW32__)
    stream->cache_pid = _beginthread( ThreadProc, 0, s );
#elif defined(__OS2__)
    stream->cache_pid = _beginthread( ThreadProc, NULL, 256 * 1024, s );
#else
    {
    pthread_t tid;
    pthread_create(&tid, NULL, ThreadProc, s);
    stream->cache_pid = 1;
    }
#endif
#endif
    if (!stream->cache_pid) {
        mp_msg(MSGT_CACHE, MSGL_ERR,
               "Starting cache process/thread failed: %s.\n", strerror(errno));
        goto err_out;
    }
    // wait until cache is filled at least prefill_init %
    mp_msg(MSGT_CACHE,MSGL_V,"CACHE_PRE_INIT: %"PRId64" [%"PRId64"] %"PRId64"  pre:%"PRId64"  eof:%d  \n",
	s->min_filepos,s->read_filepos,s->max_filepos,min,s->eof);
    while(s->read_filepos<s->min_filepos || s->max_filepos-s->read_filepos<min){
      /*
	mp_msg(MSGT_CACHE,MSGL_STATUS,MSGTR_CacheFill,
	100.0*(float)(s->max_filepos-s->read_filepos)/(float)(s->buffer_size),
	s->max_filepos-s->read_filepos
	);
      */
	if(s->eof) break; // file is smaller than prefill size
	if(stream_check_interrupt(PREFILL_SLEEP_TIME)) {
	  res = 0;
	  goto err_out;
        }
    }
    mp_msg(MSGT_CACHE,MSGL_STATUS,"\n");
    return 1; // parent exits

err_out:
    cache_uninit(stream);
    return res;
  }

#if FORKED_CACHE
  signal(SIGTERM,exit_sighandler); // kill
  cache_mainloop(s);
  // make sure forked code never leaves this function
  exit(0);
#endif
}

#if !FORKED_CACHE
#if defined(__MINGW32__) || defined(__OS2__)
static void ThreadProc( void *s ){
  cache_mainloop(s);
  _endthread();
}