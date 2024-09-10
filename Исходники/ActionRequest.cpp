void CActionRequest::SetQualifiedName(const CSmallString& name)
{
    // string is empty
    if( name == NULL ) {
        INVALID_ARGUMENT("qualified name is NULL");
    }

    int len = name.GetLength();

    // find first :
    int first = name.IndexOf(':');
    if( (first == -1) ||
            (first + 2 >= len) ||
            (name[first+1] != '/') ||
            (name[first+2] != '/') ) {
        CSmallString error;
        error << Protocol << ":// protocol is not specified";
        LOGIC_ERROR(error);
    }

    if( Protocol != name.GetSubStringFromTo(0,first-1) ) {
        CSmallString error;
        error << "protocol mismatch, required: '" << Protocol << "' specified: '" << name.GetSubStringFromTo(0,first-1) << "'";
        LOGIC_ERROR(error);
    }

    if( first + 3 >= len ) {
        LOGIC_ERROR("server name is missing");
    }

    // now extract server name ---------------------
    int lname_beg = first+3;
    int lname_end = name.Scan(":/",lname_beg);
    lname_end--;   // remove : or /
    if( lname_end < 0 ) {
        lname_end = len - 1;
    }

    if( lname_end < lname_beg ) {
        LOGIC_ERROR("server name is empty");
    }

    // resolve name and IP --------------------------------------------------------

    CSmallString addr = name.GetSubStringFromTo(lname_beg,lname_end);

    if( addr != "serverkey" ) {
        GetServerNameAndIP(addr);
    }

    if( lname_end + 1 >= len ) return; // nothing more to encode

    // is there a port specified? ------------------
    int lport_beg = name.Scan(":/",lname_end+1);
    int lport_end = lport_beg - 1;
    if( (lport_beg >= 0) && (name[lport_beg] == ':') ) {
        lport_beg++;
        if( lport_beg >= len ) {
            LOGIC_ERROR("delimiter : was specified but port number is missing");
        }
        // extract protocol
        lport_end = name.Scan("/",lport_beg);
        lport_end--;
        if( lport_end < 0 ) {
            lport_end = name.GetLength() - 1;
        }

        if( lport_end < lport_beg ) {
            LOGIC_ERROR("delimiter : was specified but port number is missing");
        }

        CSmallString sport;
        sport = name.GetSubStringFromTo(lport_beg,lport_end);
        if( sport.ToInt(Port) == false) {
            LOGIC_ERROR("specified port '" + sport + "' is not a number");
        }
    }

    if( lport_end + 2 >= len ) return; // nothing more to encode

    CSmallString tmp_string;

    tmp_string = name.GetSubStringFromTo(lport_end + 2,name.GetLength()-1);

    // decode action
    int lparam_beg;

    lparam_beg = tmp_string.Scan("?");

    if( lparam_beg < 0 ) {
        Action = tmp_string;    // only action
        return;
    }

    if( lparam_beg == 0 ) {
        LOGIC_ERROR("action is not specified");
    }

    Action = tmp_string.GetSubStringFromTo(0,lparam_beg-1);

    do {
        len = tmp_string.GetLength();
        if( lparam_beg+1 > len-1) {
            LOGIC_ERROR("delimiter ? or , was specified but key and value are missing");
        }
        tmp_string = tmp_string.GetSubStringFromTo(lparam_beg+1,tmp_string.GetLength()-1);

        CSmallString key,value;

        int key_end;
        int value_end;

        key_end = tmp_string.Scan("=");

        if( key_end < 0 ) {
            LOGIC_ERROR("key is not provided (delimiter = is missing)");
        }

        value_end = tmp_string.Scan(",");

        if( value_end < 0 ) {
            value_end = tmp_string.GetLength();
        }

        if( key_end == 0 ) {
            LOGIC_ERROR("key is not specified");
        }

        key = tmp_string.GetSubStringFromTo(0,key_end-1);
        if( value_end-1 >= key_end+1 ) {
            value = tmp_string.GetSubStringFromTo(key_end+1,value_end-1);
        }

        CActionParameter param;

        param.Key = key;
        param.Value = value;
        Parameters.push_back(param);

        lparam_beg = tmp_string.Scan(",");

    } while(lparam_beg >= 0);

}