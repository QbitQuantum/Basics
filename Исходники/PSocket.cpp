int Socket_accept(Context* ctx, Value& self)
{
    Socket* socket = static_cast<Socket*>(self.val.object);
    Socket* retSock = 0;
    SocketAddress* retAddr = 0;
    if (socket->Accept(&retSock, &retAddr)) {
        ctx->Push(retSock);
        ctx->Push(retAddr);
    } else {
        ctx->PushNull();
        ctx->PushNull();
    }
    return 2;
}