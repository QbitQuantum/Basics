//parse the first line into the array
//and store url method version into the header
int parse_resquest(char* buff,http_header* pheader)
{
    int i,j;
    i = j = 0;

    //read the method into the array
    while(!ISspace(buff[i]) &&  i<(sizeof(pheader->method) -1) )
    {
        pheader->method[j] = buff[i];
        i++,j++;
    }
    pheader->method[i] = '\0';

    //if the method not the "GET",return the unimplemented
    if( strcmp(pheader->method,"GET") != 0)
    {
        // debug_info
        printf("this method unimplemented !");
        //unimplemented method
        //unimplemented(cli_fd);
        //return -1 (method is unimplemented)
        return -1;
    }

    //skip all the space
    while(ISspace(buff[j]) && j<sizeof(buff))
        j++;

    //read the url into the array
    i = 0 ;
    while(!ISspace(buff[j]) && i<sizeof(pheader->url))
    {
        pheader->url[i] = buff[j];
        i++,j++;
    }
    pheader->url[i] = '\0';

    //read the version into the array
    while(ISspace(buff[j]) && j<sizeof(buff))
        j++;
    i = 0;
    while(!ISspace(buff[j]) && i<sizeof(pheader->version) )
    {
        pheader->version[i] = buff[j];
        i++,j++;
    }
    pheader->version[j] = '\0';

    return 0;
}