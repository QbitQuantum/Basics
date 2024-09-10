int main()
{
    printf("=====System Info=====\n");
    getSystemInfo();
    printf("=====IP Address=====\n");
    char ip[20];
    if (tools::getLocalIP_1(ip) == 0)
    {
        printf("Linux Socket get Local IP is: %s\n",ip);
    }
    else
    {
        printf("Linux Socket can't find Local IP\n");
    }

    char ip2[20];
    if (tools::getLocalIP_2(ip2) == 0)
    {
        printf("Boost asio get Local IP is: %s\n",ip2);
    }
    else
    {
        printf("Boost asio can't find Local IP\n");
    }
    printf("=====Data size=====\n");
    check_Data_size();
    return 0;
}