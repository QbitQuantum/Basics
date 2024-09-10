/** Parse a stringified option
 * This function parse a string option and create the associated object
 * variable
 * The option must be of the form "[no[-]]foo[=bar]" where foo is the
 * option name and bar is the value of the option.
 * \param p_obj the object in which the variable must be created
 * \param psz_option the option to parse
 * \param trusted whether the option is set by a trusted input or not
 * \return nothing
 */
void var_OptionParse( vlc_object_t *p_obj, const char *psz_option,
                      bool trusted )
{
    char *psz_name, *psz_value;
    int  i_type;
    bool b_isno = false;
    vlc_value_t val;

    val.psz_string = NULL;

    /* It's too much of a hassle to remove the ':' when we parse
     * the cmd line :) */
    if( psz_option[0] == ':' )
        psz_option++;

    if( !psz_option[0] )
        return;

    psz_name = strdup( psz_option );
    if( psz_name == NULL )
        return;

    psz_value = strchr( psz_name, '=' );
    if( psz_value != NULL )
        *psz_value++ = '\0';

    i_type = config_GetType( p_obj, psz_name );
    if( !i_type && !psz_value )
    {
        /* check for "no-foo" or "nofoo" */
        if( !strncmp( psz_name, "no-", 3 ) )
        {
            memmove( psz_name, psz_name + 3, strlen(psz_name) + 1 - 3 );
        }
        else if( !strncmp( psz_name, "no", 2 ) )
        {
            memmove( psz_name, psz_name + 2, strlen(psz_name) + 1 - 2 );
        }
        else goto cleanup;           /* Option doesn't exist */

        b_isno = true;
        i_type = config_GetType( p_obj, psz_name );
    }
    if( !i_type ) goto cleanup; /* Option doesn't exist */

    if( ( i_type != VLC_VAR_BOOL ) &&
        ( !psz_value || !*psz_value ) ) goto cleanup; /* Invalid value */

    /* check if option is unsafe */
    if( !trusted && !config_IsSafe( psz_name ) )
    {
        msg_Err( p_obj, "unsafe option \"%s\" has been ignored for "
                        "security reasons", psz_name );
        free( psz_name );
        return;
    }

    /* Create the variable in the input object.
     * Children of the input object will be able to retreive this value
     * thanks to the inheritance property of the object variables. */
    var_Create( p_obj, psz_name, i_type );

    switch( i_type )
    {
    case VLC_VAR_BOOL:
        val.b_bool = !b_isno;
        break;

    case VLC_VAR_INTEGER:
        val.i_int = strtoll( psz_value, NULL, 0 );
        break;

    case VLC_VAR_FLOAT:
        val.f_float = us_atof( psz_value );
        break;

    case VLC_VAR_STRING:
        val.psz_string = psz_value;
        break;

    default:
        goto cleanup;
    }

    var_Set( p_obj, psz_name, val );

cleanup:
    free( psz_name );
}