static int init_server(tcp_listener_relay_server_type* server,
		       const char* ifname,
		       const char *local_address, 
		       int port, 
		       int verbose,
		       ioa_engine_handle e,
		       uint32_t *stats) {

  if(!server) return -1;

  server->stats=stats;

  if(ifname) STRCPY(server->ifname,ifname);

  if(make_ioa_addr((const u08bits*)local_address, port, &server->addr)<0) {
    return -1;
  }

  server->verbose=verbose;
  
  server->e = e;
  
  return create_server_listener(server);
}