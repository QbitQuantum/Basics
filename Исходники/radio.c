void sim_radio_init()
{
	//! initialize node id and location
	FILE *fid;
	char line_buf[LINE_BUF_SIZE];    // line buffer
	int j = 0;

	if((fid = fopen(topofile, "r")) == NULL){
		char* sosrootdir;
		char newtopofile[256];
		sosrootdir = getenv("SOSROOT");
		strcpy(newtopofile, sosrootdir);
		printf("Unable to open %s\n", topofile);
		strcat(newtopofile, "/platform/sim/topo.def\0");
		if((fid = fopen(newtopofile, "r")) == NULL){
			printf("Unable to open %s\n", newtopofile);
			exit(1);
		}
		else
			topofile = newtopofile;
	}
	printf("Using topology file %s\n", topofile);
	// remove comments
	do{
		fgets(line_buf, LINE_BUF_SIZE, fid);
	} while(line_buf[0] == '#');

	if(sscanf(line_buf, "%d", &totalNodes) != 1){
		fprintf(stderr, "no data in %s\n", topofile);
		exit(1);
	}

	topo_array = (Topology*)malloc((totalNodes + 1) * sizeof(Topology));
	if (topo_array == NULL){
		fprintf(stderr, "not enough memory\n");
		exit(1);
	}

	for(j = 0; j < totalNodes; j++){
		do{
			// remove comments
			fgets(line_buf, LINE_BUF_SIZE, fid);
		}while(line_buf[0] == '#');
		if(sscanf(line_buf, "%d %d %d %d %d %u",
					&topo_array[j].id,
					&topo_array[j].unit,
					&topo_array[j].x,
					&topo_array[j].y,
					&topo_array[j].z,
					&topo_array[j].r2) != 6){
			fprintf(stderr, "not enough definitions in %s: %s\n", topofile, line_buf);
			exit(1);
		}
		//topo_array[j].id = j;
		topo_array[j].type = TOPO_TYPE_OTHER;
		topo_array[j].sock = -1;
	}
#if 0
	print_nodes();
	exit(1);
#endif
	if(fclose(fid) != 0){
		perror("fclose");
		exit(1);
	}

	// finding node id by finding available port
	//for(j = 1; j <= totalNodes; j++)
	{
		int sock;
		int myj = getj(ker_id());
		struct sockaddr_in name;
		sock = socket(AF_INET, SOCK_DGRAM, 0);

		if (sock < 0) {
			perror("opening datagram socket");
			exit(1);
		}

		/* Create name with wildcards. */
		name.sin_family = AF_INET;
		name.sin_addr.s_addr = INADDR_ANY;
		//		name.sin_port = htons(20000 + ker_id());
		name.sin_port = htons( get_sin_port(ker_id()) );

		if (bind(sock, (struct sockaddr *)&name, sizeof(name)) == 0) {
			//node_address = j;
			// successfully get an id
			topo_array[myj].sock = sock;
			topo_array[myj].type = TOPO_TYPE_SELF;
			topo_self = topo_array[myj];
			//! assign sos_info
			node_loc.x = topo_self.x;
			node_loc.y = topo_self.y;
			node_loc.z = topo_self.z;
			node_loc.unit = topo_self.unit;
		}else{
			fprintf(stderr, "Unable to allocate UDP for this node!\n");
			fprintf(stderr, "Perhaps you are using the same node ID\n");
			fprintf(stderr, "Use -n <node address> to specify different address\n\n");
			exit(1);
		}
	}
	{
		uint16_t id;
		node_loc_t self;
		id = ker_id();
		self = ker_loc();
		if((id != topo_self.id) || (self.x != topo_self.x) ||
				(self.y != topo_self.y) || (self.z != topo_self.z) ||
				(self.unit != topo_self.unit)){
			fprintf(stderr, "topo file and self settings do not agree.\n");
			fprintf(stderr, "ker_id() = %d : topo_self.id = %d\n",
					id, topo_self.id);
			fprintf(stderr, "self.unit = %d : topo_self.unit = %d\n",
					self.unit, topo_self.unit);
			fprintf(stderr, "self.x = %d : topo_self.x = %d\n",
					self.x, topo_self.x);
			fprintf(stderr, "self.y = %d : topo_self.y = %d\n",
					self.y, topo_self.y);
			fprintf(stderr, "self.z = %d : topo_self.z = %d\n",
					self.z, topo_self.z);
			exit(1);
		}
	}

	for(j = 0; j < totalNodes; j++){
		uint32_t r2;
		uint16_t id;
		node_loc_t self, neighbor;
		id = ker_id();
		self = ker_loc();
		if(topo_array[j].type == TOPO_TYPE_SELF) continue;
		neighbor.unit = topo_array[j].unit;
		neighbor.x = topo_array[j].x;
		neighbor.y = topo_array[j].y;
		neighbor.z = topo_array[j].z;
		r2 = ker_loc_r2(&self,&neighbor);
		if(r2 < 0){
			fprintf(stderr, "units for neighbor do not agree.\n");
			fprintf(stderr, "self.unit = %d : neighbor.unit = %d.\n",
					self.unit, neighbor.unit);
			exit(1);
		}
		DEBUG("neighbor %d r2 = %d, self r2 = %d\n", topo_array[j].id, r2, topo_self.r2);
		if(r2 <= topo_self.r2){
			topo_array[j].type = TOPO_TYPE_NEIGHBOR;
			DEBUG("node %d is reachable\n", topo_array[j].id);
		}
	}
	{
		struct hostent	*hostptr;
		char theHost [MAXLENHOSTNAME];
		unsigned long hostaddress;

		/* find out who I am */

		if ((gethostname(theHost, MAXLENHOSTNAME))<0) {
			perror ("could not get hostname");
			exit(1);
		}
		//DEBUG("-- found host name = %s\n", theHost);

		if ((hostptr = gethostbyname (theHost)) == NULL) {
			perror ("could not get host by name, use 127.0.0.1");
			if(( hostptr = gethostbyname ("127.0.0.1") ) == NULL ) {
				perror ("Cannot get host 127.0.0.1");
				exit(1);
			}

		}
		hostaddress = *((unsigned long *) hostptr->h_addr);

		/* init the address structure */
		sockaddr.sin_family    	= AF_INET;
		sockaddr.sin_port		= htons( get_sin_port(ker_id()) );
		sockaddr.sin_addr.s_addr 	= hostaddress;
	}
	//! assign locations
	//node_loc.x = (uint16_t)(topo_self.x);
	//node_loc.y = (uint16_t)(topo_self.y);
	//print_nodes();
}