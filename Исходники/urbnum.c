static void update_urbnum(char *path, uint64_t count, char *shortname)
{
	struct device_data *ptr;
	FILE *file;
	char fullpath[4096];
	char name[4096], vendor[4096];
	ptr = devices;

	while (ptr) {
		if (strcmp(ptr->pathname, path)==0) {
			ptr->urbs = count;
			sprintf(fullpath, "%s/power/active_duration", path);
			file = fopen(fullpath, "r");
			if (!file)
				return;
			fgets(name, 4096, file);
			ptr->active = strtoull(name, NULL, 10);
			fclose(file);
			sprintf(fullpath, "%s/power/connected_duration", path);
			file = fopen(fullpath, "r");
			if (!file)
				return;
			fgets(name, 4096, file);
			ptr->connected = strtoull(name, NULL, 10);
			fclose(file);

			return;
		}
		ptr = ptr->next;
	}
	/* no luck, new one */
	ptr = malloc(sizeof(struct device_data));
	assert(ptr!=0);
	memset(ptr, 0, sizeof(struct device_data));
	ptr->next = devices;
	devices = ptr;
	strcpy(ptr->pathname, path);
	ptr->urbs = ptr->previous_urbs = count;
	sprintf(fullpath, "%s/product", path);
	file = fopen(fullpath, "r");
	memset(name, 0, 4096);
	if (file) { 
		fgets(name, 4096, file);
		fclose(file);
	}
	sprintf(fullpath, "%s/manufacturer", path);
	file = fopen(fullpath, "r");
	memset(vendor, 0, 4096);
	if (file) { 
		fgets(vendor, 4096, file);
		fclose(file);
	}
	
	if (strlen(name)>0 && name[strlen(name)-1]=='\n')
		name[strlen(name)-1]=0;
	if (strlen(vendor)>0 && vendor[strlen(vendor)-1]=='\n')
		vendor[strlen(vendor)-1]=0;
	/* some devices have bogus names */
	if (strlen(name)<4)
		strcpy(ptr->human_name, path);
	else
		sprintf(ptr->human_name, _("USB device %4s : %s (%s)"), shortname, name, vendor);

	if (strstr(ptr->human_name, "Host Controller"))
		ptr->controller = 1;
	
}