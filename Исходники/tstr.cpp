/*=========================================================================
	パス合成（ANSI 版）
=========================================================================*/
int MakePath(char *dest, const char *dir, const char *file, int max_len)
{
	if (!dir) {
		dir = dest;
	}

	int	len;
	if (dest == dir) {
		len = (int)strlen(dir);
	} else {
		len = strcpyz(dest, dir);
	}

	if (len > 0) {
		bool	need_sep = (dest[len -1] != '\\');

		if (len >= 2 && !need_sep) {	// 表などで終端の場合は sep必要
			BYTE	*p = (BYTE *)dest;
			while (*p) {
				if (IsDBCSLeadByte(*p) && *(p+1)) {
					p += 2;
					if (!*p) {
						need_sep = true;
					}
				} else {
					p++;
				}
			}
		}
		if (need_sep) {
			dest[len++] = '\\';
		}
	}
	return	len + strncpyz(dest + len, file, max_len - len);
}