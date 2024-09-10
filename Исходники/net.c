void net_init( char *ip, int32_t remotePort, int32_t localPort )
{
    printf("Connecting to IP : %s , remote port %d , local port :%d\n", ip, remotePort,localPort);

    // Initialize SDL_net
    InitSDL_Net();
    OpenPort( localPort  );
    SetIPAndPort( ip, remotePort );
    CreatePacket( 512 );

}