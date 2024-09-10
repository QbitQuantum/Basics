int main(int argc,char **argv) {
	list_t list;
	int index;
	char *arg;
	int elements;
	/* Initialize our list. */
	listInitialize(&list);
	/* Fill our list with all command line arguments given, but skip the
	 * first argument since that's our needle (see below -> listSearch()). */
	for(index=2;index<argc;index++) {
		/* Append the argument to our list. */
		if(listAppend(&list,(void *)argv[index])!=listRtrnOk) {
			fprintf(stderr,"Can't create item!\n");
			break;
		}
		/* Advance to this next position. By default listAppend() does not
		 * advance our current pointer to the appended element. */
		listNext(&list);
	}
	/* Print all our arguments from the first to the last. */
	printf("First to last:\n");
	/* Does any argument exist? */
	if((arg=(char *)listFirst(&list))!=NULL) {
		/* Yes, we print it and... */
		do {
			printf("[%s]\n",arg);
			/* ...advance to the next argument, untill none left. */
		} while((arg=(char *)listNext(&list))!=NULL);
	} else {
		printf("empty list\n");
	}
	/* Print all our arguments from the last to the first. */
	printf("Last to first:\n");
	/* Does any argument exist? */
	if((arg=(char *)listLast(&list))!=NULL) {
		/* Yes, we print it and... */
		do {
			printf("[%s]\n",arg);
			/* ...advance to the next argument, untill none left. */
		} while((arg=(char *)listPrevious(&list))!=NULL);
	} else {
		printf("empty list\n");
	}
	/* If there do exist enough arguments... */
	if(argc>=2) {
		/* ...search for the first one given... */
		arg=listSearch(&list,cmpr,(void *)argv[1]);
		/* ...and tell if it's found. */
		printf("searching for [%s]... %sfound\n",argv[1],arg!=NULL?"":"not ");
	}
	/* Randomly remove half of the arguments. */
	srandom(getpid());
	for(elements=listElements(&list)/2;elements>0;elements--) {
		int element=(random()%(argc-2))+2;
		arg=listSearch(&list,cmpr,(void *)argv[element]);
		printf("Removing [%s]... ",argv[element]);
		if(arg!=NULL) {
			listRemove(&list,NULL);
			printf("ok\n");
		} else {
			printf("not in the list!\n");
		}
	}
	/* Print all our arguments from the first to the last. */
	printf("First to last:\n");
	/* Does any argument exist? */
	if((arg=(char *)listFirst(&list))!=NULL) {
		/* Yes, we print it and... */
		do {
			printf("[%s]\n",arg);
			/* ...advance to the next argument, untill none left. */
		} while((arg=(char *)listNext(&list))!=NULL);
	} else {
		printf("empty list\n");
	}
	/* Print all our arguments from the last to the first. */
	printf("Last to first:\n");
	/* Does any argument exist? */
	if((arg=(char *)listLast(&list))!=NULL) {
		/* Yes, we print it and... */
		do {
			printf("[%s]\n",arg);
			/* ...advance to the next argument, untill none left. */
		} while((arg=(char *)listPrevious(&list))!=NULL);
	} else {
		printf("empty list\n");
	}

	/* Destroy the list and all its elements. */
	listDestroy(&list,garbageCollect);
	return(0);
}