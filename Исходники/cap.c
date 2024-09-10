int
libnet_send(struct sniff_ethernet *ethernet, struct sniff_ip *ip, struct sniff_tcp *tcp, int size_payload, const u_char *payload)
{	
	char *dev = "eth0";
	libnet_t *handle; /* Libnet句柄 */
	int packet_size; /* 构造的数据包大小 */
	
	char error[LIBNET_ERRBUF_SIZE]; /* 出错信息 */
	libnet_ptag_t eth_tag, ip_tag, tcp_tag, tcp_op_tag; /* 各层build函数返回值 */
	u_short proto = IPPROTO_TCP; /* 传输层协议 */
	u_long dst_ip, src_ip; /* 网路序的目的IP和源IP */
	
	
	/* 把目的IP地址字符串转化成网络序 */
	dst_ip = libnet_name2addr4(handle, inet_ntoa(ip->ip_dst), LIBNET_RESOLVE);
	/* 把源IP地址字符串转化成网络序 */
	src_ip = libnet_name2addr4(handle, inet_ntoa(ip->ip_src), LIBNET_RESOLVE);
	
    /* 初始化Libnet */
	if ( (handle = libnet_init(LIBNET_LINK, dev, error)) == NULL ) {
		printf("libnet_init failure\n");
		return (-1);
	};
	//strncpy(payload, "test", sizeof(payload)-1); /* 构造负载的内容 */
	//payload_s = strlen(payload); /* 计算负载内容的长度 */

#if 0
	/* 构建TCP的选项,通常在第一个TCP通信报文中设置MSS */
	tcp_op_tag = libnet_build_tcp_options(
                payload,
                size_payload,
                handle,
                0
	);
	if (tcp_op_tag == -1) {
		printf("build_tcp_options failure\n");
		return (-2);
    };
#endif
	tcp_tag = libnet_build_tcp(
                ntohs(tcp->th_sport),                    /* 源端口 */
                ntohs(tcp->th_dport),                    /* 目的端口 */
                tcp->th_seq,                    /* 序列号 */
                tcp->th_ack,                    /* 确认号 */
                TH_ACK | TH_PUSH,           /* Control flags */
                ntohs(tcp->th_win),       /* 窗口尺寸 */
                0,                        /* 校验和,0为自动计算 */
                0,                        /* 紧急指针 */
                LIBNET_TCP_H + size_payload, /* 长度 */
                payload,                  /* 负载内容 */
                size_payload,             /* 负载内容长度 */
                handle,                   /* libnet句柄 */
                0                         /* 新建包 */
    );
	if (tcp_tag == -1) {
		printf("libnet_build_tcp failure\n");
		return (-3);
    };
    /* 构造IP协议块，返回值是新生成的IP协议快的一个标记 */
	ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_TCP_H + size_payload, /* IP协议块的总长,*/
        0, /* tos */
        ntohs(ip->ip_id), //(u_short) libnet_get_prand(LIBNET_PRu16), /* id,随机产生0~65535 */
        0, /* frag 片偏移 */
        ip->ip_ttl, //(u_int8_t)libnet_get_prand(LIBNET_PR8), /* ttl,随机产生0~255 */
        proto, /* 上层协议 */
        0, /* 校验和，此时为0，表示由Libnet自动计算 */
        src_ip, /* 源IP地址,网络序 */
        dst_ip, /* 目标IP地址,网络序 */
        NULL, /* 负载内容或为NULL */
        0, /* 负载内容的大小*/
        handle, /* Libnet句柄 */
        0 /* 协议块标记可修改或创建,0表示构造一个新的*/
    );
	if (ip_tag == -1) {
		printf("libnet_build_ipv4 failure\n");
		return (-4);
    };
    /* 构造一个以太网协议块,只能用于LIBNET_LINK */
	eth_tag = libnet_build_ethernet(
        ethernet->ether_dhost, /* 以太网目的地址 */
        ethernet->ether_shost, /* 以太网源地址 */
        ETHERTYPE_IP, /* 以太网上层协议类型，此时为IP类型 */
        NULL, /* 负载，这里为空 */ 
        0, /* 负载大小 */
        handle, /* Libnet句柄 */
        0 /* 协议块标记，0表示构造一个新的 */ 
    );
	if (eth_tag == -1) {
		printf("libnet_build_ethernet failure\n");
		return (-5);
    };

	packet_size = libnet_write(handle); /* 发送已经构造的数据包*/
	libnet_destroy(handle); /* 释放句柄 */
	return (0);
}	