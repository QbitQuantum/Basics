void client()
{
	Message_t msg, reply;
	int reply_port, status, code, func, packet_no = 0;
	char precoded_string[15] = "+++--*+*-+--*-*";
	int op = 0;
	reply_port = getCurrentThreadId();

	openPort(reply_port);

	msg = (Message_t)malloc(sizeof(struct message));
    reply = (Message_t)malloc(sizeof(struct message));

    srand(getCurrentThreadId());

	while(1)
	{
		if(precoded_string[op] == '+')
			func = ADD;
		else if(precoded_string[op] == '-')
			func = DELETE;
		else
			func = MODIFY;

		do
		{
			code = createPacket(msg, func, rand() % 10, packet_no++);
			printf("\n[Client_on_port_%d]:Sent message:\t", getCurrentThreadId());
			if((status = Send(SERVER_PORT, msg))<0)
			{
                 printf("\n[Client_%d]:Send error",getCurrentThreadId());
                 exit(-1);
			}
			if((status = Receive(reply_port, reply))<0)
			{
				printf("\n[Client_%d]:Receive error",getCurrentThreadId());
				exit(-1);
			}
			if(reply->error_code == -1) break;
		}while(code);

		if(++op == 15)
			op=0;

		packet_no = 0;
		sleep(1);
	}
	closePort(reply_port);
}