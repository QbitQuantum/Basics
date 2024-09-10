/*
 * xf86LoadOneModule loads a single module.
 */
pointer
xf86LoadOneModule(char *name, pointer opt)
{
    int errmaj, errmin;
    char *Name;
    pointer mod;

    if (!name)
	return NULL;

    /* Normalise the module name */
    Name = xf86NormalizeName(name);

    /* Skip empty names */
    if (Name == NULL)
	return NULL;
    if (*Name == '\0') {
	free(Name);
	return NULL;
    }

    mod = LoadModule(Name, NULL, NULL, NULL, opt, NULL, &errmaj, &errmin);
    if (!mod)
	LoaderErrorMsg(NULL, Name, errmaj, errmin);
    free(Name);
    return mod;
}