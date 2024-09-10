static void
createConverter(ConvData *data, const char *converterName, UErrorCode *pErrorCode) {
    ConvData baseData;
    UBool dataIsBase;

    UConverterStaticData *staticData;
    UCMStates *states, *baseStates;

    if(U_FAILURE(*pErrorCode)) {
        return;
    }

    initConvData(data);

    dataIsBase=readFile(data, converterName, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return;
    }

    staticData=&data->staticData;
    states=&data->ucm->states;

    if(dataIsBase) {
        /*
         * Build a normal .cnv file with a base table
         * and an optional extension table.
         */
        data->cnvData=MBCSOpen(data->ucm);
        if(data->cnvData==NULL) {
            *pErrorCode=U_MEMORY_ALLOCATION_ERROR;

        } else if(!data->cnvData->isValid(data->cnvData,
                            staticData->subChar, staticData->subCharLen)
        ) {
            fprintf(stderr, "       the substitution character byte sequence is illegal in this codepage structure!\n");
            *pErrorCode=U_INVALID_TABLE_FORMAT;

        } else if(staticData->subChar1!=0 &&
                    !data->cnvData->isValid(data->cnvData, &staticData->subChar1, 1)
        ) {
            fprintf(stderr, "       the subchar1 byte is illegal in this codepage structure!\n");
            *pErrorCode=U_INVALID_TABLE_FORMAT;

        } else if(
            data->ucm->ext->mappingsLength>0 &&
            !ucm_checkBaseExt(states, data->ucm->base, data->ucm->ext, data->ucm->ext, FALSE)
        ) {
            *pErrorCode=U_INVALID_TABLE_FORMAT;
        } else if(data->ucm->base->flagsType&UCM_FLAGS_EXPLICIT) {
            /* sort the table so that it can be turned into UTF-8-friendly data */
            ucm_sortTable(data->ucm->base);
        }

        if(U_SUCCESS(*pErrorCode)) {
            if(
                /* add the base table after ucm_checkBaseExt()! */
                !data->cnvData->addTable(data->cnvData, data->ucm->base, &data->staticData)
            ) {
                *pErrorCode=U_INVALID_TABLE_FORMAT;
            } else {
                /*
                 * addTable() may have requested moving more mappings to the extension table
                 * if they fit into the base toUnicode table but not into the
                 * base fromUnicode table.
                 * (Especially for UTF-8-friendly fromUnicode tables.)
                 * Such mappings will have the MBCS_FROM_U_EXT_FLAG set, which causes them
                 * to be excluded from the extension toUnicode data.
                 * See MBCSOkForBaseFromUnicode() for which mappings do not fit into
                 * the base fromUnicode table.
                 */
                ucm_moveMappings(data->ucm->base, data->ucm->ext);
                ucm_sortTable(data->ucm->ext);
                if(data->ucm->ext->mappingsLength>0) {
                    /* prepare the extension table, if there is one */
                    data->extData=CnvExtOpen(data->ucm);
                    if(data->extData==NULL) {
                        *pErrorCode=U_MEMORY_ALLOCATION_ERROR;
                    } else if(
                        !data->extData->addTable(data->extData, data->ucm->ext, &data->staticData)
                    ) {
                        *pErrorCode=U_INVALID_TABLE_FORMAT;
                    }
                }
            }
        }
    } else {
        /* Build an extension-only .cnv file. */
        char baseFilename[500];
        char *basename;

        initConvData(&baseData);

        /* assemble a path/filename for data->ucm->baseName */
        uprv_strcpy(baseFilename, converterName);
        basename=(char *)findBasename(baseFilename);
        uprv_strcpy(basename, data->ucm->baseName);
        uprv_strcat(basename, ".ucm");

        /* read the base table */
        dataIsBase=readFile(&baseData, baseFilename, pErrorCode);
        if(U_FAILURE(*pErrorCode)) {
            return;
        } else if(!dataIsBase) {
            fprintf(stderr, "error: the <icu:base> file \"%s\" is not a base table file\n", baseFilename);
            *pErrorCode=U_INVALID_TABLE_FORMAT;
        } else {
            /* prepare the extension table */
            data->extData=CnvExtOpen(data->ucm);
            if(data->extData==NULL) {
                *pErrorCode=U_MEMORY_ALLOCATION_ERROR;
            } else {
                /* fill in gaps in extension file header fields */
                UCMapping *m, *mLimit;
                uint8_t fallbackFlags;

                baseStates=&baseData.ucm->states;
                if(states->conversionType==UCNV_DBCS) {
                    staticData->minBytesPerChar=(int8_t)(states->minCharLength=2);
                } else if(states->minCharLength==0) {
                    staticData->minBytesPerChar=(int8_t)(states->minCharLength=baseStates->minCharLength);
                }
                if(states->maxCharLength<states->minCharLength) {
                    staticData->maxBytesPerChar=(int8_t)(states->maxCharLength=baseStates->maxCharLength);
                }

                if(staticData->subCharLen==0) {
                    uprv_memcpy(staticData->subChar, baseData.staticData.subChar, 4);
                    staticData->subCharLen=baseData.staticData.subCharLen;
                }
                /*
                 * do not copy subChar1 -
                 * only use what is explicitly specified
                 * because it cannot be unset in the extension file header
                 */

                /* get the fallback flags */
                fallbackFlags=0;
                for(m=baseData.ucm->base->mappings, mLimit=m+baseData.ucm->base->mappingsLength;
                    m<mLimit && fallbackFlags!=3;
                    ++m
                ) {
                    if(m->f==1) {
                        fallbackFlags|=1;
                    } else if(m->f==3) {
                        fallbackFlags|=2;
                    }
                }

                if(fallbackFlags&1) {
                    staticData->hasFromUnicodeFallback=TRUE;
                }
                if(fallbackFlags&2) {
                    staticData->hasToUnicodeFallback=TRUE;
                }

                if(1!=ucm_countChars(baseStates, staticData->subChar, staticData->subCharLen)) {
                    fprintf(stderr, "       the substitution character byte sequence is illegal in this codepage structure!\n");
                    *pErrorCode=U_INVALID_TABLE_FORMAT;

                } else if(staticData->subChar1!=0 && 1!=ucm_countChars(baseStates, &staticData->subChar1, 1)) {
                    fprintf(stderr, "       the subchar1 byte is illegal in this codepage structure!\n");
                    *pErrorCode=U_INVALID_TABLE_FORMAT;

                } else if(
                    !ucm_checkValidity(data->ucm->ext, baseStates) ||
                    !ucm_checkBaseExt(baseStates, baseData.ucm->base, data->ucm->ext, data->ucm->ext, FALSE)
                ) {
                    *pErrorCode=U_INVALID_TABLE_FORMAT;
                } else {
                    if(states->maxCharLength>1) {
                        /*
                         * When building a normal .cnv file with a base table
                         * for an MBCS (not SBCS) table with explicit precision flags,
                         * the MBCSAddTable() function marks some mappings for moving
                         * to the extension table.
                         * They fit into the base toUnicode table but not into the
                         * base fromUnicode table.
                         * (Note: We do have explicit precision flags because they are
                         * required for extension table generation, and
                         * ucm_checkBaseExt() verified it.)
                         *
                         * We do not call MBCSAddTable() here (we probably could)
                         * so we need to do the analysis before building the extension table.
                         * We assume that MBCSAddTable() will build a UTF-8-friendly table.
                         * Redundant mappings in the extension table are ok except they cost some size.
                         *
                         * Do this after ucm_checkBaseExt().
                         */
                        const MBCSData *mbcsData=MBCSGetDummy();
                        int32_t needsMove=0;
                        for(m=baseData.ucm->base->mappings, mLimit=m+baseData.ucm->base->mappingsLength;
                            m<mLimit;
                            ++m
                        ) {
                            if(!MBCSOkForBaseFromUnicode(mbcsData, m->b.bytes, m->bLen, m->u, m->f)) {
                                m->f|=MBCS_FROM_U_EXT_FLAG;
                                m->moveFlag=UCM_MOVE_TO_EXT;
                                ++needsMove;
                            }
                        }

                        if(needsMove!=0) {
                            ucm_moveMappings(baseData.ucm->base, data->ucm->ext);
                            ucm_sortTable(data->ucm->ext);
                        }
                    }
                    if(!data->extData->addTable(data->extData, data->ucm->ext, &data->staticData)) {
                        *pErrorCode=U_INVALID_TABLE_FORMAT;
                    }
                }
            }
        }

        cleanupConvData(&baseData);
    }
}