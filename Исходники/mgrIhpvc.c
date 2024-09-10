int send_hpvcmem(int fd , char * str ,  struct sockaddr * ppeeraddr , socklen_t addrlen)
{
		struct node_t * p = hpvc_usr.mem_list.head;

		Sendto(fd , "----------HPVCMEM---------- :\n" , 30 , 0 , ppeeraddr , addrlen);
		while(NULL != p)
		{
				sprintf(str , "p : 0x%.8x , avfd : 0x%.8x , next : 0x%.8x \n", p , *((int*)p->data) , p->next);
				Sendto(fd , str , strlen(str)  , 0 , ppeeraddr , addrlen);
				p = p->next;
		}
		return 0; 
}