void WriteCrossCheck(FILE * f)
{
    int i, j;
    VARPTR var;

    Fprintf(f, indent, "/* cross variable size checking */\n");
    for (i = 0; i < nVariable; i++)
    {
        var = variables[i];
        if (var->type == DIMFOREXT)
        {
            if (var->nfor_name > 1)
            {
                for (j = 1; j < var->nfor_name; j++)
                {
                    /** we do not check square variables : this is done elsewhere */
                    /* we do not check external values since they are not known here */
                    if ((var->for_name_orig[j] != var->for_name_orig[j - 1]) && (var->for_name[j - 1][1] != 'e' && var->for_name[j][1] != 'e'))
                    {
                        Fprintf(f, indent, "CheckDimProp(%d,%d,%s != %s);\n",
                                var->for_name_orig[j - 1], var->for_name_orig[j], var->for_name[j - 1], var->for_name[j]);
                    }
                }
            }
        }
        else if (var->type == SCALAR)
        {
            /** some dimensions are given by a scalar input argument **/
            if (var->nfor_name > 1)
            {
                for (j = 1; j < var->nfor_name; j++)
                {
                    int dim = 2;

                    if (var->for_name[j][0] == 'm')
                        dim = 1;
                    if (var->for_name[j][1] != 'e') /* do not check external variables */
                    {
                        if (strncmp(var->for_name[0], "istk", 4) == 0)
                            Fprintf(f, indent, "CheckOneDim(%d,%d,%s,*%s);\n", var->for_name_orig[j], dim, var->for_name[j], var->for_name[0]);
                        else
                            Fprintf(f, indent, "CheckOneDim(%d,%d,%s,%s);\n", var->for_name_orig[j], dim, var->for_name[j], var->for_name[0]);
                    }
                }
            }
        }
    }
    /*
     * FCprintf(f,"/ *       cross formal parameter checking\n");
     * FCprintf(f," *      not implemented yet * /\n");  */
}