redis_context_handle redisLibeventAttach(struct event_base *base, char *ip0, int port0, char *pwd, int db)
{

  struct redisLibeventEvents *e = NULL;
  redisAsyncContext *ac = NULL;

  char ip[256];
  if(ip0 && ip0[0])
	  STRCPY(ip,ip0);
  else
	  STRCPY(ip,"127.0.0.1");

  int port = DEFAULT_REDIS_PORT;
  if(port0>0)
	  port=port0;
  
  ac = redisAsyncConnect(ip, port);
  if (ac->err) {
  	fprintf(stderr,"Error: %s\n", ac->errstr);
  	return NULL;
  }

  /* Create container for context and r/w events */
  e = (struct redisLibeventEvents*)turn_malloc(sizeof(struct redisLibeventEvents));
  ns_bzero(e,sizeof(struct redisLibeventEvents));

  e->allocated = 1;
  e->context = ac;
  e->base = base;

  /* Register functions to start/stop listening for events */
  ac->ev.addRead = redisLibeventAddRead;
  ac->ev.delRead = redisLibeventDelRead;
  ac->ev.addWrite = redisLibeventAddWrite;
  ac->ev.delWrite = redisLibeventDelWrite;
  ac->ev.cleanup = redisLibeventCleanup;

  ac->ev.data = e;

  /* Initialize and install read/write events */
  e->rev = event_new(e->base,e->context->c.fd,
  		     EV_READ|EV_PERSIST,redisLibeventReadEvent,
  		     e);

  e->wev = event_new(e->base,e->context->c.fd,
		     EV_WRITE,redisLibeventWriteEvent,
  		     e);

  if (e->rev == NULL || e->wev == NULL) {
	  turn_free(e, sizeof(struct redisLibeventEvents));
	  return NULL;
  }
  
  event_add(e->wev, NULL);
  e->wev_set = 1;

  struct bufferevent *pair[2];

  bufferevent_pair_new(base, TURN_BUFFEREVENTS_OPTIONS, pair);
  e->in_buf = pair[0];
  e->out_buf = pair[1];
  bufferevent_setcb(e->in_buf, receive_message_for_redis, NULL, NULL, e);
  bufferevent_enable(e->in_buf, EV_READ);

  //Authentication
  if(pwd)
	  redisAsyncCommand(ac, NULL, e, "AUTH %s", pwd);

  if(db>0)
	  redisAsyncCommand(ac, NULL, e, "SELECT %d", db);

  return ac;
}