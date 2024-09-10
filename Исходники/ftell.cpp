static Integer __cdecl common_ftell(__crt_stdio_stream const stream) throw()
{
    _VALIDATE_RETURN(stream.valid(), EINVAL, -1);

    Integer return_value = 0;

    _lock_file(stream.public_stream());
    __try
    {
        return_value = common_ftell_nolock<Integer>(stream);
    }
    __finally
    {
        _unlock_file(stream.public_stream());
    }

    return return_value;
}