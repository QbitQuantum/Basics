ERL_NIF_TERM date_clear(ErlNifEnv* env, int argc, 
    const ERL_NIF_TERM argv[])
{
    UErrorCode status = U_ZERO_ERROR;
    UCalendar* cal;
    cloner* ptr;
    double date;

    UCalendarDateFields field;
    ERL_NIF_TERM head, tail;
    unsigned int count, i = 0;

    char    value[ATOM_LEN];
    int     parsed_value;

    if(!((argc == 3)
      && enif_get_resource(env, argv[0], calendar_type, (void**) &ptr)  
      && enif_get_double(env, argv[1], &date)
      && enif_get_list_length(env, argv[2], &count))) {
        return enif_make_badarg(env);
    }

    cal = (UCalendar*) cloner_get(ptr);
    CHECK_RES(env, cal);

    ucal_setMillis(cal, (UDate) date, &status);
    CHECK(env, status);

    tail = argv[2];
    while (enif_get_list_cell(env, tail, &head, &tail)) {

            /* Set an attribute start */

            if (!enif_get_atom(env, head, (char*) value, 
                    ATOM_LEN, ERL_NIF_LATIN1)) 
                goto bad_elem;
                
            parsed_value = parseCalendarDateField(value);
            if ((parsed_value == -1)) 
                goto bad_elem;

            field = (UCalendarDateFields) parsed_value;
 
            ucal_clearField(cal, field);

            if (U_FAILURE(status))
                goto bad_elem;
            
            /* Set an attribute end */

    }

    return calendar_to_double(env, (const UCalendar*) cal);

    bad_elem:
        return list_element_error(env, argv[2], i);
}