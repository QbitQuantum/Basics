void lxs_sappend_vformat(lua_State* const L,
                         lxs_string* const s,
                         const char* fmt,
                         va_list args)
{
    lxs_assert(L, L);
    lxs_assert(L, s);
    lxs_assert(L, fmt);
    lxs_assert(L, args);

    int len = _vscprintf(fmt, args);
    if (len < 0)
        lxs_error(L, "invalid format string and/or format arguments");
    else if (len == 0)
        return;

    lxs_sensure_space(L, s, static_cast<size_t>(len));

    vsprintf_s(&s->data[s->len], lxs_sfree(s) + 1, fmt, args);
    s->len += len;

    lxs_sterminate(s);
}