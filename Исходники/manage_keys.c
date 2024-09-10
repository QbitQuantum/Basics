/* extract base64 for a specific agent */
int k_extract(char *cmdextract)
{
    FILE *fp;
    char *user_input;
    char *b64_enc;
    char line_read[FILE_SIZE +1];
    char n_id[USER_SIZE +1];


    if(cmdextract)
    {
        user_input = cmdextract;

        if(!IDExist(user_input))
        {
            printf(NO_ID, user_input);
            exit(1);
        }
    }

    else
    {
        if(!print_agents(0, 0, 0))
        {
            printf(NO_AGENT);
            printf(PRESS_ENTER);
            read_from_user();
            return(0);
        }

        do
        {
            printf(EXTRACT_KEY);
            fflush(stdout);
            user_input = read_from_user();

            /* quit */
            if(strcmp(user_input, QUIT) == 0)
                return(0);

            if(!IDExist(user_input))
                printf(NO_ID, user_input);

        } while(!IDExist(user_input));
    }


    /* Trying to open the auth file */
    fp = fopen(AUTH_FILE, "r");
    if(!fp)
    {
        ErrorExit(FOPEN_ERROR, ARGV0, AUTH_FILE);
    }

    fsetpos(fp, &fp_pos);

    memset(n_id, '\0', USER_SIZE +1);
    strncpy(n_id, user_input, USER_SIZE -1);


    if(fgets(line_read, FILE_SIZE, fp) == NULL)
    {
        printf(ERROR_KEYS);
        fclose(fp);
        exit(1);
    }
    chomp(line_read);


    b64_enc = encode_base64(strlen(line_read),line_read);
    if(b64_enc == NULL)
    {
        printf(EXTRACT_ERROR);
        fclose(fp);
        exit(1);
    }

    printf(EXTRACT_MSG, n_id, b64_enc);
    if(!cmdextract)
    {
        printf("\n" PRESS_ENTER);
        read_from_user();
    }

    free(b64_enc);
    fclose(fp);

    return(0);
}