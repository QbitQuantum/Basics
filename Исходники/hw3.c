void print_entry(list_t* list) {
  	struct in_addr src_ip;
  	src_ip.s_addr = list->source->ip;
  	printf("Source IP      : %s\n", inet_ntoa(src_ip));

  	struct in_addr dest_ip;
  	dest_ip.s_addr = list->source->dest_ip;
  	printf("Destination IP : %s\n", inet_ntoa(dest_ip));

  	printf("Number of scans: %u\n", list->source->dest_ports->size);

  	printf("Scan type      : ");
  	switch(list->source->portscanner) {
  	case SYN_SCAN:
	  	printf("SYN scan, random order of ports\n");
  		break;
  	case FIN_SCAN:
  		printf("FIN scan, random order of ports\n");
  		break;
  	case XMAS_SCAN:
  		printf("XMAS scan, random order of ports\n");
  		break;
	case NUL_SCAN:
  		printf("Null scan, random order of ports\n");
  		break;
	case CONN_SCAN:
  		printf("TCP Connect scan, random order of ports\n");
    	break;
  	case HORIZ_SCAN:
  		printf("Horizonal scan, random order of ports\n");
  		break;

  	default:
  		break;
  	}


  	// char ts_start[64]; 
  	// time_t start_time = list->source->first_packet_time.tv_sec; //make first_packet_time field
  	// struct tm* start_time_struc = localtime(&start_time);
  	// strftime(ts_start, sizeof(ts_start), "%H:%M:%S", start_time_struc);
  	// int us_start = (int)list->source->first_packet_time.tv_usec;
  	// printf("First Packet: %s.%06d, ", ts_start, us_start); //I think this format may be off? check his comments for hw2

  	// char ts_end[64]; 
  	// time_t end_time = list->source->last_packet_time.tv_sec; 
  	// struct tm* end_time_struc = localtime(&end_time);
  	// strftime(ts_end, sizeof(ts_end), "%H:%M:%S", end_time_struc);
  	// int us_end = (int)list->source->last_packet_time.tv_usec;
  	// printf("Last Packet: %s.%06d, ", ts_end, us_end); //I think this format may be off? check his comments for hw2
  	
  	double sec_start = list->source->first_packet_time.tv_sec;
  	double usec_start = list->source->first_packet_time.tv_usec;
  	double sec_end = list->source->last_packet_time.tv_sec;
  	double usec_end = list->source->last_packet_time.tv_usec;

  	// double sec_diff = sec_end - sec_start;
  	// double usec_diff = (double_(usec_end - usec_start)/1000000);
  	//printf("%f\n", usec_start);
  	double total_start = sec_start + usec_start/1000000;
  	double total_end = sec_end + usec_end/1000000;
  	//printf("%f, %f\n", total_start, total_end);
  	double diff = total_end-total_start;
  	printf("Time taken     : %.4f\n", diff);
  	//printf("%f, %f, %f, %f\n", sec_start, usec_start, sec_end, usec_end);
  	//printf("start time: %.4f  end time: %.4f\n", (double)sec_end-sec_start, (double)usec_end-usec_start);

}