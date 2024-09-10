// returns -1 for error, 0 if not found (end of section or file)
// and 1 if found
static int prv_read_key_value(FILE * fd,
                              char ** keyP,
                              char ** valueP)
{
    char * line;
    fpos_t prevPos;
    ssize_t res;
    size_t length;
    size_t start;
    size_t middle;
    size_t end;

    *keyP = NULL;
    *valueP = NULL;

    line = NULL;
    if (fgetpos(fd, &prevPos) != 0) return -1;
    while ((res = getline(&line, &length, fd)) != -1)
    {
        length = strlen(line);

        start = 0;
        while (start < length && isspace(line[start]&0xff)) start++;
        // ignore empty and commented lines
        if (start != length
         && line[start] != ';'
         && line[start] != '#')
        {
            break;
        }

        lwm2m_free(line);
        line = NULL;
        length = 0;
        if (fgetpos(fd, &prevPos) != 0) return -1;
    }

    if (res == -1) return -1;

    // end of section
    if (line[start] == '[')
    {
        lwm2m_free(line);
        fsetpos(fd, &prevPos);
        return 0;
    }

    middle = start;
    while (middle < length && line[middle] != '=') middle++;
    // invalid lines
    if (middle == start
     || middle == length)
    {
        lwm2m_free(line);
        return -1;
    }

    end = length - 2;
    while (end > middle && isspace(line[end]&0xff)) end--;
    // invalid lines
    if (end == middle)
    {
        lwm2m_free(line);
        return -1;
    }
    end += 1;

    line[middle] = 0;
    *keyP = strdup(line + start);
    if (*keyP == NULL)
    {
        lwm2m_free(line);
        return -1;
    }

    middle +=1 ;
    while (middle < end && isspace(line[middle]&0xff)) middle++;
    line[end] = 0;
    *valueP = strdup(line + middle);
    if (*valueP == NULL)
    {
        lwm2m_free(*keyP);
        *keyP = NULL;
        lwm2m_free(line);
        return -1;
    }

    lwm2m_free(line);

    return 1;
}