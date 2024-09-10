/**
 * This function is invoked as:
 *
 *  _TOKENIZE('<token_table>', <data_row_id>, <data>, <delimiter>,
 *             <use_token_index>, <data_tag>)
 *
 * If <use_token_index> is omitted, it is treated as 0.
 * If <data_tag> is omitted, it is treated as NULL.
 *
 * It will split <data> on each instance of <delimiter> and insert each token
 * into <token_table>. The following columns in <token_table> are used:
 * token TEXT, source INTEGER, token_index INTEGER, tag (any type)
 * The token_index column is not required if <use_token_index> is 0.
 * The tag column is not required if <data_tag> is NULL.
 *
 * One row is inserted for each token in <data>.
 * In each inserted row, 'source' is <data_row_id>.
 * In the first inserted row, 'token' is the hex collation key of
 * the entire <data> string, and 'token_index' is 0.
 * In each row I (where 1 <= I < N, and N is the number of tokens in <data>)
 * 'token' will be set to the hex collation key of the I:th token (0-based).
 * If <use_token_index> != 0, 'token_index' is set to I.
 * If <data_tag> is not NULL, 'tag' is set to <data_tag>.
 *
 * In other words, there will be one row for the entire string,
 * and one row for each token except the first one.
 *
 * The function returns the number of tokens generated.
 */
static void tokenize(sqlite3_context * context, int argc, sqlite3_value ** argv)
{
    //ALOGD("enter tokenize");
    int err;
    int useTokenIndex = 0;
    int useDataTag = 0;

    if (!(argc >= 4 || argc <= 6)) {
        ALOGE("Tokenize requires 4 to 6 arguments");
        sqlite3_result_null(context);
        return;
    }

    if (argc > 4) {
        useTokenIndex = sqlite3_value_int(argv[4]);
    }

    if (argc > 5) {
        useDataTag = (sqlite3_value_type(argv[5]) != SQLITE_NULL);
    }

    sqlite3 * handle = sqlite3_context_db_handle(context);
    UCollator* collator = (UCollator*)sqlite3_user_data(context);
    char const * tokenTable = (char const *)sqlite3_value_text(argv[0]);
    if (tokenTable == NULL) {
        ALOGE("tokenTable null");
        sqlite3_result_null(context);
        return;
    }

    // Get or create the prepared statement for the insertions
    sqlite3_stmt * statement = (sqlite3_stmt *)sqlite3_get_auxdata(context, 0);
    if (!statement) {
        char const * tokenIndexCol = useTokenIndex ? ", token_index" : "";
        char const * tokenIndexParam = useTokenIndex ? ", ?" : "";
        char const * dataTagCol = useDataTag ? ", tag" : "";
        char const * dataTagParam = useDataTag ? ", ?" : "";
        char * sql = sqlite3_mprintf("INSERT INTO %s (token, source%s%s) VALUES (?, ?%s%s);",
                tokenTable, tokenIndexCol, dataTagCol, tokenIndexParam, dataTagParam);
        err = sqlite3_prepare_v2(handle, sql, -1, &statement, NULL);
        sqlite3_free(sql);
        if (err) {
            ALOGE("prepare failed");
            sqlite3_result_null(context);
            return;
        }
        // This binds the statement to the table it was compiled against, which is argv[0].
        // If this function is ever called with a different table the finalizer will be called
        // and sqlite3_get_auxdata() will return null above, forcing a recompile for the new table.
        sqlite3_set_auxdata(context, 0, statement, tokenize_auxdata_delete);
    } else {
        // Reset the cached statement so that binding the row ID will work properly
        sqlite3_reset(statement);
    }

    // Bind the row ID of the source row
    int64_t rowID = sqlite3_value_int64(argv[1]);
    err = sqlite3_bind_int64(statement, 2, rowID);
    if (err != SQLITE_OK) {
        ALOGE("bind failed");
        sqlite3_result_null(context);
        return;
    }

    // Bind <data_tag> to the tag column
    if (useDataTag) {
        int dataTagParamIndex = useTokenIndex ? 4 : 3;
        err = sqlite3_bind_value(statement, dataTagParamIndex, argv[5]);
        if (err != SQLITE_OK) {
            ALOGE("bind failed");
            sqlite3_result_null(context);
            return;
        }
    }

    // Get the raw bytes for the string to tokenize
    // the string will be modified by following code
    // however, sqlite did not reuse the string, so it is safe to not dup it
    UChar * origData = (UChar *)sqlite3_value_text16(argv[2]);
    if (origData == NULL) {
        sqlite3_result_null(context);
        return;
    }

    // Get the raw bytes for the delimiter
    const UChar * delim = (const UChar *)sqlite3_value_text16(argv[3]);
    if (delim == NULL) {
        ALOGE("can't get delimiter");
        sqlite3_result_null(context);
        return;
    }

    UChar * token = NULL;
    UChar *state;
    int numTokens = 0;

    do {
        if (numTokens == 0) {
            token = origData;
        }

        // Reset the program so we can use it to perform the insert
        sqlite3_reset(statement);
        UErrorCode status = U_ZERO_ERROR;
        char keybuf[1024];
        uint32_t result = ucol_getSortKey(collator, token, -1, (uint8_t*)keybuf, sizeof(keybuf)-1);
        if (result > sizeof(keybuf)) {
            // TODO allocate memory for this super big string
            ALOGE("ucol_getSortKey needs bigger buffer %d", result);
            break;
        }
        uint32_t keysize = result-1;
        uint32_t base16Size = keysize*2;
        char *base16buf = (char*)malloc(base16Size);
        base16Encode(base16buf, keybuf, keysize);
        err = sqlite3_bind_text(statement, 1, base16buf, base16Size, SQLITE_STATIC);

        if (err != SQLITE_OK) {
            ALOGE(" sqlite3_bind_text16 error %d", err);
            free(base16buf);
            break;
        }

        if (useTokenIndex) {
            err = sqlite3_bind_int(statement, 3, numTokens);
            if (err != SQLITE_OK) {
                ALOGE(" sqlite3_bind_int error %d", err);
                free(base16buf);
                break;
            }
        }

        err = sqlite3_step(statement);
        free(base16buf);

        if (err != SQLITE_DONE) {
            ALOGE(" sqlite3_step error %d", err);
            break;
        }
        numTokens++;
        if (numTokens == 1) {
            // first call
            u_strtok_r(origData, delim, &state);
        }
    } while ((token = u_strtok_r(NULL, delim, &state)) != NULL);
    sqlite3_result_int(context, numTokens);
}