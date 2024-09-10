void data_init()
{
	int i;

	data.Nth = 4;

	data.iord = 2;

	data.lb = -1e38;
	data.ub = +1e38;

	data.lowerbound = malloc(data.Nth*sizeof(double));
	data.upperbound = malloc(data.Nth*sizeof(double));
	data.theta = malloc(data.Nth*sizeof(double));

	for (i = 0; i < data.Nth; i++) data.lowerbound[i] = data.lb;
	for (i = 0; i < data.Nth; i++) data.upperbound[i] = data.ub;
	for (i = 0; i < data.Nth; i++) data.theta[i] = 1.0;

	data.uh = 1e-4;
	data.diffstep = malloc(data.Nth*sizeof(double));
	for (i = 0; i < data.Nth; i++) data.diffstep[i] = data.uh;
	data.posdef = -1;


/**********************************************/
// PARAMS
/**********************************************/

	/* USER-DEFINED VALUES */
	FILE *f = fopen("grad.par", "r");
	if (f == NULL) {
		return;
	}

	/*
	Nth		4
	order		2
	Bdef		-4	4

	lb		0 0 0 0 
	ub		2 2 2 2
	theta		1 1 1 1

	Hdef		1e-4
	diffstep	1-e4 1e-4 1e-4 1e-4 
	posdef		-1
	*/

	char line[256];

	int line_no = 0;
	while (fgets(line, 256, f)!= NULL) {
		line_no++;
		if ((line[0] == '#')||(strlen(line)==0)) {
			printf("ignoring line %d\n", line_no);
			continue;
		}

		if (strstr(line, "Nth")) {
			sscanf(line, "%*s %d", &data.Nth);
		}
		else if (strstr(line, "order")) {
			sscanf(line, "%*s %d", &data.iord);
		}
		else if (strstr(line, "Bdef")) {
			sscanf(line, "%*s %lf %lf", &data.lb, &data.ub);
		}
		else if (strstr(line, "Hdef")) {
			sscanf(line, "%*s %lf", &data.uh);
		}
		else if (strstr(line, "posdef")) {
			sscanf(line, "%*s %d", &data.posdef);
		}
	}

	rewind(f);
	line_no = 0;

	free(data.lowerbound);
	free(data.upperbound);
	free(data.theta);
	free(data.diffstep);
	data.lowerbound = (double *)malloc(data.Nth*sizeof(double));
	data.upperbound = (double *)malloc(data.Nth*sizeof(double));
	data.theta = (double *)malloc(data.Nth*sizeof(double));
	data.diffstep = (double *)malloc(data.Nth*sizeof(double));

	for (i = 0; i < data.Nth; i++) data.lowerbound[i] = data.lb;
	for (i = 0; i < data.Nth; i++) data.upperbound[i] = data.ub;
	for (i = 0; i < data.Nth; i++) data.theta[i] = 1.0;
	for (i = 0; i < data.Nth; i++) data.diffstep[i] = data.uh;

	rewind(f);
	while (fgets(line, 256, f)!= NULL) {
		line_no++;

		if ((line[0] == '#')||(strlen(line)==0)) continue;

		if (strstr(line, "theta")) {
			char *p;
			p = strtok(line, " \t\n");
			for (i = 0; i < data.Nth; i++) {
				p = strtok(NULL, " \t\n");
				if (!p) break;
				data.theta[i] = atof(p);
                        }
                }
		else if (strstr(line, "lb")) {
			char *p;
			p = strtok(line, " \t\n");
			for (i = 0; i < data.Nth; i++) {
				p = strtok(NULL, " \t\n");
				if (!p) break;
				data.lowerbound[i] = atof(p);
                        }
                }
		else if (strstr(line, "ub")) {
			char *p;
			p = strtok(line, " \t\n");
			for (i = 0; i < data.Nth; i++) {
				p = strtok(NULL, " \t\n");
				if (!p) break;
				data.upperbound[i] = atof(p);
                        }
                }
		else if (strstr(line, "diffstep")) {
			char *p;
			p = strtok(line, " \t\n");
			for (i = 0; i < data.Nth; i++) {
				p = strtok(NULL, " \t\n");
				if (!p) break;
				data.diffstep[i] = atof(p);
                        }
                }
        }

	for (i = 0; i < data.Nth; i++) {
                printf("param %d: %f < %f < %f: %f\n", i, data.lowerbound[i], data.theta[i], data.upperbound[i], data.diffstep[i]);
        }

	fclose(f);


}