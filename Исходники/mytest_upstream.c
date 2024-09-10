static ngx_int_t
ngx_http_mytest_upstream_handler(ngx_http_request_t *r)
{
    
    //首先建立http上下文结构体ngx_http_mytest_ctx_t
    ngx_http_mytest_upstream_ctx_t* myctx = ngx_http_get_module_ctx(r, ngx_http_mytest_upstream_module);
    if (myctx == NULL)
    {
        myctx = ngx_palloc(r->pool, sizeof(ngx_http_mytest_upstream_ctx_t));
        if (myctx == NULL)
        {
            return NGX_ERROR;
        }
        
        //将新建的上下文与请求关联起来
        ngx_http_set_ctx(r, myctx, ngx_http_mytest_upstream_module);
    }
    
    //对每1个要使用upstream的请求，必须调用且只能调用1次
    //ngx_http_upstream_create方法，它会初始化r->upstream成员
    if (ngx_http_upstream_create(r) != NGX_OK)
    {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "ngx_http_upstream_create() failed");
        return NGX_ERROR;
    }

    //得到配置结构体ngx_http_mytest_conf_t
    ngx_http_mytest_upstream_conf_t  *mycf = (ngx_http_mytest_upstream_conf_t  *) ngx_http_get_module_loc_conf(r, ngx_http_mytest_upstream_module);
    ngx_http_upstream_t *u = r->upstream;
    //这里用配置文件中的结构体来赋给r->upstream->conf成员
    u->conf = &mycf->upstream;//把我们设置好的upstream配置信息赋值给ngx_http_request_t->upstream->conf
    //决定转发包体时使用的缓冲区
    u->buffering = mycf->upstream.buffering;

    //以下代码开始初始化resolved结构体，用来保存上游服务器的地址
    u->resolved = (ngx_http_upstream_resolved_t*) ngx_pcalloc(r->pool, sizeof(ngx_http_upstream_resolved_t));
    if (u->resolved == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "ngx_pcalloc resolved error. %s.", strerror(errno));
        return NGX_ERROR;
    }

    //这里的上游服务器就是www.google.com
    static struct sockaddr_in backendSockAddr;
    struct hostent *pHost = gethostbyname((char*) "www.sina.com");
    if (pHost == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "gethostbyname fail. %s", strerror(errno));
        
        ngx_log_debugall(r->connection->log, 0, "yang test ############################MYTEST upstream gethostbyname error\n");
        return NGX_ERROR;
    }
    
    //访问上游服务器的80端口
    backendSockAddr.sin_family = AF_INET;
    backendSockAddr.sin_port = htons((in_port_t) 80);
    char* pDmsIP = inet_ntoa(*(struct in_addr*) (pHost->h_addr_list[0]));
    //char* pDmsIP = inet_ntoa(*(struct in_addr*) ("10.10.0.2"));
    backendSockAddr.sin_addr.s_addr = inet_addr(pDmsIP);
    myctx->backendServer.data = (u_char*)pDmsIP;
    myctx->backendServer.len = strlen(pDmsIP);
    ngx_log_debugall(r->connection->log, 0, "yang test ############################MYTEST upstream gethostbyname OK, addr:%s\n", pDmsIP);

    //将地址设置到resolved成员中
    u->resolved->sockaddr = (struct sockaddr *)&backendSockAddr;
    u->resolved->socklen = sizeof(struct sockaddr_in);
    u->resolved->naddrs = 1;

    //设置三个必须实现的回调方法，也就是5.3.3节至5.3.5节中实现的3个方法
    u->create_request = mytest_upstream_create_request; //构造http请求行和头部行
    u->process_header = mytest_process_status_line;
    u->finalize_request = mytest_upstream_finalize_request;

    //这里必须将count成员加1，理由见5.1.5节
/*
这里还需要执行r->main->count++，这是在告诉HTTP框架将当前请求的引用计数加1，即告诉ngx_http_mytest_handler方法暂时不要销
毁请求，因为HTTP框架只有在引用计数为0时才能真正地销毁请求。这样的话，upstream机制接下来才能接管请求的处理工作。
*/
    r->main->count++;
    //启动upstream
    ngx_http_upstream_init(r);
    //必须返回NGX_DONE
    return NGX_DONE; //这时要通过返回NGX DONE告诉HTTP框架暂停执行请求的下一个阶段
}