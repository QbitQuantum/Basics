static uint32_t swap32(uint32_t n)
{
    #ifdef __GNUC__
        return __builtin_bswap32(n);
    #elif defined _MSC_VER >= 1300
        return _byteswap_ulong(n);
    #else
        return ((n<<24)|((n<<8)&0x00FF0000)|((n>>8)&0x0000FF00)|(n>>24));
    #endif // __GNUC__
}