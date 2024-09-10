//-----------------------------------------------
// Cut module name to 11 sym
//-----------------------------------------------
static void flat_module_name_make( char* tgt, const char* name )
{
    char *p = strrchr(name,'/');
    strncpy(tgt, (p) ? p+1 : name, 12);
    tgt[11] = 0;
}