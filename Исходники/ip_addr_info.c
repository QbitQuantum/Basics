//获得ip所属地理信息,isp
int getipinfo(char *ipstr,localtmp *p_loc)
{
    if (p_share == NULL){
        perror("openshare...");
        return -1;
    }

    char *pos = p_share;
    int record_len=10;
    char *firstip=0;
    //把ip转为整数
    unsigned int ip=htonl(inet_addr(ipstr));
    firstip=p_begin; // first record position

    int l=0;
    int u=total_record;
    int i=0;
    char* findip=firstip;
    unsigned int beginip=0;
    unsigned int endip=0;
    //二分法查找
    while(l <= u)
    {
        i=(l+u)/2;
        pos=firstip+i*RECORD_LEN;
        beginip = getlong4(pos);
        pos+=4;
        if(ip<beginip)
        {
            u=i-1;    
        }
        else
        {
            endip=getlong4(p_share+getlong3(pos));
            if(ip>endip)
            {
                l=i+1;        
            }
            else
            {
                findip=firstip+i*RECORD_LEN;
                break;    
            }
        }
    }
    int offset = getlong3(findip+4);
    pos=p_share+offset;
    endip= getlong4(pos); // 用户IP所在范围的结束地址
    pos+=4;

    unsigned int j=ntohl(beginip);
    inet_ntop(AF_INET,&j,p_loc->beginip, INET6_ADDRSTRLEN);// 获得开始地址的IP字符串类型
    j=ntohl(endip);
    inet_ntop(AF_INET,&j,p_loc->endip, INET6_ADDRSTRLEN);// 获得结束地址的IP字符串类型

    char *byte = pos; // 标志字节
    pos++;
    switch (*byte) {
        case 1:{ // 标志字节为1，表示国家和区域信息都被同时重定向
                   int countryOffset = getlong3(pos); // 重定向地址
                   pos+=3;
                   pos=p_share+countryOffset;
                   byte = pos; // 标志字节
                   pos++;
                   switch (*byte) {
                       case 2: // 标志字节为2，表示国家信息又被重定向
                           {
                               p_loc->p_country=p_share+getlong3(pos);
                               pos=p_share+countryOffset+4;
                               p_loc->p_area = getarea(pos);
                           }
                           break;
                       default: // 否则，表示国家信息没有被重定向
                           {
                               p_loc->p_country=byte;
                               p_loc->p_area = getarea(p_loc->p_country+strlen(p_loc->p_country)+1);
                           }
                           break;
                   }
               }
               break;
        case 2: // 标志字节为2，表示国家信息被重定向
               {
                   p_loc->p_country=p_share+getlong3(pos);// 重定向地址
                   pos = p_share + offset + 8;
                   p_loc->p_area = getarea(pos);
               }
               break;
        default:{ // 否则，表示国家信息没有被重定向
                    p_loc->p_country=byte;
                    p_loc->p_area=getarea(p_loc->p_country+strlen(p_loc->p_country)+1);
                }
                break;
    }

    //printf("%s  %s\n", p_loc->p_country, p_loc->p_area);
    return 0;
}