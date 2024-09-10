int main(void){
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 65536);
	
	uint64_t cpus = 6;
	
	pthread_t threads[cpus];
	doRangeArg arg[cpus];
	
	uint64_t max = sqrtl(MAX);
	uint64_t *fsms = malloc(max*sizeof(uint64_t));
	for(uint64_t i = 0; i < max; ++i){
		fsms[i] = 1;
	}
	for(uint64_t p = 2; p < max; ++p){
		if(fsms[p] != 1){//p is not prime
			continue;
		}//p is prime, mark off its multiples
		for(uint64_t m = p; m < max; m += p){
			mark(fsms, p, m);
		}
	}
	
	for(uint64_t i = 0; i < cpus; ++i){
		arg[i] = (doRangeArg){.start = i + 1, .step = cpus, .fsms = fsms, .max = max};
		if(pthread_create(&threads[i], &attr, doRange, &arg[i])){
			return 1;
		}
	}
	for(uint64_t i = 0; i < cpus; ++i){
		if(pthread_join(threads[i], NULL)){
			return 1;
		}
	}
	
	free(fsms);
	printf("%"PRIu64"\n", s);
}