Ref speedtest_cmd(ref_list args){

	puts("Starting test...");

	bool doplot = true; keepgoing = true; 

	Fun f = (Fun) args->list[0]->inst;
	int min = (int) (*(float*) ((Var)args->list[1]->inst)->val);
	int max = (int) (*(float*) ((Var)args->list[2]->inst)->val);
	int step = (int) (*(float*) ((Var)args->list[3]->inst)->val);
		
	if ( min > max || step == 0) {
		set_err(ENOVAL, "infinite tests are not allowed");
		return NULL;
	}

	/* Optional parameter */
	if (args->length > 4 && cmptype_ref(FLOAT, args->list[4])) {
		int countdown = (int) (*(float*) ((Var)args->list[4]->inst)->val);
		signal(SIGALRM, stop_speedtest);
		alarm(countdown);
	} 
	
	
	/* Points list */	
	clock_t* y_time = malloc (sizeof(clock_t) * (max-min)/step + 1);
	int* x_size = malloc (sizeof(int) * (max-min)/step + 1);
	if (y_time == NULL || x_size == NULL){
		free(x_size); free(y_time);
		return NULL;
	}

	
	int i,j;
	for ( i = min, j=0; i <= max && keepgoing ; i += step, j++){
		
		/* Generate matrices. 
		   Note: they don't need to be initialized 
		*/
		Matrix m1 = newMatrix(i,i), m2 = newMatrix(i,i), ret = NULL;
		float* f1 = malloc(sizeof(float));
		if (m1 == NULL || m2 == NULL || f1 == NULL){ 
			perror("");
			keepgoing = false; doplot = false;
		}

		/* Start test */
		clock_t start = clock();

		if (f->fun == mult_call) {
			ret = multiplication(m1,m2);

		} else if ( f->fun == sub_call) {
			ret = soustraction(m1,m2);

		} else if (f->fun == addition_call){
			ret = addition(m1,m2);

		} else if (f->fun == transpose_call){
			ret = transpose(m1);	

		} else if (f->fun == determinant_call){
			determinant(m1, f1);	

		} else if (f->fun == invert_call){
			invert(m1,&ret);

		} else if (f->fun == rank_call ){
			rank(m1);
		} else {
			printf("Sorry...cannot test this function\n");
			keepgoing = false; doplot = false;
		}
		
		
		/* Finish test */
		clock_t end = clock();
	
		/* Store result */	
		x_size[j] = i; y_time[j] = end-start;
		
		dropMatrix(m1);
		dropMatrix(m2);
		dropMatrix(ret);
		free(f1);
	}

	alarm(0); // Remove countdown

	if (doplot == true) plot(args->list[0]->name, x_size, y_time, j);

	free(x_size); free(y_time);

	return NO_REF;
}