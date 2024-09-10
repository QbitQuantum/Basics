void PSDRV_AFM2C(const AFM *afm)
{
    char    buffer[256];
    FILE    *of;
    int     i;

    lstrcpynA(buffer, afm->FontName, sizeof(buffer) - 2);

    for (i = 0; i < strlen(buffer); ++i)
    	if (buffer[i] == '-')
	    buffer[i] = '_';

    buffer[i] = '.';  buffer[i + 1] = 'c';  buffer[i + 2] = '\0';

    MESSAGE("writing '%s'\n", buffer);

    of = fopen(buffer, "w");
    if (of == NULL)
    {
    	ERR("error opening '%s' for writing\n", buffer);
	return;
    }

    buffer[i] = '\0';

    writeHeader(of, afm, buffer);
    writeMetrics(of, afm, buffer);
    writeAFM(of, afm, buffer);

    fclose(of);
}