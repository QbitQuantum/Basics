/*
 * Looks up the mapping table (tzmappings) and returns a Java time
 * zone ID (e.g., "America/Los_Angeles") if found. Otherwise, NULL is
 * returned.
 *
 * value_type is one of the following values:
 *      VALUE_KEY for exact key matching
 *      VALUE_MAPID for MapID and country-based mapping (this is
 *      required for the old Windows, such as NT 4.0 SP3).
 */
static char *matchJavaTZ(const char *java_home_dir, int value_type, char *tzName,
                         char *mapID, const char *country)
{
    int line;
    int IDmatched = 0;
    FILE *fp;
    char *javaTZName = NULL;
    char *items[TZ_NITEMS];
    char mapFileName[_MAX_PATH + 1];
    char lineBuffer[MAX_ZONE_CHAR * 4];
    char bestMatch[MAX_ZONE_CHAR];
    int noMapID = *mapID == '\0';       /* no mapID on Vista */

    bestMatch[0] = '\0';

    strcpy(mapFileName, java_home_dir);
    strcat(mapFileName, MAPPINGS_FILE);

    if ((fp = fopen(mapFileName, "r")) == NULL) {
        jio_fprintf(stderr, "can't open %s.\n", mapFileName);
        return NULL;
    }

    line = 0;
    while (fgets(lineBuffer, sizeof(lineBuffer), fp) != NULL) {
        char *start, *idx, *endp;
        int itemIndex = 0;

        line++;
        start = idx = lineBuffer;
        endp = &lineBuffer[sizeof(lineBuffer)];

        /*
         * Ignore comment and blank lines.
         */
        if (*idx == '#' || *idx == '\n') {
            continue;
        }

        for (itemIndex = 0; itemIndex < TZ_NITEMS; itemIndex++) {
            items[itemIndex] = start;
            while (*idx && *idx != ':') {
                if (++idx >= endp) {
                    goto illegal_format;
                }
            }
            if (*idx == '\0') {
                goto illegal_format;
            }
            *idx++ = '\0';
            start = idx;
        }

        if (*idx != '\n') {
            goto illegal_format;
        }

        if (noMapID || strcmp(mapID, items[TZ_MAPID]) == 0) {
            /*
             * When there's no mapID, we need to scan items until the
             * exact match is found or the end of data is detected.
             */
            if (!noMapID) {
                IDmatched = 1;
            }
            if (strcmp(items[TZ_WIN_NAME], tzName) == 0) {
                /*
                 * Found the time zone in the mapping table.
                 */
                javaTZName = _strdup(items[TZ_JAVA_NAME]);
                break;
            }
            /*
             * Try to find the most likely time zone.
             */
            if (*items[TZ_REGION] == '\0') {
                strncpy(bestMatch, items[TZ_JAVA_NAME], MAX_ZONE_CHAR);
            } else if (country != NULL && strcmp(items[TZ_REGION], country) == 0) {
                if (value_type == VALUE_MAPID) {
                    javaTZName = _strdup(items[TZ_JAVA_NAME]);
                    break;
                }
                strncpy(bestMatch, items[TZ_JAVA_NAME], MAX_ZONE_CHAR);
            }
        } else {
            if (IDmatched == 1) {
                /*
                 * No need to look up the mapping table further.
                 */
                break;
            }
        }
    }
    fclose(fp);

    if (javaTZName == NULL && bestMatch[0] != '\0') {
        javaTZName = _strdup(bestMatch);
    }
    return javaTZName;

 illegal_format:
    (void) fclose(fp);
    jio_fprintf(stderr, "tzmappings: Illegal format at line %d.\n", line);
    return NULL;
}