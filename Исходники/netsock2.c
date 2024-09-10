char *ast_sockaddr_stringify_fmt(const struct ast_sockaddr *sa, int format)
{
	struct ast_sockaddr sa_ipv4;
	const struct ast_sockaddr *sa_tmp;
	char host[NI_MAXHOST];
	char port[NI_MAXSERV];
	struct ast_str *str;
	int e;
	static const size_t size = sizeof(host) - 1 + sizeof(port) - 1 + 4;


	if (ast_sockaddr_isnull(sa)) {
		return "(null)";
	}

	if (!(str = ast_str_thread_get(&ast_sockaddr_stringify_buf, size))) {
		return "";
	}

	if (ast_sockaddr_ipv4_mapped(sa, &sa_ipv4)) {
		sa_tmp = &sa_ipv4;
	} else {
		sa_tmp = sa;
	}

	if ((e = getnameinfo((struct sockaddr *)&sa_tmp->ss, sa_tmp->len,
			     format & AST_SOCKADDR_STR_ADDR ? host : NULL,
			     format & AST_SOCKADDR_STR_ADDR ? sizeof(host) : 0,
			     format & AST_SOCKADDR_STR_PORT ? port : 0,
			     format & AST_SOCKADDR_STR_PORT ? sizeof(port): 0,
			     NI_NUMERICHOST | NI_NUMERICSERV))) {
		ast_log(LOG_ERROR, "getnameinfo(): %s\n", gai_strerror(e));
		return "";
	}

	if ((format & AST_SOCKADDR_STR_REMOTE) == AST_SOCKADDR_STR_REMOTE) {
		char *p;
		if (ast_sockaddr_is_ipv6_link_local(sa) && (p = strchr(host, '%'))) {
			*p = '\0';
		}
	}

	switch ((format & AST_SOCKADDR_STR_FORMAT_MASK))  {
	case AST_SOCKADDR_STR_DEFAULT:
		ast_str_set(&str, 0, sa_tmp->ss.ss_family == AF_INET6 ?
				"[%s]:%s" : "%s:%s", host, port);
		break;
	case AST_SOCKADDR_STR_ADDR:
		ast_str_set(&str, 0, "%s", host);
		break;
	case AST_SOCKADDR_STR_HOST:
		ast_str_set(&str, 0,
			    sa_tmp->ss.ss_family == AF_INET6 ? "[%s]" : "%s", host);
		break;
	case AST_SOCKADDR_STR_PORT:
		ast_str_set(&str, 0, "%s", port);
		break;
	default:
		ast_log(LOG_ERROR, "Invalid format\n");
		return "";
	}

	return ast_str_buffer(str);
}