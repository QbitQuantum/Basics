int main(int argc, char* argv[]){
	if (argc > 1){
		return 1;
	}
	
	cout << argv[0] << endl;


	ACE_INET_Addr addr(1234, ACE_LOCALHOST);
	ACE_SOCK_Stream stream;
	ACE_SOCK_Acceptor acceptor;

	int success = acceptor.open(addr, 1);
	
	ACE_TCHAR addrStr[20];

	if (success > 0) {
		addr.addr_to_string(addrStr, 20);
	}

	



	

	//*
	success = acceptor.accept(stream);

	if (success < 0) {
		cout << "Cannot accept" << endl;
		return 1;
	}
	//*/


	char buf[BUFSIZ];
	int n;
	char *msg = "You are connected";
	stream.send_n(msg, strlen(msg));

	stream.close();


	
	/*
	while (stream.recv(buf, BUFSIZ)) {
		// _write(1, buf, n);
		cout << buf << endl;
	}	
	//*/


	cout << endl << "Done" << endl;

	return 0;
}