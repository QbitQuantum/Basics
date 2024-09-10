// /?/web_server.c=111&/1.html=&/2.html=&/server_options.c=&/web=&/dir.c~=&/server_options.h=&/no=
int getRenameInfo (int fd, char web_root[], char url_link[])
{
    char file_tmp[DIR_LENGTH];
    memset(file_tmp, 0, DIR_LENGTH*sizeof(char));
    char name_tmp[32];
    memset(name_tmp, 0, 32*sizeof(char));
    char path_tmp[DIR_LENGTH];
    memset(path_tmp, 0, DIR_LENGTH*sizeof(char));
    char current_path[DIR_LENGTH];
    memset(current_path, 0, DIR_LENGTH*sizeof(char));

    int i, j;
    int pos_equal = 0;
    int pos_and   = 0;

    sscanf(url_link, "%*[^.].%[^?]", current_path);
    printf("current path1 %s\n", current_path);
    char* seps = ".";
    char* token = strtok( current_path, seps );
    while( token != NULL )
    {
        strcpy(current_path,token);
        token = strtok( NULL, seps );
    }
    //	memset(current_path, 0, DIR_LENGTH*sizeof(char));

    printf("current path2 %s\n", current_path);

    char strTmp[DIR_LENGTH];
    strcpy(strTmp,url_link);
    seps = "/&";
    token = strtok( strTmp, seps );
    while( token != NULL )
    {
        /* While there are tokens in "string" */
        printf( " %s\n", token );

        /* process:get new name */
        sscanf(token, "%[^=]=%s", file_tmp, name_tmp);	//get file and new name
        if (strlen(name_tmp) != 0)
        {
            printf("file %s\nname %s  len= %d\n", file_tmp, name_tmp,strlen(name_tmp));
            sprintf(path_tmp,"%s%s/%s",web_root,current_path,file_tmp);
            printf("file %s\n", path_tmp);

            if ( reName(path_tmp,name_tmp) == 0 )
            {
                printf("reName%s to  %s\n",path_tmp,name_tmp );
            }

            memset(name_tmp, 0, 32*sizeof(char));
            memset(path_tmp, 0, DIR_LENGTH*sizeof(char));
            memset(file_tmp, 0, DIR_LENGTH*sizeof(char));
        }
        /* Get next token: */
        token = strtok( NULL, seps );
    }
    printDir(fd, web_root, current_path);
    return 0;
}