void* getuser32function (const char* functionname)
{
    hmodule module = getmodulehandlea ("user32.dll");
    bassert (module != 0);
    return (void*) getprocaddress (module, functionname);
}