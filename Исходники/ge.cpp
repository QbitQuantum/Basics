void Ge::activate_export_gejava_as()
{
    char name[80];
    char default_name[80];

    if ( !graph->get_java_name( name)) {
        graph->get_name( name);
        if ( strcmp( name, "") != 0) {
            if ( strncmp( name, "pwr_c_", 6) == 0) {
                strcpy( default_name, "Jopc");
                strcat( default_name, &name[6]);
                default_name[4] = _toupper( default_name[4]);
            }
            else if ( strncmp( name, "pwr_", 4) == 0) {
                strcpy( default_name, "Jop");
                strcat( default_name, &name[4]);
                default_name[3] = _toupper( default_name[3]);
            }
            else {
                strcpy( default_name, name);
                default_name[0] = _toupper( default_name[0]);
            }
        }
        else
            strcpy( default_name, "");
    }
    else
        strcpy( default_name, name);
    open_input_dialog( "Java name", "Export GeJava",
                       default_name, Ge::export_gejava);
}