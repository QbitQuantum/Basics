//キャッシュにあればコピー
//ph:アーカイブ情報を受け取るハンドルへのポインタ
//pinfo:アーカイブのファイル情報を受け取るポインタ
//		あらかじめ pinfo に filename か position をセットしておく。
//		キャッシュがあれば filename(position) の一致する情報を返す。
//キャッシュになければ、SPI_NO_FUNCTION が返る。
//キャッシュにあれば SPI_ALL_RIGHT が返る。
//アーカイブ情報はキャッシュにあるが、filename(position) が一致しない場合は
//SPI_NOT_SUPPORT が返る。エラーの場合はエラーコードが返る。
int InfoCache::Dupli(char *filepath, HLOCAL *ph, fileInfo *pinfo)
{
	cs.Enter();
	HLOCAL hinfo;
	int ret = GetCache(filepath, &hinfo);

if (ret) {
	ret = SPI_ALL_RIGHT;
	if (ph != NULL) {
		UINT size = LocalSize(hinfo);
		/* 出力用のメモリの割り当て */
		*ph = LocalAlloc(LMEM_FIXED, size);
		if (*ph == NULL) {
			ret = SPI_NO_MEMORY;
		} else {
			memcpy(*ph, (void*)hinfo, size);
		}
	} else {
		fileInfo *ptmp = (fileInfo *)hinfo;
		if (pinfo->filename[0] != '\0') {
			for (;;) {
				if (ptmp->method[0] == '\0') {
					ret = SPI_NOT_SUPPORT;
					break;
				}
				// complete path relative to archive root
				char path[sizeof(ptmp->path)+sizeof(ptmp->filename)];
				strcpy(path, ptmp->path);
				size_t len = strlen(path);
				if(len && path[len-1] != '/' && path[len-1] != '\\') // need delimiter
					strcat(path, "\\");
				strcat(path, ptmp->filename);
				if (lstrcmpi(path, pinfo->filename) == 0) break;
				ptmp++;
			}
		} else {
			for (;;) {
				if (ptmp->method[0] == '\0') {
					ret = SPI_NOT_SUPPORT;
					break;
				}
				if (ptmp->position == pinfo->position) break;
				ptmp++;
			}
		}
		if (ret == SPI_ALL_RIGHT) *pinfo = *ptmp;
	}
} else {
	ret = SPI_NO_FUNCTION;
}

	cs.Leave();
	return ret;
}