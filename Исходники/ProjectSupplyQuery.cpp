void ProjectSupplyQuery::ExtractKeywordsFromKeywordString(char *keyword_string,vector<char *> &keywords)
{
    UINT i;

    // Make the string lowercase (although it already should be)
    char *lbuf=new char[strlen(keyword_string)+1];
    strcpy(lbuf,keyword_string);
    strlwr(lbuf);

    // Trim leading and trailing whitespace
    CString cstring=lbuf;
    cstring.TrimLeft();
    cstring.TrimRight();
    string cstring_string=cstring;
    strcpy(lbuf,cstring_string.c_str());

    // Extract the keywords
    char *ptr=lbuf;
    while(strlen(ptr)>0)
    {
        // Skip past any intermediate spaces in between keywords
        while((*ptr==' '))
        {
            ptr++;
        }

        bool done=true;
        if(strchr(ptr,' ')!=NULL)	// see if there are more keywords after this keyword
        {
            done=false;
            *strchr(ptr,' ')='\0';
        }

        // Check to see if this keyword is already in there
        bool found=false;
        for(i=0; i<keywords.size(); i++)
        {
            if(strcmp(keywords[i],ptr)==0)
            {
                found=true;
                break;
            }
        }
        if(!found)	// if not, then add it
        {
            char *tmp_ptr=new char[strlen(ptr)+1];
            strcpy(tmp_ptr,ptr);
            keywords.push_back(tmp_ptr);
        }

        if(done)
        {
            break;
        }
        else
        {
            ptr+=strlen(ptr)+1;
        }
    }

    delete [] lbuf;
}