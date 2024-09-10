/* set a new maximum for the number of simultaneously open files.
 * if return = -1 error occured
 */
int
pdc_set_maxfilehandles(pdc_core *pdc, int maxfps)
{
    const char *stemp = pdc_errprintf(pdc, "%d", maxfps);

    if (maxfps < _IOB_ENTRIES)
        pdc_error(pdc, PDC_E_IO_TOOFEW_REQFILEHDLS, stemp,
                  pdc_errprintf(pdc, "%d", _IOB_ENTRIES), 0, 0);

    if (maxfps > PDC_MAXFILEHANDLES)
        pdc_error(pdc, PDC_E_IO_TOOMANY_REQFILEHDLS, stemp,
                  pdc_errprintf(pdc, "%d", PDC_MAXFILEHANDLES), 0, 0);

    return _setmaxstdio(maxfps);
}