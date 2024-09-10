void TestGetHostByName()
{
    const char *host = "www.baidu.com";
    in_addr in_addr;
    bool ret = GetHostByName(host, &in_addr);
    if (!ret)
    {
        printf("resolveHost error");
    }
    else
    {
        printf("IP Address: %s\n",inet_ntoa(in_addr));
    }
}