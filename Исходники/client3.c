void client(int readid, int writeid)
{
	size_t len;
	ssize_t n;
	char *ptr;
	struct mymesg mesg;

	//start buffer with msqid and a blank
	snprintf(mesg.mesg_data, MAXMESGDATA, "%d ", readid);
	len = strlen(mesg.mesg_data);
	ptr = mesg.mesg_data + len;

	//read pathname
	Fgets(ptr, MAXMESGDATA - len, stdin);
	len = strlen(mesg.mesg_data);
	if (mesg.mesg_data[len-1] == '\n')
		len--;
	mesg.mesg_len = len;
	mesg.mesg_type = 1;

	//write msqid and pathname to server well-know queue
	mesg_send(writeid, &mesg);

	//read from our queue, wirte to standard output
	while ((n = mesg_recv(readid, &mesg)) > 0)
		Write(STDOUT_FILENO, mesg.mesg_data, n);
}