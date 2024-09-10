static void get_service_name(char* service_name)
{
	service_name[0] = 0;

	if (PathFileExistsA("/etc/pam.d/freerds"))
	{
		strncpy(service_name, "freerds", 255);
	}
	else
	{
		strncpy(service_name, "gdm", 255);
	}
}