Bool
applyConfig(char *name)
{
    FILE *fp;
    Bool ok;

    if ((fp = findFileInPath(name, "")) == NULL)
        return False;
    ok = XkbCFParse(fp, XkbCFDflts, NULL, &cfgResult);
    fclose(fp);
    if (!ok)
    {
        ERR1("Couldn't find configuration file \"%s\"\n", name);
        return False;
    }
    if (cfgResult.rules_file)
    {
        trySetString(RULES_NDX, cfgResult.rules_file, FROM_CONFIG);
        cfgResult.rules_file = NULL;
    }
    if (cfgResult.model)
    {
        trySetString(MODEL_NDX, cfgResult.model, FROM_CONFIG);
        cfgResult.model = NULL;
    }
    if (cfgResult.layout)
    {
        trySetString(LAYOUT_NDX, cfgResult.layout, FROM_CONFIG);
        cfgResult.layout = NULL;
    }
    if (cfgResult.variant)
    {
        trySetString(VARIANT_NDX, cfgResult.variant, FROM_CONFIG);
        cfgResult.variant = NULL;
    }
    if (cfgResult.options)
    {
        addStringToOptions(cfgResult.options, &szOptions, &numOptions,
                           &options);
        cfgResult.options = NULL;
    }
    if (cfgResult.keymap)
    {
        trySetString(KEYMAP_NDX, cfgResult.keymap, FROM_CONFIG);
        cfgResult.keymap = NULL;
    }
    if (cfgResult.keycodes)
    {
        trySetString(KEYCODES_NDX, cfgResult.keycodes, FROM_CONFIG);
        cfgResult.keycodes = NULL;
    }
    if (cfgResult.geometry)
    {
        trySetString(GEOMETRY_NDX, cfgResult.geometry, FROM_CONFIG);
        cfgResult.geometry = NULL;
    }
    if (cfgResult.symbols)
    {
        trySetString(SYMBOLS_NDX, cfgResult.symbols, FROM_CONFIG);
        cfgResult.symbols = NULL;
    }
    if (cfgResult.types)
    {
        trySetString(TYPES_NDX, cfgResult.types, FROM_CONFIG);
        cfgResult.types = NULL;
    }
    if (cfgResult.compat)
    {
        trySetString(COMPAT_NDX, cfgResult.compat, FROM_CONFIG);
        cfgResult.compat = NULL;
    }
    if (verbose > 5)
    {
        MSG("After config file:\n");
        dumpNames(True, True);
    }
    return True;
}