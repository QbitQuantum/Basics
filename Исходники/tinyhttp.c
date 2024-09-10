void accept_request(int client)  
{  
    char buf[1024];  
    int numchars;  
    char method[255];  
    char url[255];  
    char path[512];  
    size_t i, j;  
    struct stat st;  
    int cgi = 0;      /* becomes true if server decides this is a CGI program */  
    char *query_string = NULL;  
  
    /*得到请求的第一行*/  
    numchars = get_line(client, buf, sizeof(buf));  
    i = 0; j = 0;  
    /*把客户端的请求方法存到 method 数组*/  
    while (!ISspace(buf[j]) && (i < sizeof(method) - 1))  
    {  
        method[i] = buf[j];  
        i++; j++;  
    }  
    method[i] = '\0';  
  
    /*如果既不是 GET 又不是 POST 则无法处理 */  
    if (strcasecmp(method, "GET") && strcasecmp(method, "POST"))  
    {  
        unimplemented(client);  
        return;  
    }  
  
    /* POST 的时候开启 cgi */  
    if (strcasecmp(method, "POST") == 0)  
        cgi = 1;  
  
    /*读取 url 地址*/  
    i = 0;  
    while (ISspace(buf[j]) && (j < sizeof(buf)))  
        j++;  
    while (!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf)))  
    {  
        /*存下 url */  
        url[i] = buf[j];  
        i++; j++;  
    }  
    url[i] = '\0';  
  
    /*处理 GET 方法*/  
    if (strcasecmp(method, "GET") == 0)  
    {  
        /* 待处理请求为 url */  
        query_string = url;  
        while ((*query_string != '?') && (*query_string != '\0'))  
            query_string++;  
        /* GET 方法特点，? 后面为参数*/  
        if (*query_string == '?')  
        {  
            /*开启 cgi */  
            cgi = 1;  
            *query_string = '\0';  
            query_string++;  
        }  
    }  
  
    /*格式化 url 到 path 数组，html 文件都在 htdocs 中*/  
    sprintf(path, "htdocs%s", url);  
    /*默认情况为 index.html */  
    if (path[strlen(path) - 1] == '/')  
        strcat(path, "index.html");  
    /*根据路径找到对应文件 */  
    if (stat(path, &st) == -1) {  
        /*把所有 headers 的信息都丢弃*/  
        while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */  
            numchars = get_line(client, buf, sizeof(buf));  
        /*回应客户端找不到*/  
        not_found(client);  
    }  
    else  
    {  
        /*如果是个目录，则默认使用该目录下 index.html 文件*/  
        if ((st.st_mode & S_IFMT) == S_IFDIR)  
            strcat(path, "/index.html");  
      if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH)    )  
          cgi = 1;  
      /*不是 cgi,直接把服务器文件返回，否则执行 cgi */  
      if (!cgi)  
          serve_file(client, path);  
      else  
          execute_cgi(client, path, method, query_string);  
    }  
  
    /*断开与客户端的连接（HTTP 特点：无连接）*/  
    close(client);  
}  