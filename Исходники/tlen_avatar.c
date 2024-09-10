static void SetAvatar(HANDLE hContact, JABBER_LIST_ITEM *item, char *data, int len, DWORD format) {
	FILE* out;
	char filename[MAX_PATH];
	char md5[33];
	MD5 context;
	int i;
	md5_init(&context);
	md5_update(&context, data, len);
	md5_finalize(&context);
	if (format == PA_FORMAT_UNKNOWN && len > 4) {
		format = JabberGetPictureType(data);
	}
	for (i=0;i<16;i++) {
		char lo, hi;
		unsigned int j=context.state[i>>2];
		j>>=8*(i%4);
		j&=0xFF;
		lo = j & 0x0F;
		hi = j >> 4;
		hi = hi + ((hi > 9) ? 'a' - 10 : '0');
		lo = lo + ((lo > 9) ? 'a' - 10 : '0');
		md5[i*2] = hi;
		md5[i*2+1] = lo;
	}
	md5[i*2] = 0;
	if (item != NULL) {
		char *hash = item->avatarHash;
		item->avatarFormat = format;
		item->avatarHash = mir_strdup(md5);
		mir_free(hash);
	} else {
		jabberThreadInfo->avatarFormat = format;
		strcpy(jabberThreadInfo->avatarHash, md5);
	}
	TlenGetAvatarFileName(item, filename, sizeof filename );
	DeleteFileA(filename);
	out = fopen( filename, "wb" );
	if ( out != NULL ) {
		fwrite( data, len, 1, out );
		fclose( out );
		DBWriteContactSettingString(hContact, "ContactPhoto", "File", filename );
		DBWriteContactSettingString(hContact, jabberProtoName, "AvatarHash",  md5);
		DBWriteContactSettingDword(hContact, jabberProtoName, "AvatarFormat",  format);
	}
	ProtoBroadcastAck( jabberProtoName, hContact, ACKTYPE_AVATAR, ACKRESULT_STATUS, NULL , 0);
}