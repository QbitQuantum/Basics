/**
 * Return the real in a formatted string with an optional currency
 * symbol, according to the given locale regarding decimal separator,
 * thousands separator and positive or negative sign.
 * 
 * \param number		    Number to format.
 * \param locale      		the locale obtained with localeconv(), or built manually
 * \param currency_symbol 	the currency symbol
 *
 * \return		A newly allocated string of the number (this
 *			function will never return NULL) 
 */
gchar *gsb_real_raw_format_string (gsb_real number,
                        struct lconv *locale,
                        const gchar *currency_symbol )
{
    gchar buffer[G_ASCII_DTOSTR_BUF_SIZE];
    gchar format[40];
    gchar *result = NULL, *temp = NULL;
	const gchar *cs_start;
    const gchar *cs_start_space;
    const gchar *sign;
    const gchar *mon_decimal_point;
    const gchar *cs_end_space;
    const gchar *cs_end;
    gint nbre_char;
	lldiv_t units;
/*printf ("currency_symbol = %s\n", currency_symbol);*/
    cs_start = (currency_symbol && locale->p_cs_precedes) ? currency_symbol : "";
    cs_start_space = (currency_symbol && locale->p_cs_precedes && locale->p_sep_by_space) ? " " : "";
    sign = (number.mantissa < 0) ? locale->negative_sign : locale->positive_sign;
    mon_decimal_point = locale->mon_decimal_point && *locale->mon_decimal_point ? locale->mon_decimal_point : "";
    cs_end_space = (currency_symbol && !locale->p_cs_precedes && locale->p_sep_by_space) ? " " : "";
    cs_end = (currency_symbol && !locale->p_cs_precedes) ? currency_symbol : "";
    
    units = lldiv ( llabs (number.mantissa), gsb_real_power_10[number.exponent] );

    nbre_char = g_sprintf ( buffer, "%.0f", (gdouble) units.quot );

    temp = g_strndup ( buffer, nbre_char );

    if ( units.quot >= 1000 )
    {
        temp = gsb_real_add_thousands_sep ( temp, locale->mon_thousands_sep );
    }

    g_snprintf ( format, sizeof ( format ), "%s%d%s",
                                            "%s%s%s%s%s%0",
                                            number.exponent,
                                            "lld%s%s" );

    result = g_strdup_printf ( format, 
                            cs_start,
                            cs_start_space,
                            sign,
                            temp,
                            mon_decimal_point,
                            units.rem,
                            cs_end_space,
                            cs_end );

    g_free ( temp );

    return result;
}