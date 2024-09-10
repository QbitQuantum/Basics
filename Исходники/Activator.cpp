bool
operator()(const wstring& lhs, const wstring& rhs) const
{
    int r = CompareStringW(LOCALE_INVARIANT, NORM_IGNORECASE, lhs.c_str(), -1, rhs.c_str(), -1);
    assert(r > 0);
    return r == CSTR_LESS_THAN;
}