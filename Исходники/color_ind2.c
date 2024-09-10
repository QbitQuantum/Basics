int main(int argc, char*argv[]) {
	char *gtm_fname=0;

	for (int i=1;i<argc;i++) {
		if (argv[i][0]!='-') {
			if (gtm_fname==0) {
				gtm_fname=argv[i];
			} else {
				fprintf(stderr, "ERROR: Only one input file is allowed\n.");
				exit(1);
			}
		} else {
			if (strcmp("-cost", argv[i])==0) {
				const int no_costs=3;
				i++;
				if (argv[i][0]==0) {
					printf("Cost tuple cannot be empty\n");
					exit(1);
				}
				for (int j=0;j<strlen(argv[i]);j++) {
					if (!isdigit(argv[i][j])) {
						printf("Invalid cost tuple %s\n", argv[i]);
						exit(1);
					}
				}
				if (strlen(argv[i])%no_costs!=0) {
					printf("Cost tuple %s length is not a multiple of %d.\n", argv[i], no_costs);
					exit(1);
				}
				int d=strlen(argv[i])/no_costs;
				switch_cost=0; visit_cost=0; absence_cost=0; 
				int j=0;
				for (int k=0;k<d;k++) switch_cost=switch_cost*10+argv[i][j++]-'0';
				for (int k=0;k<d;k++) absence_cost=absence_cost*10+argv[i][j++]-'0';
				for (int k=0;k<d;k++) visit_cost=visit_cost*10+argv[i][j++]-'0';
				//fprintf(stderr, "%d %d %d\n", switch_cost, absence_cost, visit_cost);

			} else if (strcmp("-switch", argv[i])==0) {
				assert(i+1<argc);
				switch_cost=atoi(argv[++i]);
			} else if (strcmp("-diff", argv[i])==0) {
				assert(i+1<argc);
				visit_cost=atoi(argv[++i]);
			} else if (strcmp("-absence", argv[i])==0) {
				assert(i+1<argc);
				absence_cost=atoi(argv[++i]);
			} else if (strcmp("-glimit", argv[i])==0) {
				assert(i+1<argc);
				glimit=atoi(argv[++i]);
				assert(glimit>=0);
			} else if (strcmp("-ilimit", argv[i])==0) {
				assert(i+1<argc);
				ilimit=atoi(argv[++i]);
				assert(ilimit>=0);
			} else if (strcmp("-1char", argv[i])==0) {
				color_type = COLOR_1CHAR;
			} else if (strcmp("-sep", argv[i])==0) {
				color_type = COLOR_SEP;
			} else if (strcmp("-q", argv[i])==0) {
                quiet = 1;
                ilimit = 0;
			} else {
				fprintf(stderr, "Unknown option %s\n", argv[i]);
				print_usage(argv[0]);
			}
		}
	}

	if (gtm_fname==0) {
		print_usage(argv[0]);
		exit(1);
	}

	if (access(gtm_fname, F_OK)!=0) {
		fprintf(stderr, "File %s does not exist\n", gtm_fname);
		exit(1);
	}

	gtm_data gtm;
	if (load_gtmfile(gtm_fname, &gtm)) {
		printf("Error loading gtm file: %s\n", gtm_fname);
		exit(1);
	}

	const int group_count = gtm.group_count;
	const int ind_count = gtm.ind_count;
	const int time_count = gtm.time_count;
	const int *group_time = gtm.group_time;
	const int *group_size = gtm.group_size;

	int *ind_exists = gtm.ind_exists;

	int *ind_time_group[ind_count];
	for (int i=0;i<ind_count;i++) {
		ind_time_group[i] = MAlloc(sizeof(int)*time_count);
		for (int t=0;t<time_count;t++) {
			ind_time_group[i][t]=-1;
		}
	}
	linked_group *p=gtm.group_array[0];
	for (int i=0;p!=0;p=p->next) {
		for (int j=0;j<p->member_count;j++) {
			//printf("i %d t %d g %d\n", p->member[j], p->timestep, i);
			ind_time_group[p->member[j]][p->timestep]=i;
		}
		i++;
	}
	//
	//for (int i=0;i<ind_count;i++) {
	//	for (int t=0;t<time_count;t++) {
	//		if (ind_time_group[i][t]<0) {
	//			printf(" %2c", '.');
	//		} else {
	//			printf(" %2d", ind_time_group[i][t]);
	//		}
	//	}
	//	printf("\n");
	//}
	//


	int group_color[group_count];
	memset(group_color, -1, sizeof(int)*group_count);

	// detect color_type from stdin
	if (color_type==COLOR_DEFAULT) {
		color_type = detect_type_from_abc(100);

		if (color_type==COLOR_DEFAULT) {
			int nspace = detect_type_by_space_counting();
			if (group_count-1 == nspace) {
				color_type = COLOR_SEP;
			} else if (time_count-1 == nspace) {
				color_type = COLOR_1CHAR;
			} else {
				assertf(color_type, "Cannot detect color type.\n"
					"ind_count %d time_count %d group_count %d nspace %d.\n"
					"Use -sep or -1char.", 
					ind_count, time_count, group_count, nspace);
			}
			//fprintf(stderr, "detect %s\n", 
			//	color_type==COLOR_1CHAR?"1char":(color_type==COLOR_SEP?"sep":"unknown"));
		}
	}

	int gcount=0;
	for (;;) {
		// read a line of group colors
		int rc = read_group_color(&gtm, group_color);
		int color_count=0;
		for (int g=0;g<group_count;g++) {
			if (group_color[g]>color_count) color_count=group_color[g];
		}
		color_count++;
		//if (color_count>ind_count) {
		//	fprintf(stderr, "WARNING! color_count %d > ind_count %d\n", 
		//		color_count, ind_count);
		//}

		if (rc==-1) break;
		if (rc==0) continue;

		if (ilimit==1) {
			process_group_color_limit1(&gtm, group_color, group_count, 
				color_count, &ind_time_group[0]);
			break;
		} else {
			process_group_color_limitn(&gtm, group_color, group_count, 
				color_count, &ind_time_group[0]);
			if (++gcount >= glimit) break;
			printf("\n");
		}
	}

	return 0;
}