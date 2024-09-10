int main(int argc, char** argv)
{
	mqd_t msg_queue = mq_open("/CprE308-Queue", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, NULL);
	if(msg_queue == -1)
	{
		perror("mq_open\n");
		return -1;
	}

	// Determine max. msg size; allocate buffer to receive msg
	struct mq_attr attr;
	char *buf;
	if (mq_getattr(msg_queue, &attr))
	{
		perror("mq_getattr\n");
		exit(-1);
	}
	buf = malloc(attr.mq_msgsize);
	if (buf == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	
	sleep(10);
	
	ssize_t size;
	size = mq_receive(msg_queue, buf, attr.mq_msgsize, NULL);
	if (size == -1)
	{
		perror("mq_receive\n");
		exit(-1);
	}
	printf("Received message \"%s\"\n", buf);
	
	
	size = mq_receive(msg_queue, buf, attr.mq_msgsize, NULL);
	if (size == -1)
	{
		perror("mq_receive\n");
		exit(-1);
	}
	printf("Received message \"%s\"\n", buf);
	
	
	free(buf);
	
	char my_string[] = "I am Clara";
	
	if( mq_send(msg_queue, my_string, strlen(my_string), 12))
	{
		perror("mq_send\n");
		return -1;
	}

	char my_string2[] = "I am Rose";
	
	if( mq_send(msg_queue, my_string2, strlen(my_string2), 11))
	{
		perror("mq_send\n");
		return -1;
	}
	return 0;
}