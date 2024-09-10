bool
named_pipe_t::create()
{
    // FIXME i#1703: NYI
    // We should document the 256 char limit on path name.
    HANDLE pipe = CreateNamedPipeA(named_pipe.c_str(),
                                   PIPE_ACCESS...);
}