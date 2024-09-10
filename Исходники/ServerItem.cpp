void ServerItem::convert(char *l)
{
	if (strcmp(mode, "netascii") != 0)
		return;
	while (*l != 0) {
		*l = toascii(*l);
		l++;
	}
}