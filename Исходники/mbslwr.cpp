errno_t (__cdecl _mbslwr_s)(
        unsigned char *string,
        size_t sizeInBytes
        )
{
    return _mbslwr_s_l(string, sizeInBytes, nullptr);
}