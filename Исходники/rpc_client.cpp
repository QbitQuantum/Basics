int main(int argc, char *argv[]) {
    if (argc<3) {
        fprintf(stderr, "Please supply (1) a port name for the client\n");
        fprintf(stderr, "              (2) a port name for the server\n");
        return 1;
    }

    Network yarp;
    const char *client_name = argv[1];
    const char *server_name = argv[2];

    RpcClient port;
    port.open(client_name);

    int ct = 0;
    while (true) {
	if (port.getOutputCount()==0) {
	  printf("Trying to connect to %s\n", server_name);
	  yarp.connect(client_name,server_name);
	} else {
	  Bottle cmd;
	  cmd.addString("COUNT");
	  cmd.addInt32(ct);
	  ct++;
	  printf("Sending message... %s\n", cmd.toString().c_str());
	  Bottle response;
	  port.write(cmd,response);
	  printf("Got response: %s\n", response.toString().c_str());
	}
	Time::delay(1);
    }
}