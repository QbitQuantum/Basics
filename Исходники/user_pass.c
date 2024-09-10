int sdddd(void){

    FILE *fp;
    char *tmp, *tmp2, *user, *pass, *line;

    printf("Inserire utente: ");
    if(scanf("%ms", &user) == EOF){
        perror("scanf");
        return EXIT_FAILURE;
    }

    printf("Inserire password: "******"%ms", &pass) == EOF){
        perror("scanf");
        onexit(user, NULL, NULL, NULL, 1);
        return EXIT_FAILURE;
    }

    size_t max_length = 250;
    line = malloc(max_length);
    if(line == NULL){
        perror("malloc");
        onexit(user, pass, NULL, NULL, 2);
        return EXIT_FAILURE;
    }

    fp = fopen("name_pass.txt", "r");
    if(fp == NULL){
        printf("Errore apertura file\n");
        onexit(user, pass, line, NULL, 3);
        return EXIT_FAILURE;
    }

    while(!feof(fp)){
        if(fgets(line, max_length , fp) == NULL){
            continue;
        }
        tmp = strtok(line, " ");
        if(tmp == NULL){
            perror("strtok");
            onexit(user, pass, line, fp, 4);
            return EXIT_FAILURE;
        }

        tmp2 = strtok(NULL, "\n");
        if(tmp2 == NULL){
            perror("strtok");
            onexit(user, pass, line, fp, 4);
            return EXIT_FAILURE;
        }
        if((strcmp(tmp,user) == 0) && (strcmp(tmp2,pass) == 0)){
            printf("USER: %s - PASS: %s\n", tmp, tmp2);
            onexit(user, pass, line, fp, 4);
            return EXIT_SUCCESS;
        }
        else{
                 continue;
        }
    }
    printf("no such user or pwd into DB\n");
    onexit(user, pass, line, fp, 4);
    return EXIT_FAILURE;
}