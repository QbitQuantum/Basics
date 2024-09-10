int P2PAccept(int Sockfd, struct sockaddr_in Dest, void(*Function) (void*), void* Arg){
    if(List != NULL){                                               //  如果链表为空
        LinkC_Debug("P2PAccept:LinkC Socket环境没有初始化",LINKC_FAILURE);
        return LINKC_FAILURE;                                       //  返回错误
    }
    LinkC_Socket *Socket = NULL;
    if(IsSocketInList(Sockfd,&Socket)==0){
        LinkC_Debug("P2PAccept:没有这个套接字",LINKC_FAILURE);
        return -1;
    }
    EmptyPackageList(Socket->RecvList);         //  清空发送和接收缓冲区
    EmptyPackageList(Socket->SendList); 
    SetDestAddr(Sockfd,Dest);
    int Length = _LCUDP_Package(NULL,0,Socket,CONNECTION_MESSAGE,Socket->SendBuffer);
    ___LinkC_Send(Socket,Socket->SendBuffer,Length,MSG_DONTWAIT);
    if(Function != NULL){                                   //  执行函数，这里是我发送了无用信息后向服务端确认
        Function(Arg);
    }
    Accept(Sockfd,Dest);
    
    return 0;
}