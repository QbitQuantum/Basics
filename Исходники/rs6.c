/*
 * Function: print_attack_info()
 *
 * Print attack details (when the verbose ("-v") option is specified).
 */
void print_attack_info(struct iface_data *idata){
	if(floods_f)
		printf("Flooding the target from %u different IPv6 Source Addresses\n", nsources);

	if(!floods_f){
		if(ether_ntop(&(idata->hsrcaddr), plinkaddr, sizeof(plinkaddr)) == 0){
			puts("ether_ntop(): Error converting address");
			exit(EXIT_FAILURE);
		}

		printf("Ethernet Source Address: %s%s\n", plinkaddr, ((!idata->hsrcaddr_f)?" (randomized)":""));
	}
    else{
		if(idata->hsrcaddr_f){
			if(ether_ntop(&(idata->hsrcaddr), plinkaddr, sizeof(plinkaddr)) == 0){
				puts("ether_ntop(): Error converting address");
				exit(EXIT_FAILURE);
			}

			printf("Ethernet Source Address: %s\n", plinkaddr);
		}
		else
			puts("Ethernet Source Address: randomized for each packet");
	}

	if(ether_ntop(&(idata->hdstaddr), phdstaddr, sizeof(phdstaddr)) == 0){
		puts("ether_ntop(): Error converting address");
		exit(EXIT_FAILURE);
	}

    printf("Ethernet Destination Address: %s%s\n", phdstaddr, \
					((!idata->hdstaddr_f)?" (all-routers multicast)":""));


	if(inet_ntop(AF_INET6, &(idata->srcaddr), psrcaddr, sizeof(psrcaddr)) == NULL){
		puts("inet_ntop(): Error converting IPv6 Source Address to presentation format");
		exit(EXIT_FAILURE);
	}

    if(!floods_f){
	printf("IPv6 Source Address: %s%s\n", psrcaddr, ((!idata->srcaddr_f)?" (randomized)":""));
    }
    else{
    	printf("IPv6 Source Address: randomized, from the %s/%u prefix%s\n", psrcaddr, idata->srcpreflen, \
    									(!idata->srcprefix_f)?" (default)":"");
    }

	if(inet_ntop(AF_INET6, &(idata->dstaddr), pdstaddr, sizeof(pdstaddr)) == NULL){
		perror("inet_ntop()");
		exit(EXIT_FAILURE);
	}

	printf("IPv6 Destination Address: %s%s\n", pdstaddr, \
				((!idata->dstaddr_f)?" (all-routers link-local multicast)":""));

	printf("IPv6 Hop Limit: %u%s\n", hoplimit, (hoplimit_f)?"":" (default)");

	for(i=0; i<ndstoptuhdr; i++)
		printf("Destination Options Header (Unfragmentable part): %u bytes\n", dstoptuhdrlen[i]);

	for(i=0; i<nhbhopthdr; i++)
		printf("Hop by Hop Options Header: %u bytes\n", hbhopthdrlen[i]);

	for(i=0; i<ndstopthdr; i++)
		printf("Destination Options Header: %u bytes\n", dstopthdrlen[i]);

	if(idata->fragh_f)
		printf("Sending each packet in fragments of %u bytes (plus the Unfragmentable part)\n", nfrags);
	
	for(i=0;i<nlinkaddr;i++){
		if(ether_ntop(&linkaddr[i], plinkaddr, sizeof(plinkaddr)) == 0){
			puts("ether_ntop(): Error converting address");
			exit(EXIT_FAILURE);
		}

		printf("Source Link-layer Address option -> Address: %s\n", \
				((floods_f && !sllopta_f)?"(randomized for each packet)":plinkaddr));
	}
}