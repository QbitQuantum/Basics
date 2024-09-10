extern "C" int __cdecl _ismbcalpha(unsigned int const c)
{
    return _ismbcalpha_l(c, nullptr);
}