static Iface_DEFUN sendMessage(struct Message* msg, struct Iface* iface)
{
    struct ETHInterface_pvt* ctx =
        Identity_containerOf(iface, struct ETHInterface_pvt, pub.generic.iface);

    struct Sockaddr* sa = (struct Sockaddr*) msg->bytes;
    Assert_true(msg->length >= Sockaddr_OVERHEAD);
    Assert_true(sa->addrLen <= ETHInterface_Sockaddr_SIZE);

    struct ETHInterface_Sockaddr sockaddr = { .generic = { .addrLen = 0 } };
    Message_pop(msg, &sockaddr, sa->addrLen, NULL);

    struct sockaddr_ll addr;
    Bits_memcpyConst(&addr, &ctx->addrBase, sizeof(struct sockaddr_ll));

    if (sockaddr.generic.flags & Sockaddr_flags_BCAST) {
        Bits_memset(addr.sll_addr, 0xff, 6);
    } else {
        Bits_memcpyConst(addr.sll_addr, sockaddr.mac, 6);
    }

    struct ETHInterface_Header hdr = {
        .version = ETHInterface_CURRENT_VERSION,
        .zero = 0,
        .length_be = Endian_hostToBigEndian16(msg->length + ETHInterface_Header_SIZE),
        .fc00_be = Endian_hostToBigEndian16(0xfc00)
    };
    Message_push(msg, &hdr, ETHInterface_Header_SIZE, NULL);
    sendMessageInternal(msg, &addr, ctx);
    return NULL;
}

static void handleEvent2(struct ETHInterface_pvt* context, struct Allocator* messageAlloc)
{
    struct Message* msg = Message_new(MAX_PACKET_SIZE, PADDING, messageAlloc);

    struct sockaddr_ll addr;
    uint32_t addrLen = sizeof(struct sockaddr_ll);

    // Knock it out of alignment by 2 bytes so that it will be
    // aligned when the idAndPadding is shifted off.
    Message_shift(msg, 2, NULL);

    int rc = recvfrom(context->socket,
                      msg->bytes,
                      msg->length,
                      0,
                      (struct sockaddr*) &addr,
                      &addrLen);

    if (rc < ETHInterface_Header_SIZE) {
        Log_debug(context->logger, "Failed to receive eth frame");
        return;
    }

    Assert_true(msg->length >= rc);
    msg->length = rc;

    //Assert_true(addrLen == SOCKADDR_LL_LEN);

    struct ETHInterface_Header hdr;
    Message_pop(msg, &hdr, ETHInterface_Header_SIZE, NULL);

    // here we could put a switch statement to handle different versions differently.
    if (hdr.version != ETHInterface_CURRENT_VERSION) {
        Log_debug(context->logger, "DROP unknown version");
        return;
    }

    uint16_t reportedLength = Endian_bigEndianToHost16(hdr.length_be);
    reportedLength -= ETHInterface_Header_SIZE;
    if (msg->length != reportedLength) {
        if (msg->length < reportedLength) {
            Log_debug(context->logger, "DROP size field is larger than frame");
            return;
        }
        msg->length = reportedLength;
    }
    if (hdr.fc00_be != Endian_hostToBigEndian16(0xfc00)) {
        Log_debug(context->logger, "DROP bad magic");
        return;
    }

    struct ETHInterface_Sockaddr  sockaddr = { .zero = 0 };
    Bits_memcpyConst(sockaddr.mac, addr.sll_addr, 6);
    sockaddr.generic.addrLen = ETHInterface_Sockaddr_SIZE;
    if (addr.sll_pkttype == PACKET_BROADCAST) {
        sockaddr.generic.flags |= Sockaddr_flags_BCAST;
    }

    Message_push(msg, &sockaddr, ETHInterface_Sockaddr_SIZE, NULL);

    Assert_true(!((uintptr_t)msg->bytes % 4) && "Alignment fault");

    Iface_send(&context->pub.generic.iface, msg);
}

static void handleEvent(void* vcontext)
{
    struct ETHInterface_pvt* context = Identity_check((struct ETHInterface_pvt*) vcontext);
    struct Allocator* messageAlloc = Allocator_child(context->pub.generic.alloc);
    handleEvent2(context, messageAlloc);
    Allocator_free(messageAlloc);
}

List* ETHInterface_listDevices(struct Allocator* alloc, struct Except* eh)
{
    struct ifaddrs* ifaddr = NULL;
    if (getifaddrs(&ifaddr) || ifaddr == NULL) {
        Except_throw(eh, "getifaddrs() -> errno:%d [%s]", errno, strerror(errno));
    }
    List* out = List_new(alloc);
    for (struct ifaddrs* ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_PACKET) {
            List_addString(out, String_new(ifa->ifa_name, alloc), alloc);
        }
    }
    freeifaddrs(ifaddr);
    return out;
}

static int closeSocket(struct Allocator_OnFreeJob* j)
{
    struct ETHInterface_pvt* ctx = Identity_check((struct ETHInterface_pvt*) j->userData);
    close(ctx->socket);
    return 0;
}

struct ETHInterface* ETHInterface_new(struct EventBase* eventBase,
                                      const char* bindDevice,
                                      struct Allocator* alloc,
                                      struct Except* exHandler,
                                      struct Log* logger)
{
    struct ETHInterface_pvt* ctx = Allocator_calloc(alloc, sizeof(struct ETHInterface_pvt), 1);
    Identity_set(ctx);
    ctx->pub.generic.iface.send = sendMessage;
    ctx->pub.generic.alloc = alloc;
    ctx->logger = logger;

    struct ifreq ifr = { .ifr_ifindex = 0 };

    ctx->socket = socket(AF_PACKET, SOCK_DGRAM, Ethernet_TYPE_CJDNS);
    if (ctx->socket == -1) {
        Except_throw(exHandler, "call to socket() failed. [%s]", strerror(errno));
    }
    Allocator_onFree(alloc, closeSocket, ctx);

    CString_strncpy(ifr.ifr_name, bindDevice, IFNAMSIZ - 1);
    ctx->ifName = String_new(bindDevice, alloc);

    if (ioctl(ctx->socket, SIOCGIFINDEX, &ifr) == -1) {
        Except_throw(exHandler, "failed to find interface index [%s]", strerror(errno));
    }
    ctx->ifindex = ifr.ifr_ifindex;

    if (ioctl(ctx->socket, SIOCGIFFLAGS, &ifr) < 0) {
        Except_throw(exHandler, "ioctl(SIOCGIFFLAGS) [%s]", strerror(errno));
    }
    if (!((ifr.ifr_flags & IFF_UP) && (ifr.ifr_flags & IFF_RUNNING))) {
        Log_info(logger, "Bringing up interface [%s]", ifr.ifr_name);
        ifr.ifr_flags |= IFF_UP | IFF_RUNNING;
        if (ioctl(ctx->socket, SIOCSIFFLAGS, &ifr) < 0) {
            Except_throw(exHandler, "ioctl(SIOCSIFFLAGS) [%s]", strerror(errno));
        }
    }

    ctx->addrBase = (struct sockaddr_ll) {
        .sll_family = AF_PACKET,
        .sll_protocol = Ethernet_TYPE_CJDNS,
        .sll_ifindex = ctx->ifindex,
        .sll_hatype = ARPHRD_ETHER,
        .sll_pkttype = PACKET_OTHERHOST,
        .sll_halen = ETH_ALEN
    };

    if (bind(ctx->socket, (struct sockaddr*) &ctx->addrBase, sizeof(struct sockaddr_ll))) {
        Except_throw(exHandler, "call to bind() failed [%s]", strerror(errno));
    }

    Socket_makeNonBlocking(ctx->socket);

    Event_socketRead(handleEvent, ctx, ctx->socket, eventBase, alloc, exHandler);

    return &ctx->pub;
}