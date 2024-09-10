void    o_default_frame( FILE * f, lay_att curr, def_frame * tm )
{

    switch( tm->type ) {
    case   none:
        fprintf_s( f, "        %s = none\n", att_names[curr] );
        break;
    case   rule_frame:
        fprintf_s( f, "        %s = rule\n", att_names[curr] );
        break;
    case   box_frame:
        fprintf_s( f, "        %s = box\n", att_names[curr] );
        break;
    case   char_frame:
        fprintf_s( f, "        %s = '%s'\n", att_names[curr], tm->string );
        break;
    default:
        fprintf_s( f, "        %s = ???\n", att_names[curr] );
        break;
    }
    return;
}