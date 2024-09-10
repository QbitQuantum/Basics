int 
main(int argc, char **argv)
{

	if (argc < 2) {
		printf("usage: ./multisort inputfile > outfile \n");
		exit(1);
	}

	char **words = (char **)malloc(sizeof(char *)*MAXLINE);
	int n_words = readwords(words, argv[1]);

	int len = n_words;
    
    // parent should wait for child to exit

    pid_t pid;
    if ((pid = fork() == 0))
    {
        // split input file into two halves
        int halflen = len / 2;
        FILE *firsthalf = fopen("first-half-exec.txt", "w");
        FILE *secondhalf = fopen("second-half-exec.txt", "w");
        for (int i = 0; i < halflen; i++)
        {
            fprintf(firsthalf, "%s", words[i]);
        }
        for (int i = halflen; i < len; i++)
        {
            fprintf(secondhalf, "%s", words[i]);
        }
        //fclose(firsthalf);
        //fclose(secondhalf);

        // clean up memory
        for (int i = 0; i < len; i++)
        {
            free(words[i]);
        }
        free(words);

        // the program "sort" outputs to standard output
        // we should change our programs to redirect standard output to the two files
        fclose(firsthalf);
        fclose(secondhalf);

	    pid_t cpid;
	    if ((cpid = fork()) != 0) {
            FILE *sortedfirsthalf = fopen("first-half-exec-sorted.txt", "w");
            dup2(fileno(sortedfirsthalf), STDOUT_FILENO);
            fclose(sortedfirsthalf);            
            char *sortargs[] = { "sort", "-n", "first-half-exec.txt", NULL };
            execvp("sort", sortargs);
		    //parent sort the first half of the [start, start + len] section of words
	    	//len = len/2;
		    //qsort(words + start, len, sizeof(char *), qsort_cmp);
	    	//fprintf(stderr, "pid-%d has sorted [%d, %d)\n", getpid(), start, start + len);
            // write out first half of array to disk
	    } else {
            FILE *sortedsecondhalf = fopen("second-half-exec-sorted.txt", "w");
            dup2(fileno(sortedsecondhalf), STDOUT_FILENO);
            fclose(sortedsecondhalf);            
            char *sortargs[] = { "sort" , "-n", "second-half-exec.txt", NULL };
            execvp("sort", sortargs);
	    	//start = start + len/2;
	    	//len = len - len/2;
	    	//qsort(words + start, len, sizeof(char *), qsort_cmp);
	    	//fprintf(stderr, "pid-%d has sorted [%d, %d)\n", getpid(), start, start + len);
            // write out second half of array to disk
	    	exit(0);
	    }
        // wait for child's child to exit
        int status;
        waitpid(cpid, &status, 0);
        exit(0);
    }
    else
    {
    }

    
    // wait for all child processes
    wait(NULL);

	fprintf(stderr, "both sorting has finished\n");
	fprintf(stderr, "merging both lists\n\n\n");

    for (int i = 0; i < len; i++)
    {
        free(words[i]);
    }

    int halflen = len / 2;
    FILE *firsthalf = fopen("first-half-exec-sorted.txt", "r");
    FILE *secondhalf = fopen("second-half-exec-sorted.txt", "r");
    for (int i = 0; i < halflen; i++)
    {
        char *word = (char *)malloc(MAXWORDSZ);
        fgets(word, MAXWORDSZ, firsthalf);
        words[i] = word; 
    }
    for (int i = halflen; i < len; i++)
    {
        char *word = (char *)malloc(MAXWORDSZ);
        fgets(word, MAXWORDSZ, secondhalf);
        words[i] = word;
    }
    fclose(firsthalf);
    fclose(secondhalf);

    //merge the two sorted list into one
	mergewords(words, n_words/2, words+(n_words/2), n_words-(n_words/2), argv[1]);

    for (int i = 0; i < len; i++)
    {
        free(words[i]);
    }
    free(words);
    return 0;
}