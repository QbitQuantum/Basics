char* _ngx_process_memguard_trim_ws(char *line)
{
    return line + strspn(line, " \t");
}