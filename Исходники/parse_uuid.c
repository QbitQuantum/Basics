void parseGetUUID(char *id, size_t id_size) {
    size_t i = 0;
	UUID uuid;
	char *uuid_string;
	UuidCreate(&uuid);
	UuidToStringA(&uuid, &uuid_string);

    strncpy_s(id, id_size, uuid_string, _TRUNCATE);
	i = 0;
    for ( ; i < strlen(id) ; i++) {
        id[i] = tolower(id[i]);
    }

	RpcStringFreeA(&uuid_string);
}