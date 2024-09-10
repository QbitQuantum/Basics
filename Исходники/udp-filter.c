void parse(char *country_input,
	   char *path_input,
	   char *domain_input,
	   char *ipaddress_input,
	   char *http_status_input,
	   char *referer_input,
	   char *bird,
	   char *db_path,
	   int minimum_field_count) {

	// GENERIC VARIABLES
	char *fields[MAX_FIELD_CNT];       // number of fields we expect in a single line
	int num_filters             = 0;   // total number of filters we detect from the command line
	int num_domain_filters      = 0;   // total number of domain filters
	int num_path_filters        = 0;   // total number of path filters
	int num_ipaddress_filters   = 0;   // total number of ipaddress filter
	int num_countries_filters   = 0;   // total number countries we want to restrict the filtering
	int num_http_status_filters = 0;   // total number of http status we want to restrict the filtering.
	int num_referer_filters     = 0;
	int required_hits           = 0;
	int bird_int                = 0;
	int i;

	int field_count_this_line=0;  // number of fields found in the current line

	char line[ LINE_BUF_SIZE ];
	char *ipaddr;
	char *url;
	char *http_status;
	char *referer;


	// DETERMINE NUMBER OF FILTERS
	if(params[DOMAIN_FILTER]){
		num_domain_filters = determine_num_obs(domain_input,comma_delimiter);
		required_hits+=1;
	}
	if(params[PATH_FILTER]){
		num_path_filters = determine_num_obs(path_input,comma_delimiter);
		required_hits+=1;
	}
	if(params[IP_FILTER]){
		num_ipaddress_filters = determine_num_obs(ipaddress_input, comma_delimiter);
		required_hits+=1;
	}
	if(params[GEO_FILTER]){
		if(country_input != NULL && strlen(country_input) >1){
			num_countries_filters = determine_num_obs(country_input, comma_delimiter);
			required_hits+=1;
		}
	}
	if(params[REFERER_FILTER]){
		num_referer_filters = determine_num_obs(referer_input, comma_delimiter);
		required_hits+=1;
	}
	if(params[HTTP_STATUS_FILTER]){
		if(http_status_input != NULL && strlen(http_status_input) >1){
			num_http_status_filters = determine_num_obs(http_status_input, comma_delimiter);
			required_hits+=1;
		}
	}

	num_filters = num_path_filters + num_domain_filters + num_ipaddress_filters
		+ num_countries_filters + num_http_status_filters + num_referer_filters;
	Filter filters[num_filters];

	// GEO_FILTER INITIALIZATION
	GeoIP *gi = NULL;    // initialize to suppress compiler warning
	char *countries[num_countries_filters];
	char *area;

	// FILTER INITIALIZATION
	if(params[DOMAIN_FILTER]){
		init_domains(filters, domain_input, comma_delimiter);
	} else {
		domain_input=NULL;
	}

	if(params[PATH_FILTER]){
		init_paths(filters, path_input, comma_delimiter);
	} else {
		path_input = NULL;
	}

	if(params[IP_FILTER]){
		init_ip_addresses(filters, ipaddress_input, comma_delimiter);
	} else {
		ipaddress_input = NULL;
	}

	if (params[REFERER_FILTER]){
		init_domains(filters, referer_input, comma_delimiter);
	} else {
		referer_input = NULL;
	}

	if( ! (params[GEO_FILTER] || (recode & GEO)) ) {
		country_input = NULL;
	} else {
		init_countries(countries, country_input, num_countries_filters, comma_delimiter);
		bird_int = init_bird_level(bird);
		/*
		 *  Before changing the type of cache, have a look at this benchmark:
		 *  http://www.maxmind.com/app/benchmark
		 *  and choose wisely.
		 */
		switch(bird_int){
		case COUNTRY:
			if(db_path!=NULL){
				db_country_path=db_path;
			}
			gi = GeoIP_open(db_country_path, GEOIP_MEMORY_CACHE);
			break;

		case REGION:
			if(db_path!=NULL){
				db_region_path=db_path;
			}
			gi = GeoIP_open(db_region_path, GEOIP_MEMORY_CACHE);
			break;

		case CITY:
			if(db_path!=NULL){
				db_city_path=db_path;
			}
			gi = GeoIP_open(db_city_path, GEOIP_MEMORY_CACHE);
			break;

		case LAT_LON:
			if(db_path!=NULL){
				db_city_path=db_path;
			}
			gi = GeoIP_open(db_city_path, GEOIP_MEMORY_CACHE);
			break;

		case EVERYTHING:
			if(db_path!=NULL){
				db_city_path=db_path;
			}
			gi = GeoIP_open(db_city_path, GEOIP_MEMORY_CACHE);
			break;
		}

		if (gi == NULL) {
			fprintf(stderr, "Error opening MaxMind Geo database.\n");
			fprintf(stderr, "Path used for country database:%s\n", db_country_path);
			fprintf(stderr, "Path used for region database:%s\n", db_region_path);
			fprintf(stderr, "Path used for city database:%s\n", db_city_path);
			exit(EXIT_FAILURE);
		} else {
			if(verbose_flag){
				char *db_info =GeoIP_database_info(gi);
				unsigned char db_edition = GeoIP_database_edition(gi);
				GeoIPDBTypes geodbtype = (GeoIPDBTypes)db_info;
				fprintf(stderr,"Maxmind database: %i; version: %i\n", db_edition, geodbtype);
			}
		}
	}

	if(params[HTTP_STATUS_FILTER]){
		init_http_status(filters, http_status_input, comma_delimiter);
	} else {
		http_status_input = NULL;
	}


	if (verbose_flag){
		fprintf(stderr, "num_path_filters:%d\tnum_domain_filters:%d"
			"\tnum_http_status_filters:%d\tip_address_count:%d"
			"\tcountries_count:%d\treferer_count:%d\n",
			num_path_filters, num_domain_filters, num_http_status_filters,
			num_ipaddress_filters, num_countries_filters, num_referer_filters);
	}


	// Now that we have initilaized all the filters,
	// do the actual filtering and conversion of the
	// incoming data.
	while ( true ) {
		int found =0;
		area = NULL;

		char *r;
		r=fgets(line, LINE_BUF_SIZE, stdin);
		if(!r) {
			break;
		}

		i = 0;
		char *p;
		do {
			fields[i] = r;
			//strsep(&r, ws_delimiter);
			p = strchr( r, *ws_delimiter );
			i++;
                        if ( NULL == p )
                                break;
                        *p = 0;
                        r = p + 1;
		} while (i < MAX_FIELD_CNT);

		if (i < minimum_field_count || i == MAX_FIELD_CNT){
			continue;    // ignore line since field count is outside expected range
		}


		// we found i fields in this line.
		field_count_this_line = i;

		ipaddr        = fields[4];
		http_status   = fields[5];
		url           = fields[8];
		referer       = fields[11];
		//ua            = fields[13]; // necessary for bot detection


		if (url != NULL) {

			if (params[DOMAIN_FILTER]){
				found += match_domain(url, filters, num_domain_filters,verbose_flag);
			}

			if (params[PATH_FILTER]){
				found += match_path(url, filters, num_path_filters,verbose_flag);
			}

			if (params[HTTP_STATUS_FILTER]){
				found += match_http_status(http_status, filters, num_http_status_filters,verbose_flag);
			}

			if (params[IP_FILTER]){
				found += match_ip_address(ipaddr, filters, num_ipaddress_filters,verbose_flag);
			}

			if (params[REFERER_FILTER]){
				found += match_domain(referer, filters, num_referer_filters,verbose_flag);
			}

			if (params[GEO_FILTER]){
				area = geo_lookup(gi, ipaddr, bird_int);
				found += geo_check(area, countries, num_countries_filters,verbose_flag);
				if (verbose_flag){
					fprintf(stderr, "IP address: %s was geocoded as: %s\n", ipaddr, area);
				}
			}
		}

		// required_hits will equal the number of filters
		// given.  These include ip, domain, path, status,
		// and country filtering.  If no filters were given,
		// then found will be 0 AND require_hits will be 0,
		// allowing the line to pass through.
		if (found >= required_hits) {
			// if we need to replace the IP addr
			// because recode is GEO or ANONYMIZE or both
			if (recode)
			{
				// geocode if we haven't already geocoded and
				// we'll be needing the geocoded string when
				// replacing the IP.
				if (area == NULL && (recode & GEO)) {
					area = geo_lookup(gi, ipaddr, bird_int);
				}

				// replace the ip address in fields.
				// if area is not null, it will be appended
				// to the ip address.  If (recode & ANONYMIZE) is
				// true, then the IP will be replaced.
				replace_ip_addr(fields, area, (recode & ANONYMIZE));
			}

			// print output to stdout
			for (i=0;i<field_count_this_line;++i){
				if (i!=0){
					FPUTS(ws_delimiter, stdout);
				}
				FPUTS(fields[i], stdout);
			}

		}

		if (verbose_flag) {
			fprintf(stderr, "ipaddr: '%s', url: '%s, status: %s'\n", ipaddr, url, http_status);
		}

	}
	free_memory(filters, path_input, domain_input,num_filters, gi, countries, num_countries_filters);
}