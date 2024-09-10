bool Fits2D::readStringKeyword(string keyword, string &value){

    char *ptr = NULL;

    int status = 0;

    fitsfile *fptr;

    const char * filename;

    char v[40];

    filename = mFitsPath.c_str();


    if(fits_open_file(&fptr, filename, READONLY, &status)){

        printerror(status);
        return false;

    }

    char * key = new char[keyword.length()+1];
    strcpy(key,keyword.c_str());

    if(fits_read_key(fptr, TSTRING, key, v, NULL, &status)){


        printerror(status);
        delete key;
        return false;

    }

    value = string(v);

    delete key;

    if(fits_close_file(fptr, &status)){

        printerror(status);
        return false;

    }

    return true;
}