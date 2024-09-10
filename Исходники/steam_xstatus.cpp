HICON CSteamProto::GetXStatusIcon(int status, UINT flags)
{
	if (status < 1)
		return 0;

	char iconName[100];
	mir_snprintf(iconName, SIZEOF(iconName), "%s_%s", MODULE, "gaming");

	HICON icon = Skin_GetIcon(iconName, (flags & LR_BIGICON) ? 32 : 16);
	return (flags & LR_SHARED) ? icon : CopyIcon(icon);
}