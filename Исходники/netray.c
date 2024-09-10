void print_icmp_header(struct packet* p)
{
	fputs(p->icmpmsg, stdout); 
}