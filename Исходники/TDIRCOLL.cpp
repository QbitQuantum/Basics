Boolean isDir( const char *str )
{
    Boolean result;
    finddata ff;
    intptr_t fh = findfirst( str, &ff );
    result = Boolean( fh != -1 &&
                    (ff.attrib & FA_DIREC) != 0 );
    findclose(fh);
    return result;
}