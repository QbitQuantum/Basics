string Lex_Result::ToString() {
    char tmp[256];
    string res;
    res.append(" res_type ")
        .append(max<double>(13 - strlen(type_names[res_type]), 0), ' ')
        .append(type_names[res_type]);
    res.append(" res_int ").append(Itoa(res_int, tmp, 10));
    res.append(" res_val ").append(Gcvt(res_val, 12, tmp));
    res.append(" res_str ").append(res_str).append("\n");
    return res;
}