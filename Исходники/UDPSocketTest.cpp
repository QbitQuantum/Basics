int UDPSocketTest::run_test()
{
	cout << "UDP Socket test" << endl;

	UDPSocket* sSocket = new UDPSocket(3346);
	UDPSocket* cSocket = new UDPSocket();
	string message = "Test 1234567890";
	printf("sending\n");
	cSocket->sendTo(message,"127.0.0.1", 3346);
	char buffer[100];
	memset((void*)buffer,0,100);
	int rc = sSocket->recv(buffer, 100);
	cout<<"send msg:"<<message<<endl;
	cout<<"recv msg:"<<buffer<<endl;
	if (rc != (int)message.length()){
		perror("FAIL1: receive different message length");
	}
	if (message != buffer){
		perror("FAIL2: receive different message");
	}
	message = "Test Reply 129012901290";
	sSocket->reply(message);
	memset((void*)buffer,0,100);
	rc = cSocket->recv(buffer, 100);
	cout<<"send msg:"<<message<<endl;
	cout<<"recv msg:"<<buffer<<endl;
	if (rc != (int)message.length()){
		perror("FAIL1: receive different message length");
	}
	if (message != buffer){
		perror("FAIL2: receive different message");
	}
	sSocket->close();
	cSocket->close();
	delete sSocket;
	delete cSocket;
	printf("Bye bye..\n");
	return 0;
}