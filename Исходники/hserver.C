int main(){
	signal(SIGHUP, HTTPServer::HUP_received);

	Config* con = Config::Instance();
	con->saveParam();
	int Port = atoi(con->lookupParam("Port").c_str());
	cerr << "opening a socket" << endl;
	Socket* masterSocket = new Socket();
	if (masterSocket->Listen(Port) < 0) { 
		// handle error
		cerr << "Error: the listen function has failed, OS cannot accept new connection" << endl; 
		return -1;
	}

	int LENGTH = 2;
	int count = 0;
	Thread* threads[LENGTH];
	for (int i = 0; i < LENGTH; i++)
		threads[i] = NULL;

	ssbuf* ssbuffer;
	Thread* thread;

	Thread* threadWatch = new Thread();
	threadWatch->Run(new ServWatcher(thread));

	MutexInstance::Instance();

	while ((ssbuffer = new ssbuf())->accept(masterSocket) != 0) {
		cout << (threads[count] == NULL) << endl;
		if (threads[count] == NULL) {
			cout << "created new" << endl;
			threads[count] = new Thread();
		}
		thread = threads[count];
		cout << "Opening new connection:"<<count<<endl;

		thread->Join();
		cout << "Joining"<<endl;
		cout << "Run:"<<thread->Run(new HTTPServer(thread, ssbuffer, masterSocket))<<endl;
		cout << "Running:"<<count<<endl;
		if (count++ > LENGTH-1)
			count = 0;
		if (HTTPServer::server_count <= 0) break;
	}
	return 0;
}