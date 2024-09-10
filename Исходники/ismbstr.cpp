extern "C" int __cdecl _ismbstrail(
    unsigned char const* const string,
    unsigned char const* const current
    )
{
    return _ismbstrail_l(string, current, nullptr);
}