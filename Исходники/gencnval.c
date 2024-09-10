/*
@param standard When standard is 0, then it's the "empty" tag.
*/
static uint16_t
addAlias(const char *alias, uint16_t standard, uint16_t converter, UBool defaultName) {
    uint32_t idx, idx2;
    UBool startEmptyWithoutDefault = FALSE;
    AliasList *aliasList;

    if(standard>=MAX_TAG_COUNT) {
        fprintf(stderr, "%s:%d: error: too many standard tags\n", path, lineNum);
        exit(U_BUFFER_OVERFLOW_ERROR);
    }
    if(converter>=MAX_CONV_COUNT) {
        fprintf(stderr, "%s:%d: error: too many converter names\n", path, lineNum);
        exit(U_BUFFER_OVERFLOW_ERROR);
    }
    aliasList = &tags[standard].aliasList[converter];

    if (strchr(alias, '}')) {
        fprintf(stderr, "%s:%d: error: unmatched } found\n", path, 
            lineNum);
    }

    if(aliasList->aliasCount + 1 >= MAX_TC_ALIAS_COUNT) {
        fprintf(stderr, "%s:%d: error: too many aliases for alias %s and converter %s\n", path, 
            lineNum, alias, GET_ALIAS_STR(converters[converter].converter));
        exit(U_BUFFER_OVERFLOW_ERROR);
    }

    /* Show this warning only once. All aliases are added to the "ALL" tag. */
    if (standard == ALL_TAG_NUM && GET_ALIAS_STR(converters[converter].converter) != alias) {
        /* Normally these option values are parsed at runtime, and they can
           be discarded when the alias is a default converter. Options should
           only be on a converter and not an alias. */
        if (uprv_strchr(alias, UCNV_OPTION_SEP_CHAR) != 0)
        {
            fprintf(stderr, "warning(line %d): alias %s contains a \""UCNV_OPTION_SEP_STRING"\". Options are parsed at run-time and do not need to be in the alias table.\n",
                lineNum, alias);
        }
        if (uprv_strchr(alias, UCNV_VALUE_SEP_CHAR) != 0)
        {
            fprintf(stderr, "warning(line %d): alias %s contains an \""UCNV_VALUE_SEP_STRING"\". Options are parsed at run-time and do not need to be in the alias table.\n",
                lineNum, alias);
        }
    }

    if (standard != ALL_TAG_NUM) {
        /* Check for duplicate aliases for this tag on all converters */
        for (idx = 0; idx < converterCount; idx++) {
            for (idx2 = 0; idx2 < tags[standard].aliasList[idx].aliasCount; idx2++) {
                uint16_t aliasNum = tags[standard].aliasList[idx].aliases[idx2];
                if (aliasNum
                    && ucnv_compareNames(alias, GET_ALIAS_STR(aliasNum)) == 0)
                {
                    if (idx == converter) {
                        /*
                         * (alias, standard) duplicates are harmless if they map to the same converter.
                         * Only print a warning in verbose mode, or if the alias is a precise duplicate,
                         * not just a lenient-match duplicate.
                         */
                        if (verbose || 0 == uprv_strcmp(alias, GET_ALIAS_STR(aliasNum))) {
                            fprintf(stderr, "%s:%d: warning: duplicate aliases %s and %s found for standard %s and converter %s\n", path, 
                                lineNum, alias, GET_ALIAS_STR(aliasNum),
                                GET_TAG_STR(tags[standard].tag),
                                GET_ALIAS_STR(converters[converter].converter));
                        }
                    } else {
                        fprintf(stderr, "%s:%d: warning: duplicate aliases %s and %s found for standard tag %s between converter %s and converter %s\n", path, 
                            lineNum, alias, GET_ALIAS_STR(aliasNum),
                            GET_TAG_STR(tags[standard].tag),
                            GET_ALIAS_STR(converters[converter].converter),
                            GET_ALIAS_STR(converters[idx].converter));
                    }
                    break;
                }
            }
        }

        /* Check for duplicate default aliases for this converter on all tags */
        /* It's okay to have multiple standards prefer the same name */
/*        if (verbose && !dupFound) {
            for (idx = 0; idx < tagCount; idx++) {
                if (tags[idx].aliasList[converter].aliases) {
                    uint16_t aliasNum = tags[idx].aliasList[converter].aliases[0];
                    if (aliasNum
                        && ucnv_compareNames(alias, GET_ALIAS_STR(aliasNum)) == 0)
                    {
                        fprintf(stderr, "%s:%d: warning: duplicate alias %s found for converter %s and standard tag %s\n", path, 
                            lineNum, alias, GET_ALIAS_STR(converters[converter].converter), GET_TAG_STR(tags[standard].tag));
                        break;
                    }
                }
            }
        }*/
    }

    if (aliasList->aliasCount <= 0) {
        aliasList->aliasCount++;
        startEmptyWithoutDefault = TRUE;
    }
    aliasList->aliases = (uint16_t *)uprv_realloc(aliasList->aliases, (aliasList->aliasCount + 1) * sizeof(aliasList->aliases[0]));
    if (startEmptyWithoutDefault) {
        aliasList->aliases[0] = 0;
    }
    if (defaultName) {
        if (aliasList->aliases[0] != 0) {
            fprintf(stderr, "%s:%d: error: Alias %s and %s cannot both be the default alias for standard tag %s and converter %s\n", path, 
                lineNum,
                alias,
                GET_ALIAS_STR(aliasList->aliases[0]),
                GET_TAG_STR(tags[standard].tag),
                GET_ALIAS_STR(converters[converter].converter));
            exit(U_PARSE_ERROR);
        }
        aliasList->aliases[0] = GET_ALIAS_NUM(alias);
    } else {
        aliasList->aliases[aliasList->aliasCount++] = GET_ALIAS_NUM(alias);
    }
/*    aliasList->converter = converter;*/

    converters[converter].totalAliasCount++; /* One more to the column */
    tags[standard].totalAliasCount++; /* One more to the row */

    return aliasList->aliasCount;
}