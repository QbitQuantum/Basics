int parseline( char* c1, char* c2, char* def)
{

    size_t i = 1000;
    int j, k, l, m;
    int end = 0;
    char c;
    j = k = l = m = 0;

    if(j = fscanf(stdin, " %s", c1))
    {
        while(isspace(c = getchar()))
        {
            if(c == '\n')
            {
                end = 1;
                break;
            }
        }
        m = ungetc(c, stdin);
        if(!end && (k = fscanf(stdin, " %s", c2)))
        {
            while(isspace(c = getchar()))
            {
                if(c == '\n')
                {
                    end = 1;
                    break;
                }
            }
            if(!end)
            {
                m = ungetc(c, stdin);
                l = getline(&def, &i, stdin);
                def[l-1] = '\0';
            }
        }
    }


    if(!strcmp(c1, "add"))
    {
        if(k&&l)
        {
            return 1;
        }
        else return -1;
    }

    else if(!strcmp(c1, "find"))
    {
        if(k)
        {
            if(l)
                return 7;
            else
                return 3;
        }
        else return -3;
    }


    else if(!strcmp(c1, "delete"))
    {
        if(k)
        {
            return 2;
        }
        else return -2;
    }


    else if(!strcmp(c1, "print"))
    {
        return 4;
    }


    else if(!strcmp(c1, "read"))
    {
        if(k)
        {
            return 6;
        }
        else return -5;
    }

    else if(!strcmp(c1, "exit"))
    {
        return 5;
    }
    else if(!strcmp(c1, "test"))
    {
        if(k)
            return 8;
    }

    return -4;

}