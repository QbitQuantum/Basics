int _ReadElem(FILE *fp, int position, int parent, OS_XML *_lxml)
{
    int c;
    unsigned int count = 0;
    unsigned int _currentlycont = 0;
    short int location = -1;

    char prevv = 0;
    char elem[XML_MAXSIZE +1];
    char cont[XML_MAXSIZE +1];
    char closedelem[XML_MAXSIZE +1];



    memset(elem,'\0',XML_MAXSIZE +1);
    memset(cont,'\0',XML_MAXSIZE +1);
    memset(closedelem,'\0',XML_MAXSIZE +1);

    while((c=FGETC(fp)) != EOF)
    {
        if(c == '\\')
            prevv = c;
        else if(prevv == '\\')
        {
            if(c != _R_CONFS)
                prevv = 0;
        }


        /* Max size */
        if(count >= XML_MAXSIZE)
        {
            xml_error(_lxml,"XML ERR: String overflow. Exiting.");
            return(-1);
        }


        /* Checking for comments */
        if(c == _R_CONFS)
        {
            int r = 0;
            if((r = _oscomment(fp)) < 0)
            {
                xml_error(_lxml,"XML ERR: Comment not closed. Bad XML.");
                return(-1);
            }
            else if(r == 1)
                continue;
        }

        /* real checking */
        if((location == -1) && (prevv == 0))
        {
            if(c == _R_CONFS)
            {
                if((c=fgetc(fp)) == '/')
                {
                    xml_error(_lxml,"XML ERR: Bad formed XML. Element "
                                    "not opened");
                    return(-1);
                }
                else
                    ungetc(c,fp);
                location = 0;
            }
            else
                continue;
        }

        else if((location == 0) && ((c == _R_CONFE) || (c == ' ')))
        {
            int _ge = 0;
            int _ga = 0;
            elem[count]='\0';

            /* Removing the / at the end of the element name */
            if(elem[count -1] == '/')
            {
                _ge = '/';
                elem[count -1] = '\0';
            }

            _writememory(elem, XML_ELEM, count+1, parent, _lxml);
            _currentlycont=_lxml->cur-1;
            if(c == ' ')
            {
                if((_ga = _getattributes(fp,parent,_lxml)) < 0)
                    return(-1);
            }

            /* If the element is closed already (finished in />) */
            if((_ge == '/') || (_ga == '/'))
            {
                _writecontent("\0", 2, _currentlycont,_lxml);
                _lxml->ck[_currentlycont] = 1;
                _currentlycont = 0;
                count = 0;
                location = -1;

                memset(elem,'\0',XML_MAXSIZE);
                memset(closedelem,'\0',XML_MAXSIZE);
                memset(cont,'\0',XML_MAXSIZE);

                if(parent > 0)
                    return(0);
            }
            else
            {
                count = 0;
                location = 1;
            }
        }

        else if((location == 2) &&(c == _R_CONFE))
        {
            closedelem[count]='\0';
            if(strcmp(closedelem,elem) != 0)
            {
                xml_error(_lxml,"XML ERR: Element not closed: %s",elem);
                return(-1);
            }
            _writecontent(cont,strlen(cont)+1,_currentlycont,_lxml);
            _lxml->ck[_currentlycont]=1;	
            memset(elem,'\0',XML_MAXSIZE);
            memset(closedelem,'\0',XML_MAXSIZE);
            memset(cont,'\0',XML_MAXSIZE);
            _currentlycont = 0;
            count = 0;	
            location = -1;
            if(parent > 0)
                return(0);
        }
        else if((location == 1) && (c == _R_CONFS) && (prevv == 0))
        {
            if((c=fgetc(fp)) == '/')
            {
                cont[count] = '\0';
                count = 0;
                location = 2;
            }	
            else
            {
                ungetc(c,fp);
                ungetc(_R_CONFS,fp);

                if(_ReadElem(fp,position+1,parent+1,_lxml)< 0)
                {
                    return(-1);
                }
                count=0;
            }
        }
        else
        {
            if(location == 0)
                elem[count++] = c;
            else if(location == 1)
                cont[count++] = c;
            else if(location == 2)
                closedelem[count++] = c;

            if((_R_CONFS == c) && (prevv != 0))
            {
                prevv = 0;
            }
        }
    }
    if(location == -1)
        return(LEOF);

    xml_error(_lxml,"XML ERR: End of file and some elements were not closed");
    return(-1);
}				