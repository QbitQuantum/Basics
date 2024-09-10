int main(int argc, char **argv){

	//joystick stick;
	socketpair(AF_UNIX, SOCK_STREAM, 0, sv);


	if(fork()){
		printf("Read Thread Alive\n");
		ros::init(argc, argv, "read_byte_client");

		ros::NodeHandle r;
		ros::ServiceClient rclient = r.serviceClient<rxtxserver::Read>("read_byte");
		rxtxserver::Read data;

		FILE * intercomm = fopen("intercomm", "w");

		while(1){
			printf("Read Client Attempting Read");
			if(rclient.call(data)){
				fputc(data.response.outData, intercomm);
				fflush(intercomm);
			}
			usleep(1000);
		}
		return 1;

	}
	else{
		printf("Write Thread Alive\n");

		ros::init(argc, argv, "send_byte_client");
		ros::NodeHandle n;
		ros::ServiceClient client = n.serviceClient<rxtxserver::Byte>("send_byte");

		FILE * intercomm2 = fopen("intercomm", "r");


		time_t start,now;


		char string[11];
		string[0] = ' ';
		string[1] = '0';
		string[2] = 'a';
		string[9] = 's';
		string[10] = 0;

		//int i;
		char buf;



		while(1){
			/*
			   ros::spinOnce();
			   for(i = 3; i < 8; i ++){
			   string[i] = char(stick.axes[i-3]);
			   }
			   string[8] = 20;
			   for(i = 0; i < 11; i ++){
			   if(stick.button[i]){
			   string[8] = i;
			   }
			   }
			   if(string[8] == 0){
			   string[8] = 20;
			   }
			 */
			/*
			   sendstring(string);

			   for(i = 0;i<10;i ++){
			   usleep(4000);

			   if(rclient.call(data)){
			   printf("%c", data.response.outData);
			   }

			   }
			 */
			printf("Write Thread Sending Packet\n");
			sendstring(string, &client);
			time(&start);
			do{
				usleep(1000);
				printf("checking data\n");
				if(fscanf(intercomm2, "%c", buf) == 1){
					printf("%c\n", buf);
				}
				time(&now);
			}while(difftime(now, start) < 0.04);
		}	
		printf("I'm Stopping for some reason\n");
		return 1;
	}
}