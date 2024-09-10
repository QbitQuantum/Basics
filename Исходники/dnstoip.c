int main(int argc, char **argv) {

					//start of the address from argv
	char 			*ptr, **pptr;
	char 			str[INET_ADDRSTRLEN];
	struct hostent *hptr;

	while(--argc > 0) {

		ptr = *++argv;

		//gethostbyname is a function to get the ip from DNS - numeric tpye
		if((hptr = gethostbyname(ptr)) == NULL) {

			err_msg("gethostbyname error for host: %s: %s", ptr, hstrerror(h_errno));
			continue;
		}
		//This is the “official” name of the host.
		printf("official hostname: %s\r\n", hptr->h_name);

		//These are alternative names for the host, represented as a null-terminated vector of strings.
		for(pptr = hptr->h_aliases; *pptr != NULL; pptr++) {
			printf("\t alias: %s\r\n", *pptr);
		}


		//pointer to all known IPs for that DNS
		pptr = hptr->h_addr_list; // vector of addresses

		for( ; *pptr != NULL; pptr++) {

			printf("\t Addr %lu \r\n", hptr->h_addr);
			//AF_INET or AF_INET6 lattter is for IPV6
			printf("\t address :%s\r\n", Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
		}
	}

	exit(0);
}