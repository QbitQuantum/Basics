int main(int argc, char *argv[])
{
//For debugging
	file = fopen("file_g_s.txt", "w");
	fprintf(file,"%s","Top of the file");
//
	
	//char send_buf[MAX_SEND_BUF_LENGTH];
	set_dsanode_ids();
	serverSocketStuff();
	
    printf("gateway_s: waiting for connections...\n");
    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }
        inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr *)&their_addr),s, sizeof s);

        printf("gateway_s: got connection from %s\n", s);
		//fprintf(file,"%s","server: got connection from");
		//fprintf(file,"%s\n",s);
		//Threading
		childPID=fork();
		if(childPID>=0)
		{
			if(childPID == 0){ //Child process
				close(sockfd); // child doesn't need the listener
				//Wait for #ofChunks:X message from p
				recvFrom(new_fd, 0);
				char subbuff[10];
				memcpy( subbuff, recv_buff, 10 );
				subbuff[10] = '\0';
				if(strcmp(subbuff, "#ofChunks:")==0){
					sendTo(new_fd, "OK"); //the # of chunks that client desires to get
				}
				else{
					printf("Recved irrelevant message:%s\n", recv_buff);
					exit(1);
				}
				//send the bulk data to the client
				strncpy(subbuff, recv_buff+strlen("#ofChunks:"), (strlen(recv_buff)-strlen("#ofChunks:")));
				nofChunksToRecv=atoi(subbuff);
				printf("nofChunksToRecv:%d\n", nofChunksToRecv);
				while(1){
					numbytes=recvFrom(new_fd, 0);
					fprintf(file, "\nnumbytes recved: %d",numbytes);
					//printf("GW RECEIVED: '%s'\n",recv_buff);
					fprintf(file,"\n%s",recv_buff);
					pthread_join(tt,NULL); //Wait for the previous thread to finish
					strcat(send_buff, recv_buff);//buffer all the data to be sent to dsa stage
					//Instead of writing the recved data to a file send the data to the staging nodes
					int rc = pthread_create(&tt, NULL, sendToStage, NULL);
					if (rc){
				    	printf("ERROR; return code from pthread_create() is %d\n", rc);
				        exit(-1);
					}
					memset(recv_buff, 0, MAXRECVLENGTH);
				}
			}
			else{//parent process
				close(new_fd);  // parent doesn't need this
				//Listen the channel by inf while
			}
		}
		else{
			printf("\n Fork failed, exit !\n");
	        return 1;
		}

	}
	fclose(file); /*done!*/ 
    return 0;
}