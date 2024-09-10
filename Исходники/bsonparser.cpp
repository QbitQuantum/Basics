BSONObj* BSONParser::parseBSON(const char* c, __int32& pos) throw(BSONException) {
    BSONObj* res = new BSONObj();
    __int32 state = 0; // 0 - nothing, 1 - name, 2- value
    __int32 lenBuffer = strlen(c);
    char* buffer = (char*)malloc(lenBuffer);
    char* name = NULL;
    void* value = NULL;
    __int32 len = 0;
    BSONTYPE type;
    __int32 stringOpen = 0; // 0 - closed
    // 1 - Single quote opened
    // 2 - Double quote opened
    __int32 x;
    for (x= pos; x < strlen(c); x++) {
        if (c[x] == '{') {
            if (state == 2) {
                value = parseBSON(c, x);
                type = BSON_TYPE;
            } else if (state == 0) {
                memset(buffer, 0, lenBuffer);
                state = 1;// name
                type = LONG64_TYPE;
            } else { // state == 1
                throw "json value is not allowed as name";
            }
            continue;
        }
        if (c[x] == '[') {
            value = parseArray(c, x);
            type = BSONARRAY_TYPE;
        }
        if (c[x] == '}' || c[x] == ',') {
            if (name != NULL) {
                if ((type != BSON_TYPE) && (type != BSONARRAY_TYPE)) {
                    value = (char*)malloc(len+1);
                    memset(value, 0, len + 1);
                    strcpy((char*)value, buffer);
                }
                len = 0;
                memset(buffer, 0, lenBuffer);
                switch (type) {
                case BOOL_TYPE: {
                    bool bVal = strcmp((char*)value, "true") == 0;
                    res->add(name, bVal);
                    break;
                }
                case INT_TYPE: {
                    __int32 iVal = atoi((char*)value);
                    res->add(name, iVal);
                    break;
                }
                case LONG_TYPE: {
                    __int64 lVal = atol((char*)value);
                    res->add(name, lVal);
                    break;
                }
                case LONG64_TYPE: {
#ifdef WINDOWS
                    __LONG64 lVal = _atoi64((char*)value);
#else
                    __LONG64 lVal = atoll((char*)value);
#endif
                    if (lVal <= INT_MAX) {
                        res->add(name, (__int32)lVal);
                    } else if (lVal <= LONG_MAX) {
                        res->add(name, (__int64)lVal);
                    } else {
                        res->add(name, lVal);
                    }
                    break;
                }
                case DOUBLE_TYPE: {
                    double dVal = atof((char*)value);
                    res->add(name, dVal);
                    break;
                }
                case STRING_TYPE:
                {
                    res->add(name, (char*)value);
                    break;
                }
                case BSON_TYPE:
                {
                    res->add(name, *((BSONObj*)value));
                    delete (BSONObj*)value;
                    break;
                }
                case BSONARRAY_TYPE:
                {
                    res->add(name, *((BSONArrayObj*)value));
                    delete (BSONArrayObj*)value;
                    break;
                }

                }
                free(name);
                name = NULL;
                if ((type != BSON_TYPE) && (type != BSONARRAY_TYPE)) {
                    free(value);
                    value = NULL;
                }
                if (c[x] != '}') {
                    state = 1; // name
                    type = LONG64_TYPE;
                    continue;
                }
            }
            if (c[x] == '}') {
                break;
            }
        }
        if (c[x] == ':') {
            name = (char*)malloc(len+1);
            memset(name, 0, len + 1);
            strcpy(name, buffer);
            len = 0;
            memset(buffer, 0, lenBuffer);
            state = 2; //value
            // default type
            type = LONG64_TYPE;
        } else {
            if (c[x] == '\'' || (c[x] == '\"')) {
                // Collect all the characters
                type = STRING_TYPE;
                char stringChar = c[x];
                bool escaped = false;
                x++;
                __int32 startPos = x;
                while ((x < strlen(c)) && ((c[x] != stringChar) || (escaped))) {
                    if (c[x] == '\\') {
                        escaped = true;
                    } else {
                        escaped = false;
                    }
                    buffer[len] = c[x];
                    len++;
                    x++;
                }
                if (x >= strlen(c)) {
                    char c[100];
                    sprintf(c, "An error ocurred parsing the bson. Error: unclosed string at %d",  startPos);

                    throw new BSONException(c);
                }
                continue;
            }

            if (c[x] == ' ' && stringOpen == 0) {
                continue;
            }
            if (c[x] == '\r' || c[x] == '\n') {
                continue;
            }
            if (c[x] == '.' && state == 2) {
                type = DOUBLE_TYPE;
            }
            buffer[len] = c[x];
            len++;
        }

    }
    pos = x;

    free(buffer);
    return res;
}