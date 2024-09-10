//---------------------------------------------------
//    自动返回控制器器IP主函数
//---------------------------------------------------
//int main(int argc, char *argv[])
int configpalen_ipdetaup(void)
{
    int s_fd=0;
    int ret = 0;
    int i = 0;
    unsigned char sys_id[6];
    unsigned char buf[64];
    unsigned char request_buf[13];
    unsigned char h_ip[4];
    unsigned char s_ip[16];
    unsigned char s_gw[16];
    //unsigned char *ip="192.172.1.125";
    unsigned char setip[32] = "ifconfig eth0 ";
    int s_len = strlen(setip);

    unsigned char setgw[64] = "route add default gw ";
    int g_len = strlen(setgw);

    unsigned char k_ip[4];
    unsigned char smk[6];
    int sys_id_flag = 0;

    read_identifier(sys_id);//读取identifier.ini中保存的信息

    request_buf[0] = CAM_TYPE_TOP1;
    request_buf[1] = CAM_TYPE_TOP2;
    request_buf[2] = CAM_TYPE_REPLY;
    memcpy(request_buf+3, sys_id, 6);

    unsigned char versionbuf[2];

    //获取系统本身IP

    //ret = save_system_ip(ip, strlen(ip));

    ret = read_txt_ip(s_ip, h_ip);//读取systemip.ini中的信息
    if(ret < 0)
    {
        //获取文本的IP错误
        printf("read system ip file error!!!\n");
        GetIP_v4_and_v6_linux(AF_INET,s_ip,16);        //获取系统的IP
        ret = save_system_ip(s_ip, strlen(s_ip));
    }

    /*//printf("s_ip=%s\n",s_ip);
    memcpy(setip+s_len, s_ip, strlen(s_ip)+1);
    printf("set ip:%s\n",setip);

    system(setip);//还进行了设置。

    myread_txt_ip(s_gw, h_ip);
    memcpy(setgw+g_len, s_gw, strlen(s_gw)+1);
    printf("set gateway:%s\n",setgw);
    system(setgw);*/


    s_fd = make_send_multicast_init(s_ip);    //创建主播发送字符,只使用一个套接字也完全可以的。ghf

    socklen_t  len=sizeof(addr);
    extern int errno;

    static int val=0;



    cpufd = open("/dev/cpu_led",O_RDONLY);
    if (cpufd < 0)
    {
        system("insmod cpu_led.ko");
        sleep(2);
        cpufd = open("/dev/cpu_led",O_RDONLY);
        if (cpufd < 0){
            printf("error,open device cpu_led!!!\n");
        }
    }
    else{
        printf("open device cpu_led!!!\n");
    }

    //此接口走路由不行，但直连不同字段都可以
    struct sockaddr_in peeraddr;
    bzero(&peeraddr, sizeof(peeraddr));
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_port = htons(MUTIL_PORT);
    peeraddr.sin_addr.s_addr = inet_addr(MUTIL_ADDR);


    while(1)
    {
        //防止arm端ip被改
        GetIP_v4_and_v6_linux(AF_INET,s_ip,16);
        save_system_ip(s_ip, strlen(s_ip));

        val++;

        ret = recvfrom(s_fd, buf, 64, 0, (struct sockaddr*)&addr, &len);//最后一个参数的定义跟sendto不一样，注意！

        //printf("recvret=%d,buf[2]=%d\n",ret,buf[2]);
        if(ret == -1){
            printf("in configpalen_ipdetaup recvfrom error\n");
            break;
        }
        else
        {
            buf[ret]='\0';
            if(buf[2] == CAM_TYPE_REQUEST) //得到请求IP命令,mt500将ip地址和网卡地址发上去显示，收到后会发一个
                                            //CAM_TYPE_REPLY下来
            {
                printf("------1\n");
                read_txt_ip(s_ip, h_ip);
                memcpy(request_buf+9, h_ip, 4);

                versionbuf[0]=0x01;
                versionbuf[1]=0x01; //当前版本号为1.01 累计到1.10后，进到2.00。依次类推
                                    //版本更新内容用txt文档记录，交由上层显示

                memcpy(request_buf+13, versionbuf, 2);

                //以下判断条件不加也可以，因为如果没有链接的话,while一开始的地方recvfrom会阻塞,不会进到下面来发送
                ret=0;
                if(s_fd>0)
                    ret=sendto(s_fd,request_buf,15,0,(struct sockaddr *)&addr,sizeof(addr));
                //if(sfd>0)
                //    ret=sendto(sfd,request_buf,15,0,(struct sockaddr *)&peeraddr,sizeof(peeraddr));

                if(ret<0){
                    printf("errno=%d,---sendret=%d,%s\n",errno,ret,strerror(errno));
                    system("ifconfig eth0 192.172.1.85");
                    system("route add default gw 192.172.1.1");
                    ioctl(cpufd,0,0);
                }
                else{
                    printf("sendret=%d, ipaddr to serverok\n",ret);
                    if(val%2==0)
                        ioctl(cpufd,1,0);
                    else
                        ioctl(cpufd,0,0);
                }
            }
            else if(buf[2] == CAM_TYPE_MODIFY)    //得到设置IP命令,上层可以直接设置ip才行！2015-9-16
            {
                memcpy(smk, buf+3, 6);
                for(i = 0; i < 6; i+=1)
                {
                    if(smk[i] != sys_id[i])
                    {
                        sys_id_flag = 1;
                        break;
                    }
                }

                if(sys_id_flag == 0)
                {
                    memcpy(k_ip, buf+9, 4);
                    //printf("%02x %02x %02x %02x\n",k_ip[0],k_ip[1],k_ip[2],k_ip[3]);
                    if(k_ip[0] != 0x0)
                    {
                        //continue;
                        writ_txt_ip(k_ip);
                        read_txt_ip(s_ip,h_ip);

                        printf("sip:%s\n",s_ip);
                        memcpy(setip+s_len, s_ip, strlen(s_ip)+1);
                        //printf("set ip:%s\n",setip);
                        close(s_fd);
                        system(setip);

                        myread_txt_ip(s_gw, h_ip);
                        memcpy(setgw+g_len, s_gw, strlen(s_gw)+1);
                        printf("***********************\n");
                        printf("set gateway:%s\n",setgw);
                        printf("***********************\n");
                        system(setgw);

                        s_fd = make_send_multicast_init(s_ip);
                    }
                    //printf("================================================\n");
                }
            }
            else if(buf[2] == CAM_TYPE_REBOOT)        //得到请求重启控制器命令
            {
                //printf("------3\n");
                memcpy(smk, buf+3, 6);
                for(i = 0; i < 6; i+=1)
                {
                    if(smk[i] != sys_id[i])
                    {
                        sys_id_flag = 1;
                        break;
                    }
                }

                if(sys_id_flag == 0){
                    printf("reboot!!!!!!!!!!!!!!!!!!!\n");
                    system("reboot");
                }
            }
        }
        usleep(100000);
    }

    close(s_fd);
    return 0;
}