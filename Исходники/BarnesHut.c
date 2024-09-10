void create_bodies() {
	FILE* inputdataf = fopen("inputData", "r");
	int i = 0;
	char line[100];
	char* token;
	char* end;
	double d = 0.0;
	for (i = 0; i < nbodies; i++) {

		//		printf("i = %d \n", i);
		bodies[i] = malloc(sizeof(node_t));
		leaf_t* leaf = malloc(sizeof(leaf_t));

		fgets(line, 100, inputdataf);

		//		printf("%s\n", line);

		token = strtok(line, " ");

		d = strtold(token, &end);
		leaf->mass = d;
		//		printf("%lf\n",d);
		token = strtok(NULL, " ");
		d = strtold(token, &end);
		leaf->pos[0] = d;
		//		printf("%lf\n",d);
		token = strtok(NULL, " ");
		d = strtold(token, &end);
		leaf->pos[1] = d;
		//		printf("%lf\n",d);
		token = strtok(NULL, " ");
		d = strtold(token, &end);
		leaf->pos[2] = d;
		//		printf("%lf\n",d);
		token = strtok(NULL, " ");
		d = strtold(token, &end);
		leaf->vel[0] = d;
		//		printf("%lf\n",d);
		token = strtok(NULL, " ");
		d = strtold(token, &end);
		leaf->vel[1] = d;
		//		printf("%lf\n",d);
		token = strtok(NULL, " ");
		d = strtold(token, &end);
		leaf->vel[2] = d;
		//		printf("%lf\n",d);

		leaf->acc[0] = 0.0;
		leaf->acc[1] = 0.0;
		leaf->acc[2] = 0.0;

		leafs[i] = *leaf;

		bodies[i]->type = 0;
		bodies[i]->cell.leaf = &leafs[i];
		bodies[i]->mass = &bodies[i]->cell.leaf->mass;
		bodies[i]->pos = bodies[i]->cell.leaf->pos;

		free(leaf);
	}

	fclose(inputdataf);
}