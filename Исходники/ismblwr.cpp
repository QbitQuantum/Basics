extern "C" int __cdecl _ismbclower(unsigned int const c)
{
    return _ismbclower_l(c, nullptr);
}