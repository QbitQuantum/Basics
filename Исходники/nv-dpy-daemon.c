int main(int argc, char *argv[]) {
  Display *dpy;
  Bool ret;
  int screen, display_devices[2];
  char* environment = getenv("XDG_CONFIG_HOME");
  char* configuration;

  if (environment == NULL) {
    // no XDG_CONFIG_HOME set, default is $HOME/.config/
    environment = getenv("HOME");
    configuration = (char*)calloc(sizeof(char), strlen(environment)
				  + strlen(CONFIG_FILE)
				  + strlen("/.config/") + 1);
    strcpy(configuration, environment);
    strcat(configuration, "/.config/");
  } else {
    configuration = (char*)calloc(sizeof(char), strlen(environment)
				  + strlen(CONFIG_FILE) + 1);
  }
  strcat(configuration, CONFIG_FILE);
  printf("Using callback file %s\n", configuration);

  ret = setup(&dpy, &screen);
  if (!ret) {
    return 1;
  }

  ret = XNVCTRLQueryAttribute(dpy, screen, 0,
			      NV_CTRL_PROBE_DISPLAYS, &display_devices[0]);
  if (!ret) {
    fprintf(stderr, "Failed to query the enabled Display Devices.\n\n");
    return 1;
  }

  while (True) {
    usleep(2 * 1000 * 1000);
    /*
     * first, probe for new display devices; while
     * NV_CTRL_CONNECTED_DISPLAYS reports what the NVIDIA X driver
     * believes is currently connected to the GPU,
     * NV_CTRL_PROBE_DISPLAYS forces the driver to redetect what
     * is connected.
     */
    ret = XNVCTRLQueryAttribute(dpy, screen, 0,
				NV_CTRL_PROBE_DISPLAYS, &display_devices[0]);
    if (display_devices[0] != display_devices[1]) {
      display_devices[1] = display_devices[0];
      char** strs = identifier(dpy, display_devices[0], screen);
      strs[0] = configuration; // First argument is the executable, by convention
      if (fork() == 0) { // Child
	execv(configuration, strs);
	fprintf(stderr, "An error occured executing the daemon callback file\n");
	return 0;
      }
      int i = 1;
      while(strs[i] != NULL) {
#ifdef DEBUG
	printf("%d: \"%s\"\n", i, strs[i]);
#endif
	free(strs[i++]);
      }
    }
  }

  return 0;
}