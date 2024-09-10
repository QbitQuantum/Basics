/* parses:
 *     tcp|udp|unix:host_name:port
 *     tcp|udp|unix:host_name
 *     host_name:port
 *     host_name
 * 
 *
 *     where host_name=string, ipv4 address, [ipv6 address],
 *         unix socket path (starts with '/')
 */
struct id_list* parse_listen_id(char* l, int len, enum socket_protos def)
{
	char* p;
	enum socket_protos proto;
	char* name;
	char* port_str;
	int port;
	int err;
	struct servent* se;
	char* s;
	struct id_list* id;
	
	s=pkg_malloc((len+1)*sizeof(char));
	if (s==0){
		LOG(L_ERR, "ERROR:parse_listen_id: out of memory\n");
		goto error;
	}
	memcpy(s, l, len);
	s[len]=0; /* null terminate */
	
	/* duplicate */
	proto=UNKNOWN_SOCK;
	port=0;
	name=0;
	port_str=0;
	p=s;
	
	if ((*p)=='[') goto ipv6;
	/* find proto or name */
	for (; *p; p++){
		if (*p==':'){
			*p=0;
			if (strcasecmp("tcp", s)==0){
				proto=TCP_SOCK;
				goto find_host;
			}else if (strcasecmp("udp", s)==0){
				proto=UDP_SOCK;
				goto find_host;
			}else if (strcasecmp("unixd", s)==0){
				proto=UNIXD_SOCK;
				goto find_host;
			}else if ((strcasecmp("unix", s)==0)||(strcasecmp("unixs", s)==0)){
				proto=UNIXS_SOCK;
				goto find_host;
#ifdef USE_FIFO
			}else if (strcasecmp("fifo", s)==0){
				proto=FIFO_SOCK;
				goto find_host;
#endif
			}else{
				proto=UNKNOWN_SOCK;
				/* this might be the host */
				name=s;
				goto find_port;
			}
		}
	}
	name=s;
	goto end; /* only name found */
find_host:
	p++;
	if (*p=='[') goto ipv6;
	name=p;
	for (; *p; p++){
		if ((*p)==':'){
			*p=0;
			goto find_port;
		}
	}
	goto end; /* nothing after name */
ipv6:
	name=p;
	p++;
	for(;*p;p++){
		if(*p==']'){
			if(*(p+1)==':'){
				p++; *p=0;
				goto find_port;
			}else if (*(p+1)==0) goto end;
		}else{
			goto error;
		}
	}
	
find_port:
	p++;
	port_str=(*p)?p:0;
	
end:
	/* fix all the stuff */
	if (name==0) goto error;
	if (proto==UNKNOWN_SOCK){
		/* try to guess */
		if (port_str){
			switch(def){
				case TCP_SOCK:
				case UDP_SOCK:
					proto=def;
					break;
				default:
					proto=UDP_SOCK;
					DBG("guess:%s is a tcp socket\n", name);
			}
		}else if (name && strchr(name, '/')){
			switch(def){
				case TCP_SOCK:
				case UDP_SOCK:
					DBG("guess:%s is a unix socket\n", name);
					proto=UNIXS_SOCK;
					break;
				default:
					/* def is filename based => use default */
					proto=def;
			}
		}else{
			/* using default */
			proto=def;
		}
	}
	if (port_str){
		port=str2s(port_str, strlen(port_str), &err);
		if (err){
			/* try getservbyname */
			se=getservbyname(port_str, 
					(proto==TCP_SOCK)?"tcp":(proto==UDP_SOCK)?"udp":0);
			if (se) port=ntohs(se->s_port);
			else goto error;
		}
	}else{
		/* no port, check if the hostname is a port 
		 * (e.g. tcp:3012 == tcp:*:3012 */
		if (proto==TCP_SOCK|| proto==UDP_SOCK){
			port=str2s(name, strlen(name), &err);
			if (err){
				port=0;
			}else{
				name="*"; /* inaddr any  */
			}
		}
	}
	id=pkg_malloc(sizeof(struct id_list));
	if (id==0){
		LOG(L_ERR, "ERROR:parse_listen_id: out of memory\n");
		goto error;
	}
	id->name=name;
	id->proto=proto;
	id->data_proto=P_BINRPC;
	id->port=port;
	id->buf=s;
	id->next=0;
	return id;
error:
	if (s) pkg_free(s);
	return 0;
}