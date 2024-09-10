int x11_shadow_pam_get_service_name(SHADOW_PAM_AUTH_INFO* info)
{
	if (PathFileExistsA("/etc/pam.d/lightdm"))
	{
		info->service_name = _strdup("lightdm");
	}
	else if (PathFileExistsA("/etc/pam.d/gdm"))
	{
		info->service_name = _strdup("gdm");
	}
	else if (PathFileExistsA("/etc/pam.d/xdm"))
	{
		info->service_name = _strdup("xdm");
	}
	else if (PathFileExistsA("/etc/pam.d/login"))
	{
		info->service_name = _strdup("login");
	}
	else if (PathFileExistsA("/etc/pam.d/sshd"))
	{
		info->service_name = _strdup("sshd");
	}
	else
	{
		return -1;
	}

	if (!info->service_name)
		return -1;

	return 1;
}