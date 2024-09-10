void ConnectionManagerIn::execute(void * arg)
{
    ConnectionManagerIn * pthis = (ConnectionManagerIn *)arg;
    flog<<"Connection manager In Init...\n";
    TCPSocket * socket;
    event_data_t event_data;
    try
    {
        socket = pthis->cli->getClient()->getSocket();
    }
    catch (vortex::Exception * e)
    {
        printf("%s\n",e->what());
        flog <<"Cli init:"<<e->what()<<endl;
        delete e;
    }

        char * buffer = (char *)malloc(5);
        try
        {
        if (socket->pollRead())
            socket->recv(buffer,5,0);
            LoginResponsePacket lrp(buffer,(size_t)5);
            if (lrp.getHeader().length()>0)
                flog << "Yay got a positive response!\n";
            else
                flog << "login failed!\n";
        }
        catch (vortex::Exception * e)
        {

            flog << "what 1"<<e->what()<<endl;
            //Soit Mauvais paquet
            //Soit timeout du socket
        }
        free(buffer);

    //LOGIN OK!
    //On peux rentrer dans la boucle principale de protocole
    while (1)
    {
        flog << "Main LOOP!\n";
        try
        {
            //D'abord on checks si il y a des donnees a lire avec select
            flog << "POLL successful!\n";
            char * buffer = (char *)malloc(5);
            socket->recv(buffer,5,0);
            bitBuffer header(buffer,5);
            flog << "Type:" <<(int)header.readChar(false)<<endl;

            switch (header.readChar(false))
            {

            case event_connect_login:
                flog << "login" << endl;
                break;
            case event_connect_logout:
                flog << "logout" << endl;
                break;
            case event_world_add:
                flog << "add" << endl;
                break;
            case event_world_update:
                flog << "update" << endl;
                break;
            case event_world_del:
                flog << "del" << endl;
                break;
            case event_chat_incoming:
                flog << "chat" << endl;
                break;

            }
            free(buffer);
        }
        catch (vortex::Exception * e)
        {
            flog << "what2"<<e->what()<<endl;
            delete e;
        }
        //Apres on check les events:
    }
    flog << "main loop end\n";
}