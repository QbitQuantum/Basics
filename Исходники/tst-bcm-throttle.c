int main(int argc, char **argv)
{
    int s,nbytes;
    struct sockaddr_can addr;
    struct ifreq ifr;

    struct {
      struct bcm_msg_head msg_head;
      struct can_frame frame[4];
    } txmsg, rxmsg;

    if ((s = socket(PF_CAN, SOCK_DGRAM, CAN_BCM)) < 0) {
	perror("socket");
	return 1;
    }

    addr.can_family = PF_CAN;
    strcpy(ifr.ifr_name, "vcan2");
    ioctl(s, SIOCGIFINDEX, &ifr);
    addr.can_ifindex = ifr.ifr_ifindex;

    if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
	perror("connect");
	return 1;
    }

    txmsg.msg_head.opcode  = RX_SETUP;
    txmsg.msg_head.can_id  = 0x042;
    txmsg.msg_head.flags   = SETTIMER|RX_FILTER_ID;
    txmsg.msg_head.ival1.tv_sec = 4;
    txmsg.msg_head.ival1.tv_usec = 0;
    txmsg.msg_head.ival2.tv_sec = 2;
    txmsg.msg_head.ival2.tv_usec = 0;
    txmsg.msg_head.nframes = 0;

    printf("<*>Writing RX_SETUP with RX_FILTER_ID for can_id <%03X>\n",
	   txmsg.msg_head.can_id);

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    /* obsolete for TX_SEND ... */
#if 0
    txmsg.msg_head.can_id  = 0x43;
    txmsg.msg_head.flags   = SETTIMER|STARTTIMER|TX_CP_CAN_ID;
    txmsg.msg_head.count = 0;
    txmsg.msg_head.ival1.tv_sec = 0;
    txmsg.msg_head.ival1.tv_usec = 0;
    txmsg.msg_head.ival2.tv_sec = 0;
    txmsg.msg_head.ival2.tv_usec = 0;
#endif
    txmsg.frame[0].can_id    = 0x43;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xdeadbeefdeadbeefULL;

    printf("<2>Writing TX_SEND with wrong can_id <%03X>\n",
	   txmsg.frame[0].can_id);

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xdeadbeefdeadbeefULL;

    printf("<3>Writing TX_SEND with correct can_id <%03X>\n",
	   txmsg.frame[0].can_id);

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<3>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    /* growing number of nframes => RX_DELETE instead of simple update */
    txmsg.msg_head.opcode  = RX_DELETE;
    txmsg.msg_head.can_id  = 0x042; /* everything we need for RX_DELETE */

    printf("<*>Writing RX_DELETE for can_id <%03X>\n",
	   txmsg.msg_head.can_id);

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = RX_SETUP;
    txmsg.msg_head.can_id  = 0x042;
    txmsg.msg_head.flags   = SETTIMER|RX_CHECK_DLC;
    txmsg.msg_head.ival1.tv_sec = 4;
    txmsg.msg_head.ival1.tv_usec = 0;
    txmsg.msg_head.ival2.tv_sec = 2;
    txmsg.msg_head.ival2.tv_usec = 0;
    txmsg.msg_head.nframes = 1;
    /* txmsg.frame[0].can_dlc   = 8; obsolete for RX_SETUP */
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xFF00000000000000ULL;

    printf("<*>Writing simple RX_SETUP for can_id <%03X> with msgbits 0x%016llX\n",
	   txmsg.msg_head.can_id, U64_DATA(&txmsg.frame[0]));

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xdeadbeefdeadbeefULL;

    printf("<5>Writing TX_SEND with correct can_id <%03X>\n",
	   txmsg.frame[0].can_id);

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<5>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xdeadbeefdeadbeefULL;

    printf("<6>Writing TX_SEND with correct can_id <%03X> ",
	   txmsg.frame[0].can_id);
    printf("no changed data\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    /* no change here */

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xdeadbeefdeadbeefULL;

    printf("<7>Writing TX_SEND with correct can_id <%03X> ",
	   txmsg.frame[0].can_id);
    printf("changed relevant msgbits\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<7>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xdeadbeefdeadbeefULL;

    printf("<8>Writing TX_SEND with correct can_id <%03X> ",
	   txmsg.frame[0].can_id);
    printf("changed irrelevant msgbits\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 7;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xdeadbeefdeadbeefULL;

    printf("<9>Writing TX_SEND with correct can_id <%03X> ",
	   txmsg.frame[0].can_id);
    printf("changed Data Length Code DLC\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<9>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    /* no problems ;-) but NOW we try MUX messages ... and timeouts */

    /* growing number of nframes => RX_DELETE instead of simple update */
    txmsg.msg_head.opcode  = RX_DELETE;
    txmsg.msg_head.can_id  = 0x042; /* everything we need for RX_DELETE */

    printf("<*>Writing RX_DELETE for can_id <%03X>\n",
	   txmsg.msg_head.can_id);

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = RX_SETUP;
    txmsg.msg_head.can_id  = 0x042;
    txmsg.msg_head.flags   = SETTIMER|RX_CHECK_DLC;
    txmsg.msg_head.ival1.tv_sec = 4;
    txmsg.msg_head.ival1.tv_usec = 0;
    txmsg.msg_head.ival2.tv_sec = 2;
    txmsg.msg_head.ival2.tv_usec = 0;
    txmsg.msg_head.nframes = 3;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0xFF00000000000000ULL;
    U64_DATA(&txmsg.frame[1]) = (__u64) 0x01000000000000FFULL;
    U64_DATA(&txmsg.frame[2]) = (__u64) 0x02000000000000FFULL;

    printf("<*>Writing multiplex RX_SETUP for can_id <%03X>\n",
	   txmsg.msg_head.can_id);

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");


    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x4200000000000000ULL;

    printf("<A>Writing TX_SEND with wrong MUX ID 42\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x0100000000000000ULL;

    printf("<B>Writing TX_SEND with correct MUX ID 01\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<B>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x0100000000000000ULL;

    printf("<C>Writing TX_SEND with correct MUX ID 01 but no data change\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x0100001234567800ULL;

    printf("<D>Writing TX_SEND with correct MUX ID 01 but no relevant data change\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x0100001234567801ULL;

    printf("<E>Writing TX_SEND with correct MUX ID 01 with relevant data change\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<E>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x0200000000000000ULL;

    printf("<F>Writing TX_SEND with correct MUX ID 02\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<F>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 8;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x0200000000000001ULL;

    printf("<10>Writing TX_SEND with correct MUX ID 02 with relevant data change\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<10>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 7;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x0200000000000001ULL;

    printf("<11>Writing TX_SEND with correct MUX ID 02 no data change but DLC\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_CHANGED &&
	nbytes == sizeof(struct bcm_msg_head) + sizeof(struct can_frame) &&
	rxmsg.msg_head.can_id == 0x42 && rxmsg.frame[0].can_id == 0x42) {
      printf("<11>Received correct RX_CHANGED message for can_id <%03X> >> OK!\n",
	     rxmsg.frame[0].can_id);
    }

    txmsg.msg_head.opcode  = TX_SEND;
    txmsg.msg_head.nframes = 1;
    txmsg.frame[0].can_id    = 0x42;
    txmsg.frame[0].can_dlc   = 7;
    U64_DATA(&txmsg.frame[0]) = (__u64) 0x0300000000000001ULL;

    printf("<12>Writing TX_SEND with wrong MUX ID 03\n");

    if (write(s, &txmsg, sizeof(txmsg)) < 0)
      perror("write");

    if ((nbytes = read(s, &rxmsg, sizeof(rxmsg))) < 0)
      perror("read");

    if (rxmsg.msg_head.opcode == RX_TIMEOUT &&
	nbytes == sizeof(struct bcm_msg_head) &&
	rxmsg.msg_head.can_id == 0x42) {
      printf("<-->Received correct RX_TIMEOUT message for can_id <%03X> >> OK!\n",
	     rxmsg.msg_head.can_id);
    }

    close(s);

    return 0;
}