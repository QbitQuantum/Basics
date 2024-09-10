int ipx_change_default_socket( ushort socket_number )
{
	int i;
	WORD new_ipx_socket;
	dpmi_real_regs rregs;

	if ( !ipx_installed ) return -3;

	// Open a new socket	
	memset(&rregs,0,sizeof(dpmi_real_regs));
	swab( (char *)&socket_number,(char *)&new_ipx_socket, 2 );
	rregs.edx = new_ipx_socket;
	rregs.eax = ipx_socket_life;
	rregs.ebx = 0;	// Open socket
	dpmi_real_int386x( 0x7A, &rregs );
	
	new_ipx_socket = rregs.edx & 0xFFFF;
	
	if ( rregs.eax & 0xFF )	{
		//printf( (1, "IPX error opening channel %d\n", socket_number-IPX_DEFAULT_SOCKET ));
		return -2;
	}

	for (i=1; i<ipx_num_packets; i++ )	{
		ipx_cancel_listen_for_packet(&packets[i].ecb);
	}

	// Close existing socket...
	memset(&rregs,0,sizeof(dpmi_real_regs));
	rregs.edx = ipx_socket;
	rregs.ebx = 1;	// Close socket
	dpmi_real_int386x( 0x7A, &rregs );

	ipx_socket = new_ipx_socket;

	// Repost all listen requests on the new socket...	
	for (i=1; i<ipx_num_packets; i++ )	{
		packets[i].ecb.in_use = 0;
		packets[i].ecb.socket_id = ipx_socket;
		ipx_listen_for_packet(&packets[i].ecb);
	}

	packets[0].ecb.socket_id = ipx_socket;
	packets[0].ipx.destination.socket_id = ipx_socket;

	ipx_packetnum = 0;
	// init packet buffers.
	for (i=0; i<MAX_PACKETS; i++ )	{
		packet_buffers[i].packetnum = -1;
		packet_free_list[i] = i;
	}
	num_packets = 0;
	largest_packet_index = 0;

	return 0;
}