BOOL WINAPI DllMain(
    HINSTANCE,  //hDllInst
    DWORD fdwReason,
    LPVOID  // lpvReserved
)
{
# ifdef BOOST_MSVC
    _set_se_translator(structured_exception_translator);
# endif
    (void)fdwReason; // warning suppression.

    return 1;
}