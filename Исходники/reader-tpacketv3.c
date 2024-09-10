void reader_tpacketv3_init(char *UNUSED(name))
{
    int i;
    int blocksize = moloch_config_int(NULL, "tpacketv3BlockSize", 1<<21, 1<<16, 1<<31);
    numThreads = moloch_config_int(NULL, "tpacketv3NumThreads", 2, 1, 6);

    if (blocksize % getpagesize() != 0) {
        LOGEXIT("block size %d not divisible by pagesize %d", blocksize, getpagesize());
    }

    if (blocksize % config.snapLen != 0) {
        LOGEXIT("block size %d not divisible by %d", blocksize, config.snapLen);
    }

    moloch_packet_set_linksnap(1, config.snapLen);

    pcap_t *dpcap = pcap_open_dead(pcapFileHeader.linktype, pcapFileHeader.snaplen);

    if (config.bpf) {
        if (pcap_compile(dpcap, &bpf, config.bpf, 1, PCAP_NETMASK_UNKNOWN) == -1) {
            LOGEXIT("ERROR - Couldn't compile filter: '%s' with %s", config.bpf, pcap_geterr(dpcap));
        }
    }


    for (i = 0; i < MAX_INTERFACES && config.interface[i]; i++) {
        MOLOCH_LOCK_INIT(infos[i].lock);

        int ifindex = if_nametoindex(config.interface[i]);

        infos[i].fd = socket(AF_PACKET, SOCK_RAW, 0);

        int version = TPACKET_V3;
        if (setsockopt(infos[i].fd, SOL_PACKET, PACKET_VERSION, &version, sizeof(version)) < 0)
            LOGEXIT("Error setting TPACKET_V3, might need a newer kernel: %s", strerror(errno));


        memset(&infos[i].req, 0, sizeof(infos[i].req));
        infos[i].req.tp_block_size = blocksize;
        infos[i].req.tp_block_nr = numThreads*64;
        infos[i].req.tp_frame_size = config.snapLen;
        infos[i].req.tp_frame_nr = (blocksize * infos[i].req.tp_block_nr) / infos[i].req.tp_frame_size;
        infos[i].req.tp_retire_blk_tov = 60;
        infos[i].req.tp_feature_req_word = 0;
        if (setsockopt(infos[i].fd, SOL_PACKET, PACKET_RX_RING, &infos[i].req, sizeof(infos[i].req)) < 0)
            LOGEXIT("Error setting PACKET_RX_RING: %s", strerror(errno));

        struct packet_mreq      mreq;
        memset(&mreq, 0, sizeof(mreq));
        mreq.mr_ifindex = ifindex;
        mreq.mr_type    = PACKET_MR_PROMISC;
        if (setsockopt(infos[i].fd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
            LOGEXIT("Error setting PROMISC: %s", strerror(errno));

        if (config.bpf) {
            struct sock_fprog       fcode;
            fcode.len = bpf.bf_len;
            fcode.filter = (struct sock_filter *)bpf.bf_insns;
            if (setsockopt(infos[i].fd, SOL_SOCKET, SO_ATTACH_FILTER, &fcode, sizeof(fcode)) < 0)
                LOGEXIT("Error setting SO_ATTACH_FILTER: %s", strerror(errno));
        }

        infos[i].map = mmap64(NULL, infos[i].req.tp_block_size * infos[i].req.tp_block_nr,
                             PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED, infos[i].fd, 0);
        if (unlikely(infos[i].map == MAP_FAILED)) {
            LOGEXIT("ERROR - MMap64 failure in reader_tpacketv3_init, %d: %s",errno, strerror(errno));
        }
        infos[i].rd = malloc(infos[i].req.tp_block_nr * sizeof(struct iovec));

        uint16_t j;
        for (j = 0; j < infos[i].req.tp_block_nr; j++) {
            infos[i].rd[j].iov_base = infos[i].map + (j * infos[i].req.tp_block_size);
            infos[i].rd[j].iov_len = infos[i].req.tp_block_size;
        }

        struct sockaddr_ll ll;
        memset(&ll, 0, sizeof(ll));
        ll.sll_family = PF_PACKET;
        ll.sll_protocol = htons(ETH_P_ALL);
        ll.sll_ifindex = ifindex;

        if (bind(infos[i].fd, (struct sockaddr *) &ll, sizeof(ll)) < 0)
            LOGEXIT("Error binding %s: %s", config.interface[i], strerror(errno));
    }

    if (i == MAX_INTERFACES) {
        LOGEXIT("Only support up to %d interfaces", MAX_INTERFACES);
    }

    moloch_reader_start         = reader_tpacketv3_start;
    moloch_reader_stop          = reader_tpacketv3_stop;
    moloch_reader_stats         = reader_tpacketv3_stats;
}