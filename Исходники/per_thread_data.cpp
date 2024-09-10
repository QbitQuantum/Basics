extern "C" uintptr_t __cdecl __threadhandle()
{
    return reinterpret_cast<uintptr_t>(GetCurrentThread());
}