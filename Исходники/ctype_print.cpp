bool PhpFunction::ctype_print(char text)
{
    PhpFunction::reset_function_execute_status("ctype/ctype_print: char");

    return (isprint(text) ? TRUE : FALSE);
}