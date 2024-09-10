/*---------------------------------------------------------------------*/
int main(int count, char *strings[])
{
	signal(SIGCHLD, sigchild);
	if ( count != 3 )
	{
		printf("usage: %s <addr:port> <peer:port>\n", strings[0]);
		exit(1);
	}
	HostAddress addr(strings[1]);
	HostAddress domain(strings[2]);

	try
	{
		Socket *channel = new Broadcast(addr);
		if ( !fork() )
			receiver(channel);
		channel->CloseInput();
		TextMessage msg(1024);
		do
		{
			char line[100];
			fgets(line, sizeof(line), stdin);
			msg = line;
			channel->Send(domain, msg);
		}
		while ( !done );
		delete channel;
	}
	catch (Exception& err)
	{
		printf("[PARENT]");
		err.PrintException();
	}
	catch (...)
	{
		fprintf(stderr, "Unknown error\n");
	}
	return 0;
}