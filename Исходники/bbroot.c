ST int next_token(struct rootinfo *r)
{
    int s = E_eos;
    _strlwr(NextToken(r->token, &r->cptr, " "));
    r->flag = 1;
    if (r->token[0]) {
        const char * p = r->token;
        if (0 == strncmp(p, "-no", 3))
            r->flag = 0, p+= 3;
        s = get_string_index(p, switches) + E_other + 1;
    }
    //dbg_printf("token %d: %s", s, r->token);
    return s;
}