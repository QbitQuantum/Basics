//-------------------------------------------------------------------------------------
bool ClientObject::initCreate()
{
    Network::EndPoint* pEndpoint = Network::EndPoint::ObjPool().createObject();

    pEndpoint->socket(SOCK_STREAM);
    if (!pEndpoint->good())
    {
        ERROR_MSG("ClientObject::initNetwork: couldn't create a socket\n");
        Network::EndPoint::ObjPool().reclaimObject(pEndpoint);
        error_ = C_ERROR_INIT_NETWORK_FAILED;
        return false;
    }

    ENGINE_COMPONENT_INFO& infos = g_kbeSrvConfig.getBots();
    u_int32_t address;

    Network::Address::string2ip(infos.login_ip, address);
    if(pEndpoint->connect(htons(infos.login_port), address) == -1)
    {
        ERROR_MSG(fmt::format("ClientObject::initNetwork({1}): connect server({2}:{3}) is error({0})!\n",
                              kbe_strerror(), name_, infos.login_ip, infos.login_port));

        Network::EndPoint::ObjPool().reclaimObject(pEndpoint);
        // error_ = C_ERROR_INIT_NETWORK_FAILED;
        state_ = C_STATE_INIT;
        return false;
    }

    Network::Address addr(infos.login_ip, infos.login_port);
    pEndpoint->addr(addr);

    pServerChannel_->pEndPoint(pEndpoint);
    pEndpoint->setnonblocking(true);
    pEndpoint->setnodelay(true);

    pServerChannel_->pMsgHandlers(&ClientInterface::messageHandlers);

    pTCPPacketSenderEx_ = new Network::TCPPacketSenderEx(*pEndpoint, this->networkInterface_, this);
    pTCPPacketReceiverEx_ = new Network::TCPPacketReceiverEx(*pEndpoint, this->networkInterface_, this);
    Bots::getSingleton().networkInterface().dispatcher().registerReadFileDescriptor((*pEndpoint), pTCPPacketReceiverEx_);

    //²»ÔÚÕâÀï×¢²á
    //Bots::getSingleton().networkInterface().dispatcher().registerWriteFileDescriptor((*pEndpoint), pTCPPacketSenderEx_);
    pServerChannel_->pPacketSender(pTCPPacketSenderEx_);

    Network::Bundle* pBundle = Network::Bundle::ObjPool().createObject();
    (*pBundle).newMessage(LoginappInterface::hello);
    (*pBundle) << KBEVersion::versionString() << KBEVersion::scriptVersionString();

    if(Network::g_channelExternalEncryptType == 1)
    {
        pBlowfishFilter_ = new Network::BlowfishFilter();
        (*pBundle).appendBlob(pBlowfishFilter_->key());
    }
    else
    {
        std::string key = "";
        (*pBundle).appendBlob(key);
    }

    pEndpoint->send(pBundle);
    Network::Bundle::ObjPool().reclaimObject(pBundle);
    return true;
}