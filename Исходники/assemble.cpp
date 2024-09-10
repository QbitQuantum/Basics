symbol* assembler::identify(string s, symbol& ans)
{
    ans.name = s;
    ans.value = 0;
    char c = s[0];
    if (s == end_of_line)
        ans.kind = the_end;
    else if (c == '\"')
        ans.kind = a_string;
    else if (c == ',')
        ans.kind = a_comma;
    else if (c == ':')
        ans.kind = a_colon;
    else if (c == '=')
        ans.kind = an_equals_sign;
    else if (c == '+')
        ans.kind = a_plus_sign;
    else if (c == '-')
        ans.kind = a_minus_sign;
    else if (c == '[')
        ans.kind = an_open_bracket;
    else if (c == ']')
        ans.kind = a_close_bracket;
    else if (c == '.')
    {
        c = s[1];
        if (c >= '0' && c <= '9')
        {
            s = s.substr(1);
            ans.name = s;
            int last = s.length() - 1;
            if (last > 0 && (s[last] == 'H' || s[last] == 'L'))
                s = s.substr(0, last);
            union
            {
                float fv;
                int iv;
            } converter;
            converter.fv = strtof(s.c_str(), NULL);
            ans.value = converter.iv;
            ans.kind = a_float;
        }
        else
            ans.kind = a_command;
    }
    else if (c == '\'')
    {
        int len = s.length();
        ans.value = 0;
        for (int i = 1; i < len; i += 1)
        {
            char c = s[i];
            if (c == '\\')
            {
                i += 1;
                c = backstroke_char(s[i]);
            }
            ans.value = ans.value * 256 + c;
        }
        ans.kind = a_number;
    }
    else if (c >= '0' && c <= '9')
    {
        int last = s.length() - 1;
        if (last > 0 && (s[last] == 'H' || s[last] == 'L'))
            s = s.substr(0, last);
        bool ok = string_to_int(s, ans.value);
        if (ok)
            ans.kind = a_number;
        else
            ans.kind = a_bad_number;
    }
    else if (c == '#')
    {
        s = s.substr(1);
        symbol* e = symtab.find(s);
        if (pass == 2 && e->kind == a_name)
            error("There is nothing matching '%s' in the symbol table\n", s.c_str());
        ans.kind = a_number;
        ans.value = e->value;
    }
    else if (c >= 'A' && c <= 'Z' || c == '_' || c == '%' || c == '$' || c == '@')
    {
        symbol* e = symtab.find(s);
        return e;
    }
    else
        ans.kind = something_else;
    return & ans;
}