int main(int argc, char * * argv)
{
	struct s_pwd pwd;
	struct s_pwd pwd2;

	unsigned int max_lvl, max_len;
	unsigned long long start, end;

	max_lvl = 0;
	max_len = 0;
	start = 0;
	end = 0;

	if((argc<3) || (argc>6))
	{
		printf("Usage: %s statfile max_lvl [max_len] [start] [end]\n", argv[0]);
		return -1;
	}
		
	max_lvl = atoi(argv[2]);

	if(argc>3)
		max_len = atoi(argv[3]);
	if(argc>4)
		start = atoll(argv[4]);
	if(argc>5)
		end = atoll(argv[5]);

	init_probatables(argv[1]);

	if(max_len==0)
	{
		for(max_len=6;max_len<20;max_len++)
		{
			nbparts = mem_alloc(256*(max_lvl+1)*sizeof(long long)*max_len);
			printf("len=%u (%lu KB for nbparts) ", max_len, 256UL*(max_lvl+1)*max_len*sizeof(long long)/1024);
			memset(nbparts, 0, 256*(max_lvl+1)*max_len*sizeof(long long));
			nb_parts(0, 0, 0, max_lvl, max_len);
			if(nbparts[0] > 1000000000)
				printf("%lld G possible passwords (%lld)\n", nbparts[0] / 1000000000, nbparts[0]);
			else if(nbparts[0] > 10000000)
				printf("%lld M possible passwords (%lld)\n", nbparts[0] / 1000000, nbparts[0]);
			else if(nbparts[0] > 10000)
				printf("%lld K possible passwords (%lld)\n", nbparts[0] / 1000, nbparts[0]);
			else 
				printf("%lld possible passwords\n", nbparts[0] );
			free(nbparts);
		}
		goto fin;
	}

	if(max_lvl==0)
	{
		for(max_lvl=100;max_lvl<350;max_lvl++)
		{
			nbparts = mem_alloc(256*(max_lvl+1)*sizeof(long long)*max_len);
			printf("lvl=%u (%lu KB for nbparts) ", max_lvl, 256UL*(max_lvl+1)*max_len*sizeof(long long)/1024);
			memset(nbparts, 0, 256*(max_lvl+1)*max_len*sizeof(long long));
			nb_parts(0, 0, 0, max_lvl, max_len);
			if(nbparts[0] > 1000000000)
				printf("%lld G possible passwords (%lld)\n", nbparts[0] / 1000000000, nbparts[0]);
			else if(nbparts[0] > 10000000)
				printf("%lld M possible passwords (%lld)\n", nbparts[0] / 1000000, nbparts[0]);
			else if(nbparts[0] > 10000)
				printf("%lld K possible passwords (%lld)\n", nbparts[0] / 1000, nbparts[0]);
			else 
				printf("%lld possible passwords\n", nbparts[0] );
			free(nbparts);
		}
		goto fin;
	}
		
	nbparts = mem_alloc(256*(max_lvl+1)*sizeof(long long)*max_len);
	fprintf(stderr, "allocated %lu KB for nbparts\n", 256UL*(max_lvl+1)*max_len*sizeof(long long)/1024);
	memset(nbparts, 0, 256*(max_lvl+1)*max_len*sizeof(long long));

	nb_parts(0, 0, 0, max_lvl, max_len);
	if(nbparts[0] > 1000000000)
		fprintf(stderr, "%lld G possible passwords (%lld)\n", nbparts[0] / 1000000000, nbparts[0]);
	else if(nbparts[0] > 10000000)
		fprintf(stderr, "%lld M possible passwords (%lld)\n", nbparts[0] / 1000000, nbparts[0]);
	else if(nbparts[0] > 10000)
		fprintf(stderr, "%lld K possible passwords (%lld)\n", nbparts[0] / 1000, nbparts[0]);
	else 
		fprintf(stderr, "%lld possible passwords\n", nbparts[0] );

	if(end==0)
		end = nbparts[0];

	pwd.level = 0;
	pwd.len = 0;
	pwd.index = 0;
	memset(pwd.password, 0, max_len+1);

	print_pwd(start, &pwd, max_lvl, max_len);
	print_pwd(start, &pwd2, max_lvl, max_len);

	fprintf(stderr, "starting with %s (%lld to %lld, %f%% of the scope)\n", pwd.password, start, end, 100*((float) end-start)/((float) nbparts[0]) );

	show_pwd(start, end, max_lvl, max_len);

	free(nbparts);
fin:
	free(proba1);
	free(proba2);
	free(first);
	return 0;
}