void main()
{
	FILE *fp;
	int i, j, k, count;
	
	// I don't use srand
	fp = fopen("star.in","w");
	assert(fp != NULL);
	
/*  -----------------------------   Graph Generation ------------------------  */
	memset(gr, 0, sizeof(gr));
	memset(forbidden, 0, sizeof(forbidden));
	switch(gr_type){
		case GRAPH_TYPE_ANY:
			for(i = 0; i < n; i++)
				for(j = i + 1; j < n; j++)
					gr[i][j] = gr[j][i] = (rand() % 100 < density);

			// Make it connected
			while(1){
				memset(mark, 0, sizeof(mark));
				dfs(0);
				for(i = 0; i < n; i++)
					if(!mark[i]) break;         // unmarked vertex
				if(i == n || mark[i]) break;
				else{
					while(1){					// find a vertex in the set v(1)
						j = rand() % n;
						if(mark[j]) break;
					}
					gr[i][j] = gr[j][i] = 1;	// connect
				}
			}
			break;
		
		case GRAPH_TYPE_TREE:
			memset(mark, 0, sizeof(mark));
			memset(degree, 0 ,sizeof(degree));
			mark[0] = 1;
			for(i = 0; i < n - 1; i++){
				while(1){
					j = rand() % n;
					if(mark[j]) break;
				}
				while(1){
					k = rand() % n;
					if(!mark[k]) break;
				}
				gr[j][k] = gr[k][j] = 1;
				degree[j]++;
				degree[k]++;
				mark[k] = 1;
			}
			for(i = 0; i < n; i++)
				if(degree[i] > 1) forbidden[i] = 1;
			break;
		
		case GRAPH_TYPE_STAR:
			for(i = 1; i < branch; i++){
				gr[0][i] = gr[i][0] = 1;
				last[i-1] = i;
			}
			for(i = branch; i < n; i++){		// connect to the end of a chain
				j = rand() % branch;
				gr[i][last[j]] = gr[last[j]][i] = 1;
				last[j] = i;
			}
			for(i = 0; i < branch; i++)
				forbidden[last[i]] = 1;
			for(i = 0; i < n; i++)
				forbidden[i] = 1 - forbidden[i];
			break;

		case GRAPH_TYPE_RING:
			for(i = 0; i < n; i++)
				gr[i][(i+1)%n] = gr[(i+1)%n][i] = 1;
			break;
	}

	edgecount = 0;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(gr[i][j]) edgecount++;

/*  ----------------  Skills Generation ----------------------  */
	memset(know, 0, sizeof(know));
	memset(skill_ok, 0, sizeof(skill_ok));
	for(i = 0; i < n; i++){
		if(forbidden[i]) continue;
		count = rand() % (skill_upper_bound - skill_lower_bound + 1) + skill_lower_bound;
		for(j = 0; j < count; j++)
			while(1){
				k = rand() % m;
				if(!know[i][k]){
					know[i][k] = 1;
					skill_ok[k] = 1;
					break;
				}
			}

	}
	// Check if any skill is NOT learned by ANYONE
    for(i = 0; i < m; i++)
		if (!skill_ok[i]){
			while(1){
				j = rand() % n;
				if(!forbidden[j]) break;
			}
			know[j][i] = 1;
		}
	
/*  ------------------- Output -----------------------  */
	fprintf(fp, "%d %d\n", n, m);
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++)
			fprintf(fp, "%d ", know[i][j]);
		fprintf(fp, "\n");
	}
	for(i = 0; i < n; i++){
		j = rand() % 20 + 1;
		k = rand() % 20 + 1;
		fprintf(fp, "%d %d\n", j, k);
	}
	fprintf(fp, "%d\n", edgecount);
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(gr[i][j]) fprintf(fp, "%d %d\n", i+1, j+1);

	fclose(fp);
}